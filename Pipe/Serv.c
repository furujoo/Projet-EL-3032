// Projet_EL3032.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <fcntl.h> // for open, O_RDONLY, O_WRONLY
#include <stdio.h> // for printf
#include <sys/stat.h> // for mkfifo
#include <unistd.h> // for read, write
#include <stdlib.h>
#include "pipe.h"

#define BUFFER_SIZE 256
#define TAILLE_MAX 1000

//#define CLIENT_SERV_TUBE "clientserv.tube"

//void PipeServDoRout(Pipe pipe){

   
//}






int main()
{
    char buffer[BUFFER_SIZE]="";
    char chaine[TAILLE_MAX]="";
    Pipe pServDR;
    

    FILE *Serv = fopen("/workspaces/Projet-EL-3032/Base de donnée/ListeServer.txt", "r");



    //Initialisation du pipe 

    pipe_init(&pServDR,"servD.pipe" , "servR.pipe" );
    char *toto = pipe_format(&pServDR);
    printf( "  %s \n", toto);
    
     

    //PipeServDoRout(pSR);
    //PipeServClient(pSC);

    while(1){
        int result = pipe_read(&pServDR, buffer, BUFFER_SIZE);// Utilsier getopt ou juste argc/argv
        if( result >0){
            printf("Données lu (%d) :%s \n",result, buffer);
        }
        
        fgets
       
       usleep(1000);

        
        

    }

    //test
    //pipe_init(&p,"serv.pipe" , "client.pipe" );
    //char *toto = pipe_format(&p);
    //printf( "  %s \n", toto);
    //pipe_write(CLIENT_SERV_TUBE, );
    
    free(toto);
}