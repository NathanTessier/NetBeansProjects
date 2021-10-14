/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 8 octobre 2021, 09:46
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv) {


    int valEnvoyee, valRecu;
    int sock;
    int retour;

    struct sockaddr_in infosServeur;
    struct sockaddr_in infosReception;
    int taille;

    printf("serveur udp 2222\n");
    taille = sizeof (infosReception);

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(1);
    }

    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(2222); // port dans l'ordre reseau
    infosServeur.sin_addr.s_addr = htons(INADDR_ANY);

    retour = bind(sock, &infosServeur, sizeof (infosServeur));


    if (retour == -1) {
        printf("pb retour : %s\n", strerror(errno));
        exit(2);
    }

    while (1) {
        retour = recvfrom(sock, &valRecu, sizeof (valRecu), 0,
                (struct sockaddr *) &infosReception, &taille);

        if (retour == -1) {
            printf("pb recvfrom : %s\n", strerror(errno));
            exit(3);
        }
        printf("Message du client %s : %d -> %d\n", inet_ntoa(infosReception.sin_addr),
                infosReception.sin_port, valRecu);

        valRecu *= -1;

        retour = sendto(sock, &valRecu, sizeof (valRecu), 0,
                (struct sockaddr *) &infosReception, sizeof (infosReception));

        if (retour == -1) {
            printf("pb sendto : %s\n", strerror(errno));
            exit(4);
        }
    }



    return (EXIT_SUCCESS);
}

