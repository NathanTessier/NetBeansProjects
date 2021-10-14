#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

typedef struct {
    unsigned char jour;
    unsigned char mois;
    unsigned short int annee;
    char jourDeLaSemaine[10]; // le jour en toute lettre
} datePerso;



int main(int argc, char** argv) {
    float valEnvoyee, valRecu;
    float sock;
    float retour;
    struct sockaddr_in infosServeur;
     struct sockaddr_in infosReception;
     socklen_t taille;
     datePerso date_1;
     date_1.annee = 2002;
     date_1.jour = 17;
     date_1.mois = 02;
     strcpy(date_1.jourDeLaSemaine,"Dimanche");
     
     
    //creation socket
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(3333); // port dans l'ordre reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.83");

    //client : envoie un entier
    
    retour = sendto(sock, &date_1, sizeof (date_1), 0, (struct sockaddr *)&infosServeur, sizeof (infosServeur));

    if (retour == -1) {
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno);
    }
    //serveur : affiche l'entier reçu
    //serveur : envoie l'inverse de l'entier
    //client : affiche ce que le serveur a envoyé
    return (EXIT_SUCCESS);
}


