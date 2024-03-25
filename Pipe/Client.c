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

void PipeClientServR(Pipe pipe){

    pipe_init(&pipe,"client.pipe" , "servR.pipe" );
    char *toto = pipe_format(&pipe);
    printf( "  %s \n", toto);
    //pipe_write(CLIENT_SERV_TUBE, 'Ping');
    free(toto);
}


int main()
{
    char buffer[BUFFER_SIZE];
    Pipe pClientServR;
    
    char CodeServ[4];
    char CodeLieu[4];
    char CodeMenu[4];

    char messageClient="Ping"; 
    PipeClientServR(pClientServR);


    scanf("%s",CodeServ);
    scanf("%s",CodeLieu);
    scanf("%s",CodeMenu);

   // char message= '|'+CodeServ+'|'+ CodeLieu +'|'+CodeMenu+'|'; 

   

    while(1){
        char typeR, code,erreur;

        sscanf(buffer,"%c|%4c|%4c|%4c|%249[^|]\n", &typeR,&CodeServ, &CodeLieu,&CodeMenu,  code);  //249[^|] : 	Une donnée de type chaîne de caractères, constituée de tous caractères sauf les caractères spécifiés.
       
        //pipe_write(&pClientServR,messageClient);


        if(typeR == 'D'){
            printf("Demande \n");
        }
        else if(typeR == 'R'){
            printf("Requete \n");
        }
        else if(typeR == 'E'){
            pritnf("Erreur \n");
        }
        else{
            printf("Requetes inconnu \n");
        }


        if(typeR == 'D'){
            printf("|%c|%c|%c|%c|| \n", typeR,CodeServ,CodeLieu,CodeMenu);
        }
        else if(typeR == 'R'){
            printf("|%c|%c|%c|%c|%c| \n", typeR,CodeServ,CodeLieu,CodeMenu,code);
        }
        else if(typeR == 'E'){
            printf("|%c|%c|%c|%c|%c| \n", typeR,CodeServ,CodeLieu,CodeMenu,erreur);
        }


        int result = pipe_read(&pClientServR, buffer, BUFFER_SIZE);// Utilsier getopt ou juste argc/argv
        if( result >0){
            printf("Données lu (%d) :%s \n",result, buffer);
        }
       
       usleep(1000);


    }

        

    
    

    //printf("|%s|%s|%s|",CodeServ,CodeLieu,CodeMenu);

    
    

    //test
   
    
   
}