/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 29 septembre 2021, 11:42
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

typedef struct {
    int v1;
    int v2;
    int v3;
} laStruct;

laStruct global;
pthread_mutex_t monMutex = PTHREAD_MUTEX_INITIALIZER;

void *tache1(void *data) {

    laStruct a = *((laStruct *) data);
    pthread_mutex_lock(&monMutex);
    global = a;
    pthread_mutex_unlock(&monMutex);

    int tid = syscall(SYS_gettid);
    printf("Je suis le thread T1 , mon TID est %d a= %d\n", tid, a);
}

void *tache2(void *data) {

    laStruct a = *((laStruct *) data);

    pthread_mutex_lock(&monMutex);
    global = a;
    pthread_mutex_unlock(&monMutex);
    int tid = syscall(SYS_gettid);
    printf("Je suis le thread T2 , mon TID est %d b= %d\n", tid, a);
}

void *tache3(void *data) {

    laStruct a = *((laStruct *) data);
    int tid = syscall(SYS_gettid);
    printf("Je suis le thread T3 , mon TID est %d c= %d\n", tid, a);

    pthread_mutex_lock(&monMutex);
    global = a;
    pthread_mutex_unlock(&monMutex);
    }

int main() {
    int retour;
    void * resultat;
    pthread_t T[3];
    laStruct a = {10, 20, 30};
    laStruct b = {16, 23, 17};
    laStruct c = {7, 29, 11};



    retour = pthread_create(&T[0], NULL, tache1, &a);
    retour = pthread_create(&T[1], NULL, tache2, &b);
    retour = pthread_create(&T[2], NULL, tache3, &c);

    retour = pthread_join(T[0], resultat);
    retour = pthread_join(T[1], resultat);
    retour = pthread_join(T[2], resultat);


    printf("golbal.v1 : %d\nglobal.v2 : %d\nglobal.v3 : %d\n", global.v1, global.v2, global.v3);

    return EXIT_SUCCESS;
}