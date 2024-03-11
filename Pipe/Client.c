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

void PipeClientServ(Pipe pipe){

    pipe_init(&pipe,"client.pipe" , "serv.pipe" );
    char *toto = pipe_format(&pipe);
    printf( "  %s \n", toto);
    //pipe_write(CLIENT_SERV_TUBE, 'Ping');
    free(toto);
}


int main()
{
    //char buffer[BUFFER_SIZE];
    Pipe p;
    
    char CodeServ[4];
    char CodeLieu[4];
    char CodeMenu[4];

    

    scanf("%s",CodeServ);
    scanf("%s",CodeLieu);
    scanf("%s",CodeMenu);

   // char message= '|'+CodeServ+'|'+ CodeLieu +'|'+CodeMenu+'|'; 


    PipeClientServ(p);

    //printf("|%s|%s|%s|",CodeServ,CodeLieu,CodeMenu);

    
    

    //test
   
    
   
}