// Projet_EL3032.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <fcntl.h> // for open, O_RDONLY, O_WRONLY
#include <stdio.h> // for printf
#include <string.h>
#include <sys/stat.h> // for mkfifo
#include <unistd.h> // for read, write
#include <stdlib.h>
#include "pipe.h"

#define BUFFER_SIZE 256

#define CLIENT_SERV_TUBE "clientserv.tube"

// Pipe vers le serveur de données 1
void PipeServRoutD1(Pipe *pipe){
    pipe_init(pipe,"servR1.pipe" , "servD1.pipe" ); 
}

// Pipe vers le serveur de données 2
void PipeServRoutD2(Pipe *pipe){
    pipe_init(pipe,"servR1.pipe" , "servD2.pipe" );
}

// Pipe vers le Client 1
void PipeServRClient1(Pipe *pipe){
    pipe_init(pipe,"servR.pipe" , "client1.pipe" );
}

// Pipe vers le Client 2 
void PipeServRClient2(Pipe *pipe){
    pipe_init(pipe,"servR.pipe" , "client2.pipe" );
}



int main()  {

/////////////////// INITIALISATION DES VARIABLES ////////////////////////

    //initialisation de la variable qui stock les messages
    char buffer[BUFFER_SIZE];
    char bufferSD[BUFFER_SIZE];

    //initialisation des pipes
    Pipe pServRClient1,pServRClient2, pServRD1, pServRD2;


    PipeServRoutD1(&pServRD1);
    char *toto = pipe_format(&pServRD1);
    printf( "  %s \n", toto);
    free(toto);

    PipeServRoutD2(&pServRD2);
    toto = pipe_format(&pServRD2);
    printf( "  %s \n", toto);
    free(toto);


    PipeServRClient1(&pServRClient1);
    toto = pipe_format(&pServRClient1);
    printf( "  %s \n", toto);
    free(toto);


    PipeServRClient2(&pServRClient2);
    toto = pipe_format(&pServRClient2);
    printf( "  %s \n", toto);
    free(toto);

    
    int result = 0;
    int resultServD = 0;
    
    
    //changement de methode pour la table de routage, lécture de tout puis des if si infos lu )
    while(1){

        result = pipe_read(&pServRClient1, buffer, BUFFER_SIZE);
        if(result == 0){
            result = pipe_read(&pServRClient2, buffer, BUFFER_SIZE);
        }
        resultServD = pipe_read(&pServRD1, bufferSD, BUFFER_SIZE);
        if (resultServD == 0){
            resultServD = pipe_read(&pServRD2, bufferSD, BUFFER_SIZE);
        }


        if (result != 0){ 
            char Serveur[BUFFER_SIZE] = "";
            for (int i = 2; i < 6; i++) {
                char temp[2] = {buffer[i], '\0'};
                strcat(Serveur, temp);
            }

            
            if (strcmp(Serveur, "1111") == 0){
                printf ("Data read (%d bytes): %s\n", result, buffer);
                pipe_open_write(&pServRD1);
                printf ("Data sent to server 1111 \n");
                pipe_write(&pServRD1, buffer);
            }

            else if (strcmp(Serveur, "2222") == 0){
                printf ("Data read (%d bytes): %s\n", result, buffer); 
                pipe_open_write(&pServRD2);
                printf ("Data sent to server 2222 \n");
                pipe_write(&pServRD2,buffer);
            }

            else{  
                buffer[0]='E';
                printf ("%s : serveur inconnu\n", Serveur);
                char chaine1 = strcat(buffer,"|Serveur Inconnu|");
                
                pipe_write(&pServRClient1,chaine1);
                pipe_write(&pServRClient2,chaine1);
            }
            result = 0;
        }
        
        if (resultServD !=0){
            char Client = bufferSD[1];
            char Menu[BUFFER_SIZE] = "";

            if(Client == '1'){
                printf("Il s'agit du Client 1 \n");
                pipe_write(&pServRClient1, bufferSD);
            }

            else if(Client == '2'){
                printf("Il s'agit du Client 2\n");
                pipe_write(&pServRClient2, bufferSD);
            }
            else{
                printf("Client Inconnu\n");
            }

        }
    }
    
}




    
    
    
