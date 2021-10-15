/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 15 octobre 2021, 09:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>

#define TAILLE_MAX 255

int main(int argc, char** argv) {
    int sock;
    struct sockaddr_in infoServeur;
    int retour;
    int taille;
    char msgEnvoye[TAILLE_MAX];
    char msgRecu[TAILLE_MAX];

    if (argc!=2)
    {
        printf("Usage : %s IpDuServeur\n",argv[0]);
        exit(EXIT_SUCCESS);
    }
    printf("client de tchat tcp port 5678\n");
    infoServeur.sin_family = AF_INET;
    infoServeur.sin_port = htons(5678);
    infoServeur.sin_addr.s_addr = inet_addr(argv[1]);

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    //demande de connexion au serveur
    retour = connect(sock, (struct sockaddr *) &infoServeur,
            sizeof (infoServeur));
    if (retour == -1) {
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }
    // envoyer donnees au serveur
    do {
        printf("votre message : ");
        fgets(msgEnvoye,TAILLE_MAX,stdin);
        retour = write(sock, msgEnvoye, strlen(msgEnvoye));
        if (retour == -1) {
            printf("pb write : %s\n", strerror(errno));
            exit(errno);
        }
        // reception en provenance du serveur
        memset(msgRecu, '\0', TAILLE_MAX);
        retour = read(sock, msgRecu, TAILLE_MAX);
        if (retour == -1) {
            printf("pb read : %s\n", strerror(errno));
            exit(errno);
        }
        printf("msg provenant du serveur :%s\n", msgRecu);
    } while (strcmp("a+", msgEnvoye) != 0);
    close(sock);

    return (EXIT_SUCCESS);
}
