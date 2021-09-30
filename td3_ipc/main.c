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

    pid1 = getpid();
    (void) signal(SIGUSR1, traitement);

    printf("Père p1 pid =%d\n", pid1);
    pid2 = fork();
    if (pid2 == 0) {
        pid3 = fork();
        if (pid1 == 0) {
            printf("fils p1 sid =%d ppid =%d\n", getpid(), getppid());

            printf("p1 envoie un signal urs1 à p3\n");
            retour = kill(pid3, SIGUSR1);
            if (retour != 0) {
                printf("Erreur avec kill");

            }
            printf("le processus p3 attend un signal");
            pause();
            printf("Fin de procssus p3\n");
        } else {
            printf("fils p2 sid =%d ppid =%d\n", getpid(), getppid());
            printf("le processus p2 attend un signal sigusr1");

            pause();
            printf("p2 envoie un signal urs1 à p1\n");
            retour = kill(pid1, SIGUSR1);
            if (retour != 0) {
                printf("Erreur avec kill");

            }
            printf("le processus p2 envoie a p3\n");
            retour = kill(pid3, SIGUSR1);
            if (retour != 0) {
                printf("Erreur avec kill");

            }
            printf("le processus p2 envoie a p3\n");
            retour = kill(pid3, SIGUSR1);
            if (retour != 0) {
                printf("Erreur avec kill");

            }
            printf("fin de p2\n");

        }
    } else {
        printf("Le processus p1 attend un signal sigusr1\n");
        pause();
        printf("p1 envoie un signal a p2\n");
        retour = kill(pid2,SIGUSR1);
        printf("p1 attend un deuxieme signal sigusr1\n");
        pause();
        printf("");
        

    }
}