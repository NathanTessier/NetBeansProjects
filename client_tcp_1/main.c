/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 14 octobre 2021, 09:07
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





    int sock;
    int valEnvoyee,valRecue;
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosReception;
    socklen_t taille;
    
    taille = sizeof(infosServeur);
    
    valEnvoyee = 17;
    

    sock = socket(PF_INET,SOCK_STREAM,0);
    if (sock == -1)
    {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }

    infosServeur.sin_family= AF_INET;
    infosServeur.sin_port = htons(5555);  
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.83");
    
    retour = connect(sock,(struct sockaddr *) &infosServeur, taille);
    
    if(retour == -1){
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }
    
    retour = write(sock, &valEnvoyee, sizeof(valEnvoyee)); 

    if(retour == -1){
        printf("pb write : %s\n", strerror(errno));
        exit(errno);
    }
    
    retour = read(sock, &valRecue, sizeof (valRecue));
    
    if(retour == -1){
        printf("pb read : %s\n", strerror(errno));
        exit(errno);
    }
    
    printf("Valeur recue : %d\n",valRecue);
    
    shutdown(sock,SHUT_RDWR);
    close(sock);
    
    return (EXIT_SUCCESS);
}

