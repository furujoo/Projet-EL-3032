#ifndef COMMON_NAMED_PIPE_H
#define COMMON_NAMED_PIPE_H

#include <sys/types.h> // for size_t, ssize_t

// Strusture with data to handle two named pipe (In + out)
//   Use lazy openning: i.e. open pipes only on first read/write
typedef struct Pipe {
  int in;
  int out;
  char *name_in;
  char *name_out;
} Pipe;

/* Format a named pipe into a string
   /!\ result must be freed /!\ */
char *pipe_format(Pipe *self);

void pipe_init(Pipe *self, char *name_in, char *name_out);

int pipe_open_read(Pipe *self);

int pipe_open_write(Pipe *self);

// Try to read on input pipe
int pipe_read(Pipe *self, char buffer[], size_t size);

// Try to write on output pipe
int pipe_write(Pipe *self, char *to_send);

// Free pipe handler
void pipe_free(Pipe *self);

#endif // COMMON_NAMED_PIPE_H
