// Projet_EL3032.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <fcntl.h> // for open, O_RDONLY, O_WRONLY
#include <stdio.h> // for printf
#include <sys/stat.h> // for mkfifo
#include <unistd.h> // for read, write
#include <stdlib.h>
#include "pipe.h"

#define BUFFER_SIZE 256

#define CLIENT_SERV_TUBE "clientserv.tube"

void PipeServRoutD(Pipe pipe){

    pipe_init(&pipe,"servDR.pipe" , "servD.pipe" );
    char *toto = pipe_format(&pipe);
    printf( "  %s \n", toto);
    //pipe_write("serv.pipe", 'Ping');
    free(toto);
}

void PipeServRClient(Pipe pipe){

    pipe_init(&pipe,"servCR.pipe" , "client.pipe" );
    char *toto = pipe_format(&pipe);
    printf( "  %s \n", toto);
    //pipe_write("serv.pipe", 'Ping');
    free(toto);
}

int main()
{
    char buffer[BUFFER_SIZE];
    //char message;
    Pipe pServRClient, pServRD;

    PipeServRoutD(pServRD);
    PipeServRClient(pServRClient);

    FILE* RoutageF = fopen ( "FichierRoutage.txt", "r+" );

    if (RoutageF == NULL) {
        perror("Error opening FichierRoutage.txt");
        exit(EXIT_FAILURE);
    }

       while (1) {
        // Read from servCR.pipe
        int result = pipe_read(&pServRClient, buffer, BUFFER_SIZE);

        if (result > 0) {
            printf("Data read (%d bytes): %s\n", result, buffer);

            // Write to FichierRoutage.txt
            if (fwrite(buffer, 1, result, RoutageF) != result) {
                perror("Error writing to FichierRoutage.txt");
                exit(EXIT_FAILURE);
            }

            // Write to servRD.pipe
            if (pipe_write(&pServRD, buffer) == -1) {
                perror("Error writing to servRD.pipe");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    int fclose (FILE* RoutageF);
    
}