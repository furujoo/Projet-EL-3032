// Projet_EL3032.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <fcntl.h> // for open, O_RDONLY, O_WRONLY
#include <stdio.h> // for printf
#include <sys/stat.h> // for mkfifo
#include <unistd.h> // for read, write
#include <stdlib.h>
#include <string.h>
#include "pipe.h"

#define BUFFER_SIZE 256

//#define CLIENT_SERV_TUBE "clientserv.tube"

void PipeClient1ServR(Pipe *pipe){

    //char *client= strcat("client",&NClient);
    //printf("%s",client);
    //printf("%s",strcat(client,".pipe"));


    pipe_init(pipe,"client1.pipe", "servR.pipe" );
    
}

void PipeClient2ServR(Pipe *pipe){

    //char *client= strcat("client",&NClient);
    //printf("%s",client);
    //printf("%s",strcat(client,".pipe"));


    pipe_init(pipe,"client2.pipe", "servR.pipe" );
    
}


int main(int argc, char *argv[]) ////TO DO Possible aussi de remplacer les noms des pipe dans le pipe init par les argv 
{

////TO DO PLUSIEURS APPLICATIONS CLIENTES : EN GROS TU CHANGES DANS LE PIPE INIT CLIENT.PIPE PAR CLIENT1.PIPE
    
    //testfvnfgngfh
    char buffer[BUFFER_SIZE];
    Pipe pClient1ServR;
    Pipe pClient2ServR;
    char* NumClient = argv[5];
    

    

    
    if( atoi(NumClient) == 1){
        PipeClient1ServR(&pClient1ServR);
        char *toto = pipe_format(&pClient1ServR);
        printf( "  %s \n", toto);
       
        free(toto);
    }
    
    else if (atoi(NumClient)==2){
        PipeClient2ServR(&pClient2ServR);
        char *toto = pipe_format(&pClient2ServR);
        printf( "  %s \n", toto);
    
        free(toto);
    }
    

    

    


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
        if (argc == 7){
            message = argv[6]; //TODO :verifier si y'a pas de caractere invalide genre |
        }

        //sscanf(buffer,"%c|%4c|%4c|%4c|%250[^|]\n", &typeR,&CodeServ, &CodeLieu,&CodeMenu,  code);  //249[^|] : 	Une donnée de type chaîne de caractères, constituée de tous caractères sauf les caractères spécifiés.
       
        //pipe_write(&pClientServR,messageClient);

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


        ////ECRIRE SUR LE PIPE
        if(atoi(NumClient)==1){
            pipe_open_write(&pClient1ServR);
            pipe_write(&pClient1ServR,CodeServ);
        }
        else if (atoi(NumClient)==2){
            pipe_open_write(&pClient2ServR);
            pipe_write(&pClient2ServR,CodeServ);

        }
        //pipe_free(&pClientServR);

        /////Lire sur le PIPE


        int result=0;
        
        while(result==0){
            if(atoi(NumClient)==1){
                result = pipe_read(&pClient1ServR, buffer, BUFFER_SIZE);// Utilsier getopt ou juste argc/argv
            }
            else if(atoi(NumClient)==2){
                result = pipe_read(&pClient2ServR, buffer, BUFFER_SIZE);
            }
            
        }

        printf("Données lu (%d) :%s \n",result, buffer);


      


       
       usleep(1000);


    }

        

    
    

    //printf("|%s|%s|%s|",CodeServ,CodeLieu,CodeMenu);

    
    

    //test
   
    
   
}