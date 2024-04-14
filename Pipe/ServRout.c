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



int main()  ///Garder les codes envoyés par le client pour pouvoir reconnaitre plus tard à qui renvoyer les données : si les 3 codes sont les meme forcement la reposne sera la meme pour n'importe quel utilisateur
{

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

        //printf ("%s", buffer);

        if (result != 0){
            
            char Serveur[BUFFER_SIZE] = "";

            for (int i = 2; i < 6; i++) {
                char temp[2] = {buffer[i], '\0'};
                strcat(Serveur, temp);
            }

            //printf ( "%s", buffer[2]);
            if (strcmp(Serveur, "1111") == 0){
                printf ("Data read (%d bytes): %s\n", result, buffer);
                pipe_open_write(&pServRD1);
                pipe_write(&pServRD1, buffer);

            }

            else if (strcmp(Serveur, "2222") == 0){
                printf ("Data read (%d bytes): %s\n", result, buffer);
                pipe_open_write(&pServRD2);
                pipe_write(&pServRD2,buffer);
            }

            else{
                //pipe_open_write(&pServRClient1);
                //pipe_write(&pServRClient1,"serveur inconnu");
                printf ("%s : serveur inconnu\n", Serveur);
            }

        }
        
        if (resultServD !=0){

            char Client = bufferSD[0];

            char Menu[BUFFER_SIZE] = "";

            for (int i = 1; i < BUFFER_SIZE; i++) {
                char temp[2] = {buffer[i], '\0'};
                strcat(Menu, temp);
            }

            if(Client == 'R'){
                pipe_open_write(&pServRClient1);
                pipe_write(&pServRClient1, Menu);
            }

            if(Client == '2'){
                //pipe_open_write(&pServRClient2);
                //pipe_write(&pServRClient2, Menu);
            }

        }
    }
    
}


/*


////////// Lecture du Pipe entre le client et le Serveur de Routage ////////////////////////

    while(result == 0){
        result = pipe_read(&pServRClient1, buffer, BUFFER_SIZE);
        
        result = pipe_read(&pServRClient2, buffer, BUFFER_SIZE);
    }


    printf("Data read (%d bytes): %s\n", result, buffer);


    FILE* RoutageF = fopen ( "TableDeRoutage.txt", "r+" );
    fwrite(buffer, 1, result, RoutageF);


///////////Envoie de la demande du Client vers le Serveur de Donnée sur le pipe////////////
    //pipe_open_write(&pServRD);
    //pipe_write(&pServRD,buffer);  


//////////Lecture de la reponse du Serveur de donnée sur le pipe///////////////////


    while(resultServD == 0){
        resultServD = pipe_read(&pServRD1, buffer, BUFFER_SIZE);
        if (resultServD!=0){

            break;
        }
        else{
            resultServD = pipe_read(&pServRClient2, buffer, BUFFER_SIZE);
        }
    }
    
    //pipe_free(&pServRClient)
    printf("Data read (%d bytes): %s\n", result, buffer);
    
    

//////////Envoie de le reponse du Serveur de Donnée au Client ////////////////////

    pipe_open_write(&pServRClient1);
    pipe_write(&pServRClient1,buffer);
    //pipe_free(&pServRClient);  

    pipe_open_write(&pServRClient2);
    pipe_write(&pServRClient2,buffer);



 */

    
    
    
