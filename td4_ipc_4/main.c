/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 30 septembre 2021, 08:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

// fonction de traitement du signal SIGUSR1

void traitement(int sig) {
    static int cpt = 0;
    cpt++;

    printf("cptt : %d : un signal %d SIGUSR1 ppid :%d\n", cpt, sig, getppid());
}

int main(int argc, char *argv[]) {
    int pid1;
    int pid2;
    int pid3;
    int retour;
    int tube[2];
    int nbOctets = 0;
    char message [255];
    int status;
    char buffer[255];



    pid1 = getpid();
    (void) signal(SIGUSR1, traitement);

    status = pipe(tube);

    
    if (status != 0) {
        printf("Probleme de creation des tubes\n");
        exit(1);
    }

    printf("Père p1 pid =%d\n", pid1);
    pid2 = fork();
    if (pid2 == 0) {
        pid3 = fork();
        if (pid3 == 0) { // p3
            printf("fils p3 sid =%d ppid =%d\n", getpid(), getppid());
            printf("le processus p3 attend un signal\n");
            sprintf(message, "%d\n", getpid());
            pause();
           
            nbOctets = write(tube[1], message, strlen(message));
            printf("Octets ecrit : %d\n", nbOctets);

            printf("Fin de processus p3\n");
            wait(&status);
            
        } else { // p2
            printf("fils p2 sid =%d ppid =%d\n", getpid(), getppid());
            printf("le processus p2 attend un signal\n");
            pause();
            printf("Fin de processus p2\n");

        }
    } else { // p1
         sleep(2);
        
        nbOctets = read(tube[0], buffer, 255);
        printf("Octets lus : %d %s\n", nbOctets, buffer);
        sscanf(buffer,"%d",&pid3);
        printf("p1 envoie un signal a p2\n");
        retour = kill(pid2, SIGUSR1);
        printf("p1 envoie un signal a p3\n");
        retour = kill(pid3, SIGUSR1);
        
        wait(&status);
        printf("Fin de processus p1");


    }
    return EXIT_SUCCESS;
}