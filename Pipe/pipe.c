#include "pipe.h"

#include <errno.h>     // for errno, ENOENT, EAGAIN, EEXIST, ENXIO
#include <fcntl.h>     // for open, O_NONBLOCK, O_RDONLY, O_WRONLY
#include <stdio.h>     // for perror, dprintf, sprintf, NULL
#include <stdlib.h>    // for free, exit, malloc, EXIT_FAILURE
#include <string.h>    // for strerror, strdup, strlen
#include <sys/stat.h>  // for mkfifo
#include <sys/types.h> // for ssize_t, size_t
#include <unistd.h>    // for close, read

#include "log.h" // for log_error, log_warn, log_debug, log_info

#define FD_LENGTH 5

int create_fifo(char name[]) {
  if (mkfifo(name, 0666) < 0) {
    switch (errno) {
    case 0:
      log_debug("Created fifo '%s'", name);
      break;
    case EEXIST:
      log_debug("Fifo '%s': File exists", name);
      break;
    default:
      log_error("Can't create fifo '%s': %s", name, strerror(errno));
      return -1;
    }
  }
  return 0;
}

char *pipe_format(Pipe *self) {
  int len = 24 + 2 * FD_LENGTH;
  len += strlen(self->name_in);
  len += strlen(self->name_out);

  char *result = malloc(len * sizeof(char));
  if (result == NULL) {
    log_error("Can't allocate %d char: %s", len, strerror(errno));
    ;
    return NULL;
  }

  sprintf(result, "Pipe{in: '%s':%d, out: '%s':%d}", self->name_in, self->in,
          self->name_out, self->out);

  return result;
}

int pipe_open_read_non_block(Pipe *self) {
  if (self->in == -1) {
    int result = open(self->name_in, O_RDONLY | O_NONBLOCK);
    if (result == -1) {
      return -errno;
    }
    self->in = result;
  }
  return 0;
}

int pipe_open_read(Pipe *self) {
  if (self->in == -1) {
    int result = open(self->name_in, O_RDONLY);
    if (result == -1) {
      return -errno;
    }
    self->in = result;
  }
  return 0;
}

int pipe_open_write_non_block(Pipe *self) {
  if (self->out == -1) {
    int result = open(self->name_out, O_WRONLY | O_NONBLOCK);
    if (result == -1) {
      return -errno;
    }
    self->out = result;
  }
  return 0;
}

int pipe_open_write(Pipe *self) {
  if (self->out == -1) {
    int result = open(self->name_out, O_WRONLY);
    if (result < 0) {
      return -errno;
    }
    self->out = result;
  }
  return 0;
}

void pipe_init(Pipe *self, char *name_in, char *name_out) {
  self->in = -1;
  self->out = -1;

  self->name_in = strdup(name_in);
  self->name_out = strdup(name_out);

  create_fifo(self->name_in);
  create_fifo(self->name_out);

  pipe_open_read_non_block(self);
  pipe_open_write_non_block(self);
}

int pipe_read(Pipe *self, char buffer[], size_t size) {
  int res = pipe_open_read_non_block(self);
  if (res < 0) {
    return res;
  }

  if (self->in != -1) {
    ssize_t count = read(self->in, buffer, size - 1);
    if (count == -1) {
      switch (errno) {
      case EAGAIN:
        return 0;
      default:
        return -errno;
      }
    }
    buffer[count] = '\0';
    return count;
  }
  return 0;
}

int pipe_write(Pipe *self, char *to_send) {
  int res = pipe_open_write(self);
  if (res < 0) {
    return res;
  }

  if (self->out < 0) {
    log_warn("Can't write on '%s': Pipe closed", self->name_out);
  } else {
    int res = dprintf(self->out, "%s", to_send);
    if (res < 1) {
      log_error("Can't write on '%s': %s", self->name_out, strerror(errno));
      return -errno;
    }
    log_trace("Sent '%s'", to_send);
  }
  return 0;
}

void pipe_free(Pipe *self) {
  if (self->in >= 0) {
    close(self->in);
  }
  if (self->out >= 0) {
    close(self->out);
  }
  free(self->name_in);
  free(self->name_out);
}

#ifdef MAIN

#include <sys/stat.h>
#include <sys/types.h>

#define PIPENAME "/tmp/test.fifo"
#define BUFFER_SIZE 256

// To do before running test:
//   tail -f /tmp/test.fifo
//
// Expected result:
//   Pipe{in: -1, out: -1, name_in: '/tmp/test.fifo', name_out:
//   '/tmp/test.fifo'} 4: 'toto'

void pipe_print(Pipe *self) {
  char *p = pipe_format(self);
  printf("%s\n", p);
  free(p);
}

int main() {
  Pipe p;
  pipe_init(&p, PIPENAME, PIPENAME);

  pipe_print(&p);

  pipe_write(&p, "toto");

  char buffer[BUFFER_SIZE];
  buffer[0] = '\0';
  ssize_t count = 0;
  while (count == 0) {
    count = pipe_read(&p, buffer);
    printf("%zd: '%s'\n", count, buffer);
    usleep(100000);
  }

  pipe_print(&p);

  pipe_free(&p);
}
#endif
