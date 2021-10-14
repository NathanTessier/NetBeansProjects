/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 14 octobre 2021, 09:13
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

/*
 * 
 */
int main(int argc, char** argv) {

    int sock, sockClient;
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosReception;
    int taille;
    int valeur;


    printf("serveur tcp sur le port 5555\n");

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(1);
    }

    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555);
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);

    retour = bind(sock, &infosServeur, sizeof (infosServeur));

    if (retour == -1) {
        printf("pb retour : %s\n", strerror(errno));
        exit(2);
    }

    retour = listen(sock, 10); // 10 clients maxi en file d'attente
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(3);
    }
    taille = sizeof (infosReception);

    while (1) {
        printf("attente de requetes sur le port 5555\n");
        
        sockClient = accept(sock, &infosReception, &taille);

        retour = read(sockClient, (void *) &valeur, sizeof (valeur));

        if (retour == -1) {
            printf("pb read : %s\n", strerror(errno));
            exit(4);
        }
        printf("Valeur recue : %d\n",valeur);
        valeur *= -1;

        retour = write(sockClient, (void *) &valeur, sizeof (valeur));

        if (retour == -1) {
            printf("pb write : %s\n", strerror(errno));
            exit(5);
        }
        
        
        shutdown(sockClient,SHUT_RDWR);
        close(sockClient);
        
    }
    return (EXIT_SUCCESS);

}
