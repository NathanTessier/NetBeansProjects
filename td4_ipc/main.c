/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 29 septembre 2021, 11:10
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    int pid1, pid2;
    int tube[2];
    int tubeRetour[2];
    int nbOctets = 0;
    char buffer [255];
    int status, status2;
    char message[] = "\nCoucou mon pere\n";
    char reponse[] = "\nMessage bien recu\n";

    pid1 = getpid();
    status = pipe(tube);
    
    status2 = pipe(tubeRetour);
    if (status == !0 || status2 == !0) {
        printf("Probleme de creation des tubes");
        exit(1);
    }
    if (pipe(tube) == 0) {
        pid2 = fork();

        if (pid2 == 0) {
            //fils
            sleep(2);
            nbOctets = read(tube[0], buffer, 255);
            printf("Octets lus : %d %s\n", nbOctets, buffer);
            nbOctets = write(tube[1], reponse, strlen(reponse));
            printf("Octets ecrit : %d\n", nbOctets);

        } else {
            //pere
            sleep(2);
            nbOctets = write(tube[1], message, strlen(message));
            printf("Octets ecrit : %d\n", nbOctets);
            nbOctets = read(tube[0], buffer, 255);
            printf("Octets lus : %d %s\n", nbOctets, buffer);
            wait(&status);
        }

    }
    return 0;
}