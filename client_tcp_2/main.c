/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 14 octobre 2021, 09:10
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>


int main(int argc, char** argv) {

    int sock;
    float valEnvoyee,valRecue;
    int retour;
    struct sockaddr_in infosServeur;
    socklen_t taille;
    
    taille = sizeof(infosServeur);
    
    valEnvoyee = 3.14;
    

    sock = socket(PF_INET,SOCK_STREAM,0);
    if (sock == -1)
    {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }

    infosServeur.sin_family= AF_INET;
    infosServeur.sin_port = htons(6666);
    
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.150");
    
    retour = connect(sock,(struct sockaddr *) &infosServeur, taille);
    
    if(retour == -1){
        printf("pb write : %s\n", strerror(errno));
        exit(errno);
    }
    
    retour = write(sock, &valEnvoyee, taille); 

    if(retour == -1){
        printf("pb write : %s\n", strerror(errno));
        exit(errno);
    }
    
    retour = read(sock, &valRecue, 512);
    
    if(retour == -1){
        printf("pb read : %s\n", strerror(errno));
        exit(errno);
    }
            
    printf("valeur reçue : %f", valRecue);

    
    return (EXIT_SUCCESS);
}

