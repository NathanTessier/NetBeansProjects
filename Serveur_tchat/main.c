
/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 15 octobre 2021, 09:16
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


    int sockFileAtt;
    int sockComClient;
    struct sockaddr_in infoServeur;
    struct sockaddr_in infoClient;
    int retour;
    int taille;
    char msgEnvoye[TAILLE_MAX];
    char msgRecu[TAILLE_MAX];

    printf("le serveur sur le port 5678");

    infoServeur.sin_family = AF_INET;
    infoServeur.sin_port = htons(5678);
    infoServeur.sin_addr.s_addr = htonl(INADDR_ANY);



    sockFileAtt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sockFileAtt == -1) {
        printf("pb socket file attente : %s\n", strerror(errno));
        exit(1);
    }

    retour = bind(sockFileAtt, (struct sockaddr *) &infoServeur, sizeof (infoServeur));

    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(2);
    }

    retour = listen(sockFileAtt, 10);

    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(3);
    }

    taille = sizeof (infoClient);



    sockComClient = accept(sockFileAtt, (struct sockaddr *) &infoClient, &taille);

    if (sockComClient == -1) {
        printf("pb accept : %s\n", strerror(errno));
        exit(4);
    }
    do {

        // reception en provenance du client
        memset(msgRecu, '\0', TAILLE_MAX);
        retour = read(sockComClient, msgRecu, TAILLE_MAX);
        if (retour == -1) {
            printf("pb read : %s\n", strerror(errno));
            exit(errno);
        }
        printf("msg provenant du client :%s\n", msgRecu);
        printf("votre message : ");
        fgets(msgEnvoye, TAILLE_MAX, stdin);
        retour = write(sockComClient, msgEnvoye, strlen(msgEnvoye));
        if (retour == -1) {
            printf("pb write : %s\n", strerror(errno));
            exit(errno);
        }
    } while (strcmp("a+", msgRecu) != 0);
    close(sockComClient);
    close(sockFileAtt);

    return (EXIT_SUCCESS);
}





