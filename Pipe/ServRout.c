// Projet_EL3032.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <fcntl.h> // for open, O_RDONLY, O_WRONLY
#include <stdio.h> // for printf
#include <string.h>
#include <sys/stat.h> // for mkfifo
#include <unistd.h> // for read, write
#include <stdlib.h>
#include <stdarg.h>
#include "pipe.h"

#define BUFFER_SIZE 256
#define TAILLE_MAX 2000
#define MAX_MOTS 100


int main(int argc, char *argv[])  ///Garder les codes envoyés par le client pour pouvoir reconnaitre plus tard à qui renvoyer les données : si les 3 codes sont les meme forcement la reposne sera la meme pour n'importe quel utilisateur
{

//////////////////////////////////////////////////// INITIALISATION /////////////////////////////////////////////////////////////////

     ///////////////////////////////////////// Liste des serveurs /////////////////////////////////////////////////


    char serveur[TAILLE_MAX][50];  //liste des serveur  
    int nb_serv =0; //NOMBRE DE SERVEUR
    
    //ouverture du fichier liste des serveur
    FILE *ListeServ = fopen("../BaseDeDonnee/liste_des_serveurs.txt", "r");
    
    
    //remplissage de la liste des serveur mot par mot 
    while (fscanf(ListeServ, "%s", serveur[nb_serv]) != EOF) {
        nb_serv++;
        if (nb_serv >= MAX_MOTS) {
            printf("Trop de mots dans le fichier.\n");
            break;
        }
    }
    printf("\nNombre de serveur dispo : %d\n", nb_serv);




    ///////////////////////////////////////// PIPES ///////////////////////////////////////////////////////////


    //////////////////////////////////// PIPES SERVEURS ////////////////////////////////
    
    Pipe PipeSD[nb_serv];        //tableau de Struture de pipe pour les multiples pipe serveurs 

    //Création des pipes serveurs, en fonction des serveurs du fichier : la liste des serveur
    for (int i = 0; i < nb_serv; i++){
        
        // création de la syntax
        char nomPipe[50]= "PipeSD";
        strcat(nomPipe, serveur[i]);
        strcat(nomPipe, ".pipe");

        //initialisation
        pipe_init(&PipeSD[i+1], "servRD.pipe", nomPipe);
            char *toto = pipe_format(&PipeSD[i+1]);
            printf( "  %s \n", toto);
            free(toto);

    }


    ///////////////////////////////////// PIPES CLIENTS /////////////////////////////////////
    
    int nb_client = atoi(argv[1]);          // on récupère le nombre de client en argument
    printf("Nombre de client : %d\n", nb_client);
    

    Pipe PipeC[nb_client];      //Idem, tableau de Struture de pipe pour les multiples pipes client 
    
    // création des pipes clients en fonction de l'argument passé en paramètre
    for (int i = 0; i < nb_client; i++){        
        
        //syntaxe
        char NomPipeC[30];
        sprintf(NomPipeC, "PipeClient%d.pipe", i+1);

        //initialisation
        pipe_init(&PipeC[i],"servRC.pipe" , NomPipeC);
        char *toto = pipe_format(&PipeC[i]);
        printf( " %s \n", toto);
        free(toto);

    }
    
    //////////////////////////////////// Variable de stockage ////////////////////////////////////

    char buffer[BUFFER_SIZE]="";
    char buffersd[BUFFER_SIZE]="";

    int result = 0;
    int resultsd = 0;

    char TableRoutage[50][BUFFER_SIZE];
    char Commande [30];



    /////////////////////////////////////////////// BOUCLE SUR LES PIPES /////////////////////////////////////////////////


    while(1){
       
        /// Boucle lecture pipe client ///
        for (int i =0; i<nb_client; i++){
            result = pipe_read(&PipeC[i], buffer, BUFFER_SIZE);
            

            /////  Message d'un client reçu  //////
            if(result !=0){ 


                /// on le place dans la table de routage : tableau à double dimension ///
                for (int i = 0; i < 50; i++) { //on parcours la table
                    
                    //dés qu'une ligne est vide on place le message
                    if (TableRoutage[i][0] == '\0'){ 
                        
                        // on insere buffer dans la table jusqu'à ce que buffer[k] soit vide
                        for (int j = 0; j < strlen(buffer); j++) { 
                                for (int k = 2; buffer[k] !=0; k++, j++) {      // on démare k à 2 car on ne veut pas prendre en compte la lettre et la première barre de la commande
                                    TableRoutage[i][j] = buffer[k];
                                    Commande [j] = buffer[k];       // on remplit parrallelement la chaine de commande finale à envoyer
                                }     
                        }

                    // Partie un peu brute du code, le but est de supprimer le num client de la commande. Le mieux aurait été de récup la commande et de compléter un numero client directement dans le serveur de routage
                    Commande[14]= '\0';
                    Commande[15]= '\0';
                    Commande[16]= '\0';

                    break;// Terminer la boucle après avoir inséré le tableau 
                    }

                }//remplissage table routage
                

                // on affiche la table de routage
                for (int i = 0; i < BUFFER_SIZE && TableRoutage[i][0] != '\0'; i++) {

                    for (int j = 0; j < BUFFER_SIZE && TableRoutage[i][j] != '\0'; j++) {
                        printf("%c", TableRoutage[i][j]);
                    }
                    printf("\n");
                }

                printf("%s\n", Commande);
                
                //isoler le code serveur
                char Serveur[BUFFER_SIZE] = "";    
                for (int i = 0; i < 4; i++) {
                    char temp[2] = {Commande[i], '\0'};
                    strcat(Serveur, temp);
                }

                //initialisation de la variable qui identifie le serveur
                int m=0;
                int serv = 0;
                while (serv < nb_serv){
                    if (strcmp(serveur[serv], Serveur) == 0 ){              
                        pipe_write(&PipeSD[serv+1], Commande);   // on envoie la commande au bon pipe serveur 
                        m=1;
                    }
                    serv++;
                }

                if (m==0){
                    printf("serveur introuvable");
                }


            }//// Fin message client reçu ////
                    
        } /// Fin Boucle lecture pipe client ///




        //////// LECTURE SERVEUR DE DONNÉE ///////

        for (int i = 1; i<= nb_serv; i++){
            resultsd = pipe_read(&PipeSD[i], buffersd, BUFFER_SIZE);

            ///////  Message d'un serveur de donnée  //////
            if(resultsd !=0){ 

                
                //on retire de la table de routage la commande 
                for (int i = 0; i < 50; i++) {
                    if (strncmp(buffersd+2, TableRoutage[i], 14) == 0) {

                        // Si les chaînes sont égales, on affiche le numéro client et supprimer la chaîne du tableau
                        printf("La chaîne %s \n", buffersd+2);

                        char NumClient = TableRoutage[i][15]; // Récupération du numéro client à l'indice k+1
                        printf("%c\n", NumClient);

                        // Supprimer la chaîne du tableau
                        for (int j = i; j <  49; j++) {
                            for (int k =0; k<= 16; k++){
                                TableRoutage[j][k]= TableRoutage[j+1][k];
                            }
                        }
                        printf("%s yes\n", TableRoutage[i]);
                        

                        int NumC = NumClient -'0';
                        printf("%d\n", NumC);

                        pipe_write(&PipeC[NumC-1], buffersd);
                        
                    }
                }

                
            }
        }
    }
        
}

    
    
    
