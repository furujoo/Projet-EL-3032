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
#define TAILLE_MAX 2000
#define MAX_MOTS 100

//#define CLIENT_SERV_TUBE "clientserv.tube"

void Pipe1111(Pipe *pipe){
    pipe_init(pipe,"servD1.pipe" , "servR1.pipe" );
}

void Pipe2222(Pipe *pipe){
    pipe_init(pipe,"servD2.pipe" , "servR1.pipe" );
}




int main(int argc, char *argv[])
{
    Pipe pServD1R, pServD2R;
    ////Initialisation du pipe////
    char buffer[BUFFER_SIZE]="";
    char chaine[TAILLE_MAX]="";

    char mots[TAILLE_MAX][50];
    int nb_mots = 0;

    char mots_menu[TAILLE_MAX][100];
    int nb_mots_menu = 0;

    int result = 0;
    int result2=0;
    //char *reponse = "";

    char* NumServ = argv[1];
    
    char typeR;
    int CodeServ;
    int CodeLieux;
    int CodeMenu;
    int NumClient;

    


    Pipe1111(&pServD1R);
        char *toto = pipe_format(&pServD1R);
        printf( "  %s \n", toto);
        free(toto);


    Pipe2222(&pServD2R);
        toto = pipe_format(&pServD2R);
        printf( "  %s \n", toto);
        free(toto);

    
    if (atoi(NumServ)==1111) {

        printf("Serveur 1111 \n");

        



        FILE *ListeLieux = fopen("/workspaces/Projet-EL-3032/Base de donnée/ListeLieux.txt", "r");
 

        while (fscanf(ListeLieux, "%s", mots[nb_mots]) != EOF) {
            nb_mots++;
            if (nb_mots >= MAX_MOTS) {
                printf("Trop de mots dans le fichier.\n");
                break;
            }
        }

/*
        for (int i = 0; i < nb_mots; i++) {
            printf("Mot %d : %s\n", i+1, mots[i]);
        }
*/
        fclose(ListeLieux);
    
        while(result==0){
            result = pipe_read(&pServD1R, buffer, BUFFER_SIZE);
        }

        //printf("buffer : %s \n", buffer);
        

        int elements_lus = sscanf(buffer, "%c|%d|%d|%d|%d", &typeR,&CodeServ, &CodeLieux, &CodeMenu,&NumClient);

        //printf("nombres d'elements lus : %d\n  TypeR : %c \n, Code Serv : %d \n, Code Lieux : %d \n, Code Menu : %d \n",elements_lus,typeR, CodeServ,CodeLieux,CodeMenu);

        

        int nombre_mots = sizeof(mots)/sizeof(mots[0]);
        
        char NomFichierMenu[50]="t";

        printf("nombre d'element dans mots : %d\n", nombre_mots);
        printf("nombre de mots : %d\n", nb_mots);

        for (int i =0; i<nb_mots; i=i+2){
            
            if(atoi(mots[i]) == CodeLieux){  
                strcpy(NomFichierMenu, mots[i+1]);
            }
            //else{
             //   strcpy(NomFichierMenu, "Inconnu");
            //}
        }

        printf("Le nom du fichier est %s \n", NomFichierMenu);
        printf("test6 \n");
        

        //char chemin = "/workspaces/Projet-EL-3032/Base de donnée/";


        //FILE *ListeMenu = fopen(fichierMenu, "r");
        printf("test5 \n");

        //char* chemin = strcat(,NomFichierMenu);

        FILE *ListeMenu = fopen("/workspaces/Projet-EL-3032/Base de donnée/Esiee.txt", "r");

        printf("test3 \n");
        while (fscanf(ListeMenu, "%s", mots_menu[nb_mots_menu]) != EOF) {
            
            nb_mots_menu++;
            if (nb_mots_menu >= MAX_MOTS) {
                printf("Trop de mots dans le fichier.\n");
                break;
            }
        }
        printf("nombre de mots menu: %d\n", nb_mots_menu);
        
    
        int nombre_mots_menu = sizeof(mots_menu)/sizeof(mots_menu[0]);

        printf("nombre d'element ds tableau mots menu: %d\n", nombre_mots_menu);



        

        for (int i =1; i<nb_mots_menu; i=i+2){
            
             pipe_write(&pServD1R, strcat(NumClient ,mots_menu[i])); 
        }
        
        
        

    }




    else if (atoi(NumServ)==2222){


        printf("Serveur 2222 \n");
        

        while(result2 ==0){
            result2 = pipe_read(&pServD2R, buffer, BUFFER_SIZE);
        }
        
        int elements_lus = sscanf(buffer, "%c|%d|%d|%d|", &typeR,&CodeServ, &CodeLieux, &CodeMenu);

        //pipe_write(&pServD2R, "qqchose");
    }

    else{
        printf("Serveur de données inconnu, veuillez ressayer");
        
        }


}


    


  
    


    

   /*

    while(1)
    {
        result = pipe_read(&pServD1R, buffer, BUFFER_SIZE);

        if (result==0){
            result = pipe_read(&pServD2R, buffer, BUFFER_SIZE);
        }

        //printf("Buffer : %s \n", buffer);
        // Utilisation de sscanf pour extraire les éléments de la chaîne
        int elements_lus = sscanf(buffer, "%c %d %d %d", &typeR,&CodeServ, &CodeLieux, &CodeMenu);

        //printf("Elements lus: %d \n", elements_lus);

        if (result != 0){
            pipe_write(&pServD1R, "R Menu le costaud ");
        }
    }

}
*/

    /*
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
    */

