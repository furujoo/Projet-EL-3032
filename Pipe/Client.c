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


int main()
{
    //char buffer[BUFFER_SIZE];
    Pipe p;
    char CodeServ[3];
    char CodeLieu[3];
    char CodeMenu[3];
    

    scanf("Veuillez saisir le code du Serveur :%s",CodeServ);
    scanf("Veuillez saisir le code du Lieu :%s",CodeLieu);
    scanf("Veuillez saisir le code du Menu :%s",CodeMenu);

    //printf("|%s|%s|%s|",CodeServ,CodeLieu,CodeMenu);

    
    

    //test
    pipe_init(&p,"client.pipe" , "serv.pipe" );
    char *toto = pipe_format(&p);
    printf( "  %s \n", toto);
    //pipe_write(CLIENT_SERV_TUBE, 'Ping');
    
    free(toto);
}