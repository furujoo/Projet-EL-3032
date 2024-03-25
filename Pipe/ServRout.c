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

    pipe_init(&pipe,"servR.pipe" , "servD.pipe" );
    char *toto = pipe_format(&pipe);
    printf( "  %s \n", toto);
    //pipe_write("serv.pipe", 'Ping');
    free(toto);
}

void PipeServRClient(Pipe pipe){

    pipe_init(&pipe,"servR.pipe" , "client.pipe" );
    char *toto = pipe_format(&pipe);
    printf( "  %s \n", toto);
    //pipe_write("serv.pipe", 'Ping');
    free(toto);
}

int main()
{
    char buffer[BUFFER_SIZE];
    //char message;
    Pipe pServRClient;
    Pipe pServRD;

    PipeServRoutd(pServRD);
    PipeServRClient(pServRClient);

    while(1){
        int result = pipe_read(&pServRD,buffer,BUFFER_SIZE);

        if( result >0){
            printf("Données lu (%d) :%s \n",result, buffer);
        }

        //pipe_write(&pServRD,buffer);

    }
    
    char FileConfigPath[] = "/workspaces/Projet-EL-3032/Serveur de routage/FichierRoutage.txt";
    char ListeServPath[] = "/workspaces/Projet-EL-3032/Base de donnée/ListeServer.txt";

    

    //PipeServRoutd(p);
    
    
}