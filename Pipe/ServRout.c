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

void PipeServRoutD1(Pipe *pipe){

    pipe_init(pipe,"servR1.pipe" , "servD1.pipe" );
    
}

void PipeServRoutD2(Pipe *pipe){

    pipe_init(pipe,"servR1.pipe" , "servD2.pipe" );
    
}

void PipeServRClient1(Pipe *pipe){

    pipe_init(pipe,"servR.pipe" , "client1.pipe" );
    
}

void PipeServRClient2(Pipe *pipe){

    pipe_init(pipe,"servR.pipe" , "client2.pipe" );
    
}

int main()  ///Garder les codes envoyés par le client pour pouvoir reconnaitre plus tard à qui renvoyer les données : si les 3 codes sont les meme forcement la reposne sera la meme pour n'importe quel utilisateur
{
    char buffer[BUFFER_SIZE];
    //char message;
    Pipe pServRClient1,pServRClient2, pServRD1, pServRD2;

    PipeServRoutD1(&pServRD1);

    char *toto = pipe_format(&pServRD1);
    printf( "  %s \n", toto);
    //pipe_write("serv.pipe", 'Ping');
    free(toto);

    PipeServRoutD2(&pServRD2);

    char *toto = pipe_format(&pServRD2);
    printf( "  %s \n", toto);
    //pipe_write("serv.pipe", 'Ping');
    free(toto);




    PipeServRClient1(&pServRClient1);

    toto = pipe_format(&pServRClient1);
    printf( "  %s \n", toto);
    //pipe_write("serv.pipe", 'Ping');
    free(toto);


    PipeServRClient2(&pServRClient2);

    toto = pipe_format(&pServRClient2);
    printf( "  %s \n", toto);
    //pipe_write("serv.pipe", 'Ping');
    free(toto);

    //FILE* RoutageF = fopen ( "FichierRoutage.txt", "r+" );
 
    int result =0;
    int resultServD =0;
    

//////////Lecture du Pipe entre le client et le Serveur de Routage////////////////////////

    while(result == 0){
        result = pipe_read(&pServRClient1, buffer, BUFFER_SIZE);
        if (result!=0){

            break;
        }
        else{
            result = pipe_read(&pServRClient2, buffer, BUFFER_SIZE);
        }
        
    }
    
    //pipe_free(&pServRClient)
    printf("Data read (%d bytes): %s\n", result, buffer);
    
    
///////////Envoie de la demande du Client vers le Serveur de Donnée 1 sur le pipe////////////


        pipe_open_write(&pServRD1);
        pipe_write(&pServRD1,buffer);
        //pipe_free(&pServRD);   

////////////ECRITURE SUR SERV DE DONNEE 2/////////////
        pipe_open_write(&pServRD2);
        pipe_write(&pServRD2,buffer);



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



    //if (RoutageF == NULL) {
    //    perror("Error opening FichierRoutage.txt");
    //    exit(EXIT_FAILURE);
    //}

    //while (1) {
    // Read from servR.pipe
    //int result = pipe_read(&pServRClient, buffer, BUFFER_SIZE);

    //if (result > 0) {
     //   printf("Data read (%d bytes): %s\n", result, buffer);

        // Write to FichierRoutage.txt
    ///    if (fwrite(buffer, 1, result, RoutageF) != result) {
    ///        perror("Error writing to FichierRoutage.txt");
    //        exit(EXIT_FAILURE);
      //  }

     //   exit(EXIT_FAILURE);

        // Write to servRD.pipe
        //if (pipe_write(&pServRD, buffer) == -1) {
        //    perror("Error writing to servRD.pipe");
        //    exit(EXIT_FAILURE);
        //}
    //}

    //int fclose (FILE* RoutageF);

}
    
    
    
