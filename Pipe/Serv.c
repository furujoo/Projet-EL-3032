// Projet_EL3032.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <fcntl.h> // for open, O_RDONLY, O_WRONLY
#include <stdio.h> // for printf
#include <sys/stat.h> // for mkfifo
#include <unistd.h> // for read, write
#include <stdlib.h>
#include "pipe.h"

#define BUFFER_SIZE 256
#define TAILLE_MAX 2000

//#define CLIENT_SERV_TUBE "clientserv.tube"

void PipeServDoRout(Pipe *pipe){
    pipe_init(pipe,"servD1.pipe" , "servR1.pipe" );
}

void PipeServDoRout(Pipe *pipe){
    pipe_init(pipe,"servD2.pipe" , "servR1.pipe" );
}




int main()
{
    char *buffer[BUFFER_SIZE];
    char chaine[TAILLE_MAX];
    Pipe pServD1R, pServD2R;
    

    FILE *ListeLieux = fopen("/workspaces/Projet-EL-3032/Base de donnée/ListeLieux.txt", "r");



    ////Initialisation du pipe////

    PipeServDoRout(&pServD1R);
    char *toto = pipe_format(&pServD1R);
    printf( "  %s \n", toto);
    free(toto);

    PipeServDoRout(&pServD2R);
    char *toto = pipe_format(&pServD2R);
    printf( "  %s \n", toto);
    free(toto);
     

     
    if(ListeLieux == NULL) {
        printf("ERREUR : Impossible d'ouvrir le fichier");
        //return 1;
    }
    
    while(fgets(chaine, TAILLE_MAX, ListeLieux) != NULL){
        printf("%s \n", chaine);
    }
        
    fclose(ListeLieux);
    

    printf("test1 \n");

    //PipeServDoRout(pSR);
    //PipeServClient(pSC);

    int result=0;
    char *reponse="rien";
    printf("test2 \n");
    /////////LE SERVEUR LIT LA SORTIE DU PIPE ENTRE LE SERV DE DONNEE ET LE SERV DE ROUTAGE///////////////////
    while(result ==0){
        result = pipe_read(&pServD1R, buffer, BUFFER_SIZE);
        if (result!=0){
            
            break;
        }
        else{
        result = pipe_read(&pServD2R, buffer, BUFFER_SIZE);// Utilsier getopt ou juste argc/argv
        }   
    }
    printf("Données lu (%d) :%s \n",result, buffer);


    printf("test3 \n");
    //////////////////LE SERVEUR ENVOIE SA REPONSE AU SERVEUR DE ROUTAGE////////////////////////////


    printf("test4 \n");



    ///////////////////ECRITURE SUR LES PIPE CORRESPONDANT A CONFIGURER////////////////////////////

    //////ECRITURE SUR LE PIPE SERVEUR 1 VERS SERVEUR ROUTAGE/////
    pipe_open_write(&pServD1R);
    pipe_write(&pServD1R, reponse);
    //pipe_free(&pServDR);

    //////ECRITURE SUR LE PIPE SERVEUR 2 VERS SERVEUR ROUTAGE/////
    pipe_open_write(&pServD2R);
    pipe_write(&pServD2R, reponse);
       
    //usleep(1000);

}

    //test
    //pipe_init(&p,"serv.pipe" , "client.pipe" );
    //char *toto = pipe_format(&p);
    //printf( "  %s \n", toto);
    //pipe_write(CLIENT_SERV_TUBE, );
    
    
