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

void PipeClientServR(Pipe *pipe,char NClient){

    char client= strcat("client",NClient);

    pipe_init(pipe,strcat(client,".pipe"), "servR.pipe" );
    
}


int main(int argc, char *argv[]) ////TO DO Possible aussi de remplacer les noms des pipe dans le pipe init par les argv 
{

////TO DO PLUSIEURS APPLICATIONS CLIENTES : EN GROS TU CHANGES DANS LE PIPE INIT CLIENT.PIPE PAR CLIENT1.PIPE
    
    //testfvnfgngfh
    char buffer[BUFFER_SIZE];
    Pipe pClientServR;
    char *NumClient = argv[1];
    

    

    

    PipeClientServR(&pClientServR,NumClient);

    char *toto = pipe_format(&pClientServR);
    printf( "  %s \n", toto);
    //pipe_write(CLIENT_SERV_TUBE, 'Ping');
    free(toto);


    //scanf("%s",CodeServ);
    //scanf("%s",CodeLieu);
    //scanf("%s",CodeMenu);

   // char message= '|'+CodeServ+'|'+ CodeLieu +'|'+CodeMenu+'|'; 

   

    while(1){

        char* typeR    = argv[2];
        char* CodeServ = argv[3];
        char* CodeLieu = argv[4];
        char* CodeMenu = argv[5];
        
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

        pipe_open_write(&pClientServR);
        pipe_write(&pClientServR,CodeServ);
        //pipe_free(&pClientServR);

        /////Lire sur le PIPE

        ///// UTILISER 2 TERMINAUX UN POUR CLIENT ET L'AUTRE POUR SERVROUT QD ON TEST LES PIPE //////

        int result=0;
        
        while( result==0){
            
            result = pipe_read(&pClientServR, buffer, BUFFER_SIZE);// Utilsier getopt ou juste argc/argv
        }

        printf("Données lu (%d) :%s \n",result, buffer);


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


        


        //int result = pipe_read(&pClientServR, buffer, BUFFER_SIZE);// Utilsier getopt ou juste argc/argv
        //if( result >0){
        //    printf("Données lu (%d) :%s \n",result, buffer);
        //}
       
       usleep(1000);


    }

        

    
    

    //printf("|%s|%s|%s|",CodeServ,CodeLieu,CodeMenu);

    
    

    //test
   
    
   
}