// Projet_EL3032.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <fcntl.h> // for open, O_RDONLY, O_WRONLY
#include <stdio.h> // for printf
#include <sys/stat.h> // for mkfifo
#include <unistd.h> // for read, write
#include <stdlib.h>
#include "pipe.h"

#define BUFFER_SIZE 256

//#define CLIENT_SERV_TUBE "clientserv.tube"

void PipeServDoRout(Pipe pipe){

    pipe_init(&pipe,"serv.pipe" , "servR.pipe" );
    char *toto = pipe_format(&pipe);
    printf( "  %s \n", toto);
    //pipe_write("serv.pipe", 'Ping');
     free(toto);
}






int main()
{
    char buffer[BUFFER_SIZE];
    Pipe pSR;
    

    FILE *Serv = fopen("/workspaces/Projet-EL-3032/Base de donnée/ListeServer.txt", "r");


    PipeServDoRout(pSR);
    //PipeServClient(pSC);

    while(1){
        pipe_read(&pSR, buffer, BUFFER_SIZE);// Utilsier getopt ou juste argc/argv
        printf("Données lu :%s \n", buffer);

    }

    //test
    //pipe_init(&p,"serv.pipe" , "client.pipe" );
    //char *toto = pipe_format(&p);
    //printf( "  %s \n", toto);
    //pipe_write(CLIENT_SERV_TUBE, );
    
  
}