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


int main(int argc, char *argv[])
{

    
    
    char buffer[BUFFER_SIZE];
    Pipe pClientServR;
    
    

    

    
    PipeClientServR(pClientServR);


    //scanf("%s",CodeServ);
    //scanf("%s",CodeLieu);
    //scanf("%s",CodeMenu);

   // char message= '|'+CodeServ+'|'+ CodeLieu +'|'+CodeMenu+'|'; 

   

    while(1){

        char* typeR    = argv[1];
        char* CodeServ = argv[2];
        char* CodeLieu = argv[3];
        char* CodeMenu = argv[4];
        char* erreur= NULL;
        char* message= NULL;
        if (argc == 6){
            message = argv[5]; //TODO :verifier si y'a pas de caractere invalide genre |
        }

        //sscanf(buffer,"%c|%4c|%4c|%4c|%250[^|]\n", &typeR,&CodeServ, &CodeLieu,&CodeMenu,  code);  //249[^|] : 	Une donnée de type chaîne de caractères, constituée de tous caractères sauf les caractères spécifiés.
       
        //pipe_write(&pClientServR,messageClient);


        //if(typeR == 'D'){
          //  printf("Demande \n");
        //}
        //else if(typeR == 'R'){
          //  printf("Reponse \n");
        //}
        //else if(typeR == 'E'){
         //   printf("Erreur \n");
        //}
        //else{
            
        //}


        if(typeR[0] == 'D'){
            printf("|%c|%d|%d|%d|| \n", typeR[0],atoi(CodeServ),atoi(CodeLieu),atoi(CodeMenu));
        }
        else if(typeR[0] == 'R'){
            printf("|%c|%d|%d|%d|%s| \n", typeR[0],atoi(CodeServ),atoi(CodeLieu),atoi(CodeMenu),message);
        }
        else if(typeR[0] == 'E'){
            printf("|%c|%d|%d|%d|%s| \n", typeR[0],atoi(CodeServ),atoi(CodeLieu),atoi(CodeMenu),erreur);
        }
        else{
            printf("Requete inconnue \n");
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