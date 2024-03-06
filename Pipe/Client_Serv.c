// Projet_EL3032.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <fcntl.h> // for open, O_RDONLY, O_WRONLY
#include <stdio.h> // for printf
#include <sys/stat.h> // for mkfifo
#include <unistd.h> // for read, write


#define BUFFER_SIZE 256

#define CLIENT_TUBE "client.tube"

#define SERV_ROUT_TUBE "servRoutage.tube"

int main()
{
    char buffer[BUFFER_SIZE];


    ////Création du pipe nommé Client-ServeurRoutage////

    int result = mkfifo(SERV_ROUT_TUBE, 0777);
    if (result != 0) {
        printf("Ne peut créé ’%s’\n", SERV_ROUT_TUBE);
        return 0;
    }

    // Creation du second pipe nommé
    result = mkfifo(CLIENT_TUBE, 0777);
    if (result != 0) {
        printf("Ne peut créé ’%s’\n", CLIENT_TUBE);
        return 0;
    }
    // Ouverture en lecture du premier pipe
    int fd_in = open(SERV_ROUT_TUBE, O_RDONLY);
    if (fd_in == -1) {
        printf("Ne peut ouvrir ’%s’\n", SERV_ROUT_TUBE);
        return 0;
    }


    // Lecture bloquante sur le premier pipe
    result = read(fd_in, buffer, BUFFER_SIZE);
    if (result < 0) {
        printf("Ne peut lire ’%s’\n", SERV_ROUT_TUBE);
        return 0;
    }


    printf("Reçu: ’%s’\n", buffer);


    // Ouverture en écriture du second pipe
    int fd_out = open(CLIENT_TUBE, O_WRONLY);
    if (fd_out == -1) {
        printf("Ne peut ouvrir ’%s’\n", CLIENT_TUBE);
        return 0;
    }
    // Écriture sur le second pipe
    result = write(fd_out, buffer, result);
    if (result < 0) {
        printf("Ne peut écrire ’%s’\n", CLIENT_TUBE);
        return 0;
    }

}