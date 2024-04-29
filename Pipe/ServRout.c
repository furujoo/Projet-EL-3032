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

/////////////////// INITIALISATION /////////////////////////////////////////////////////////////////

    //initialisation de la variable qui stock les messages
    char buffer[BUFFER_SIZE];
    char buffersd[BUFFER_SIZE];



    //////////////////////////// INITIALISATION DES PIPES /////////////////////////////////////



    //////////////////// INITIALISATION DES PIPES SERVEURS ////////////////////

    char serveur[TAILLE_MAX][50];  //liste des serveur  
    int nb_serv =0; //NOMBRE DE SERVEUR
    
    //ouverture du fichier liste des serveur
    FILE *ListeServ = fopen("../BaseDeDonnee/liste_des_serveurs.txt", "r");
    
    
    //remplissage de la liste des serveur
    while (fscanf(ListeServ, "%s", serveur[nb_serv]) != EOF) {
        nb_serv++;
        if (nb_serv >= MAX_MOTS) {
            printf("Trop de mots dans le fichier.\n");
            break;
        }
    }
    printf("Nombre de serveur : %d\n", nb_serv);


    
    Pipe PipeSD[nb_serv];
    //Création des pipes serveurs, en fonction des serveurs du fichier : la liste des serveur
    for (int i = 0; i < nb_serv; i++){
        
        char nomPipe[50]= "PipeSD";
        strcat(nomPipe, serveur[i]);
        strcat(nomPipe, ".pipe");

        pipe_init(&PipeSD[i+1], "servRD.pipe", nomPipe);
            char *toto = pipe_format(&PipeSD[i+1]);
            printf( "  %s \n", toto);
            free(toto);
        
    }
    printf("  name_in : %s\n", PipeSD[2].name_out);






    /////////////////// INITIALISATION DES PIPES CLIENT /////////////////
    
    int nb_client = atoi(argv[1]);
    
    printf("Nombre de client : %d\n", nb_client);
    
    Pipe PipeC[nb_client];
    
    // création des pipes clients en fonction de l'argument passé en paramètre
    for (int i = 0; i < nb_client; i++){

        //char numCLient [TAILLE_MAX] = "";
        //sprintf(numCLient, "%d", i);
        
        
        char NomPipeC[30];
        //strcat(nomPipeC, numCLient);
        sprintf(NomPipeC, "PipeClient%d.pipe", i+1);

        pipe_init(&PipeC[i],"servRC.pipe" , NomPipeC);
        char *toto = pipe_format(&PipeC[i]);
        printf( " %s \n", toto);
        free(toto);

    }
    
    printf("  name_in : %s\n", PipeC[0].name_out);


    int result = 0;
    int resultsd = 0;

    char TableRoutage[50][BUFFER_SIZE];
    char Commande [30];






    /////////////////// BOUCLE SUR LES PIPES /////////////////////


    //changement de methode pour la table de routage, lécture de tout puis des if si infos lu )
    while(1){

       
        for (int i =0; i<nb_client; i++){
            result = pipe_read(&PipeC[i], buffer, BUFFER_SIZE);
            


            /////  Message d'un client reçu  //////
            if(result !=0){ 


                /// on le place das la table de routage : tableau à double dimension ///
                for (int i = 0; i < 50; i++) { //on parcours la table
                    
                    //dés qu'un élément est vide on place le message
                    if (TableRoutage[i][0] == '\0'){ 
                        
                        // on insere buffer dans la table jusqu'à ce que buffer[k] soit vide
                        for (int j = 0; j < strlen(buffer); j++) { 
                                for (int k = 2; buffer[k] !=0; k++, j++) {
                                    TableRoutage[i][j] = buffer[k];
                                    Commande [j] = buffer[k];
                                }     
                        }
                    Commande[14]= '\0';
                    Commande[15]= '\0';
                    Commande[16]= '\0';

                    break;// Terminer la boucle après avoir inséré le tableau 
                    }
                }//remplissage table routage
                

                // on afficher la table de routage
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
                        pipe_write(&PipeSD[serv+1], Commande);
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

            /////  Message d'un serveur de donnée  //////
            if(resultsd !=0){ 

                
                //on retire de la table de routage la commande 
                for (int i = 0; i < 50; i++) {
                    if (strncmp(buffersd+2, TableRoutage[i], 14) == 0) {

                        // Si les chaînes sont égales, on afficher le numéro client et supprimer la chaîne du tableau
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

    
    
    
