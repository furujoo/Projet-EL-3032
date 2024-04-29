// Projet_EL3032.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <fcntl.h> // for open, O_RDONLY, O_WRONLY
#include <stdio.h> // for printf
#include <sys/stat.h> // for mkfifo
#include <unistd.h> // for read, write
#include <stdlib.h>
#include <string.h>
#include "pipe.h"
#include <stdbool.h>

#define BUFFER_SIZE 256
#define TAILLE_MAX 2000
#define MAX_MOTS 100

//Fonctions qui initialisent des Pipes

void Pipe1111(Pipe *pipe){
    pipe_init(pipe,"PipeSD1111.pipe" , "servRD.pipe" );
}

void Pipe2222(Pipe *pipe){
    pipe_init(pipe,"PipeSD2222.pipe" , "servRD.pipe" );
}




int main(int argc, char *argv[]){

    ////Initialisation des pipe et des variables utilisés////
    Pipe pServD1R, pServD2R;
    
    char buffer[BUFFER_SIZE]="";
    char chaine[]="";

    char mots[TAILLE_MAX][50];
    int nb_mots = 0;

    char mots_menu[TAILLE_MAX][100];
    int nb_mots_menu = 0;

    int result = 0;
    int result2=0;

    char* NumServ = argv[1];
    
    char typeR;
    int CodeServ;
    int CodeLieux;
    int CodeMenu;
    

    bool Erreur = false;
    bool ErreurServ = false;
    bool ErreurLieu = false;
    bool ErreurMenu = false;



  

    ////////////////////////////////////////Serveur 1111///////////////////////////////////////////////////////
    if (atoi(NumServ)==1111){

        // Création du pipe serveur 1111
        Pipe1111(&pServD1R);
        char *toto = pipe_format(&pServD1R);
        printf( "  %s \n", toto);
        free(toto);

        printf("Serveur 1111 \n");

        while(result==0){ //////Lecture en boucle sur le pipe entre le serveur de Routage
            result = pipe_read(&pServD1R, buffer, BUFFER_SIZE);
        }   

        FILE *ListeLieux = fopen("/workspaces/Projet-EL-3032/Base de donnée/ListeLieux1111.txt", "r");   //////Apres lecture du contenu du pipe, on lit le fichier de Lieux qui correspond au serveur
 

        while (fscanf(ListeLieux, "%s", mots[nb_mots]) != EOF) {  /// On stocke chaque mot dans un tableau mots et on compte le nombre de mots présent dans le fichier
            nb_mots++;
            if (nb_mots >= MAX_MOTS) {
                printf("Trop de mots dans le fichier.\n");
                break;
            }
        }
        fclose(ListeLieux);   

    }


////////////////////////////////////////    Serveur 2222    ///////////////////////////////////////////////////////

    else if (atoi(NumServ)==2222){

        Pipe2222(&pServD2R);
        char* toto = pipe_format(&pServD2R);
        printf( "  %s \n", toto);
        free(toto);

        printf("Serveur 2222 \n");



        while(result2==0){
            result2 = pipe_read(&pServD2R, buffer, BUFFER_SIZE);
        }
        
        FILE *ListeLieux = fopen("/workspaces/Projet-EL-3032/Base de donnée/ListeLieux2222.txt", "r");    //////Apres lecture du contenu du pipe, on lit le fichier de Lieux qui correspond au serveur
 
        while (fscanf(ListeLieux, "%s", mots[nb_mots]) != EOF) {       /// On stocke chaque mot dans un tableau mots et on compte le nombre de mots présent dans le fichier
            nb_mots++;
            if (nb_mots >= MAX_MOTS) {
                printf("Trop de mots dans le fichier.\n");
                break;
            }
        }
        fclose(ListeLieux);   
    }

    //////////////////////////////////////// Si Serveur INCONNU///////////////////////////////////////////////////////

    else{   
        Erreur = true;

        printf("Serveur Inconnu veuillez reesayer \n");

        /*
        char MessageErreurS[200] = "";
        snprintf(MessageErreurS, 300, "|%c|R|%d|%d|%d|%s|", NumClient,CodeServ,CodeLieux,CodeMenu,"Erreur: Serveur Inconnu, Veuillez reessayer" );

        printf("%s \n", MessageErreurS); 
        
        */
    }


    /////Lecture des Fichiers et envoie du Menu au Serveur de Routage puis au Client////////////

   

    int elements_lus = sscanf(buffer, "%d|%d|%d", &CodeServ, &CodeLieux, &CodeMenu); ////Parsing du message reçu par le serveur de Routage

    if((CodeServ != 1111) & (CodeServ != 2222)){  
        Erreur = true;   /////On verifie si les codes serveur du Client sont bon 
        
    }

    char NomFichierMenu[50];   
        
    
    for (int i =0; i<nb_mots; i=i+2){      
        if(atoi(mots[i]) == CodeLieux){          //On cherche dans les mots trouvés le Lieu correspondant au Code Lieu du Client     
            strcpy(NomFichierMenu, mots[i+1]);  // Dans notre Fichier, on suit le format suivant. Les élements pair (0,2,4...) correspondent au Code du Lieu et les élements impairs correspondent au Nom du fichier où se trouvent les menu du Lieu
            Erreur = false;  
            ErreurLieu= false;                  //On signale qu'il n'y pas d'erreur
            break;
        }
        else{
            Erreur = true;                      //Si on ne trouve pas de lieu qui correspond au Code du client, on signale une erreur
            ErreurLieu= true;       
        }
    }


    if(Erreur==false){    ////Si il n'y a pas d'erreur , le serveur de Donnée envoie sa réponse au Serveur de Routage

        char chemin[100];
        char Commande[200]="";

        snprintf(chemin, sizeof(chemin), "/workspaces/Projet-EL-3032/Base de donnée/%s", NomFichierMenu); ////On lit le fichier apres avoir recuperer le nom du fichier plus tot et l'avoir stocké dans NomFichierMenu
        FILE *ListeMenu = fopen(chemin, "r");

        while (fscanf(ListeMenu, "%s", mots_menu[nb_mots_menu]) != EOF) {
            
            nb_mots_menu++;
            if (nb_mots_menu >= MAX_MOTS) {
                printf("Trop de mots dans le fichier.\n");
                break;
            }
        }
        
        
        for (int i=0; i<nb_mots_menu; i=i+2){
            
            
            if (atoi(mots_menu[i])==CodeMenu) {  // On vérifie si un element dans le fichier correspond au code Menu donné par le client, si c'est le cas on stock le menu dans la variable Commande
                strcpy(Commande, mots_menu[i+1]); 
                break;     
            }
            else{
                ErreurMenu= true;               //Si on ne trouve rien, on renvoie une erreur au Client
            }
            
        }



       
        if(ErreurMenu == false){
            char Reponse[200]="";
            snprintf(Reponse, 300, "R|%d|%d|%d|%s|",CodeServ,CodeLieux,CodeMenu,Commande );  ///Envoie de la reponse au Client suivant le format du protocole de communication
            printf("La Répônse Envoyée : %s \n", Reponse);

            //envoie du message
            if (atoi(NumServ)==1111){
                pipe_write(&pServD1R, Reponse); 
            }
            else if(atoi(NumServ)==2222){
                pipe_write(&pServD2R, Reponse); 
            }
        }

        else if(ErreurMenu == true) {
            char ErreurMenu[200]="";
            snprintf(ErreurMenu, 300, "R|%d|%d|%d|Le Code du Menu est incorrect|",CodeServ,CodeLieux,CodeMenu );  ///Envoie de la reponse au Client suivant le format du protocole de communication
            printf("La Répônse Envoyée : %s \n", ErreurMenu);
            pipe_write(&pServD1R, ErreurMenu); 

        }
    }




////////////////////////En cas d'erreur de Code Serveur, Code Menu ou Code Lieu, le serveur prépare un message d'erreur selon le type d'erreur ////////////////////////////

    else if (Erreur == true){
        char MessageErreur[300]="";
        char MessageErreurServ[300]="";
        


        if(ErreurServ == true){
            snprintf(MessageErreurServ, 300, "R|%d|%d|%d|Code Serv Inconnu|",CodeServ,CodeLieux,CodeMenu );
            printf("Le code Serveur est inconnu");
            if (atoi(NumServ)==1111){
                pipe_write(&pServD1R, MessageErreurServ);
            }
            else if(atoi(NumServ)==2222){
                pipe_write(&pServD2R, MessageErreurServ);
            }
        }



        if(ErreurLieu == true){ //Si on a une erreur sur le code Lieu envoyé par le client, on le signale
            snprintf(MessageErreur, 300, "R|%d|%d|%d|Code Lieu Inconnu|",CodeServ,CodeLieux,CodeMenu );
            printf("L'Erreur est': %s \n", MessageErreur);
            if (atoi(NumServ)==1111){
                pipe_write(&pServD1R, MessageErreur);
            }
            else if(atoi(NumServ)==2222){
                pipe_write(&pServD2R, MessageErreur);
            }
        }                  
    }
}


    


  
    


