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


void PipeClient1ServR(Pipe *pipe){
    pipe_init(pipe,"client1.pipe", "servR.pipe" );  
}

void PipeClient2ServR(Pipe *pipe){
    pipe_init(pipe,"client2.pipe", "servR.pipe" ); 
}


int main(int argc, char *argv[]){ 

    char buffer[BUFFER_SIZE];
    Pipe pClient1ServR;
    Pipe pClient2ServR;
    char* NumClient = argv[4];
    

    ////Lecture sur le Pipe selon le numero Client
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
    


    while(1){
        char* CodeServ = argv[1];
        char* CodeLieu = argv[2];
        char* CodeMenu = argv[3];    
        char Demande[200]="";

        snprintf(Demande, 200,"D|%d|%d|%d|%d| \n",atoi(CodeServ),atoi(CodeLieu),atoi(CodeMenu),atoi(NumClient));  ///On ecrit la demande du Client formaté selon le protocole de communication
       

        ////ECRIRE SUR LE PIPE CORRESPONDANT AU NUMERO CLIENT AVEC LE SERVEUR DE ROUTAGE
        if(atoi(NumClient)==1){
            pipe_write(&pClient1ServR,Demande);
        }
        else if (atoi(NumClient)==2){
            pipe_write(&pClient2ServR,Demande);
        }
        else{
            printf("%s \n","Veuillez choisir un numéro Client compris entre 1 et 2");
        }
        

        /////Lire sur le PIPE Avec le serveur de routage pour obtenir la réponse du serveur de donnée

        int result=0;
        
        while(result==0){     ////////Tant que l'application Cliente ne lis rien sur les Pipe, on continue de boucler sur le pipe_read
            if(atoi(NumClient)==1){
                result = pipe_read(&pClient1ServR, buffer, BUFFER_SIZE);
            }
            else if(atoi(NumClient)==2){
                result = pipe_read(&pClient2ServR, buffer, BUFFER_SIZE);
            }        
        }
        printf("Reçu (%d) : %s \n",result, buffer);  ///// Une fois la réponse du Serveur de donnée reçu, on l'affiche au Client   
       usleep(1000);      
    }  
}