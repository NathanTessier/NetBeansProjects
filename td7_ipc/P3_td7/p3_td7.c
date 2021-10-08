/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 7 octobre 2021, 15:30
 */

#include "zone.h"


float randomF() {
    return ((float) 50.0 * (rand() / (RAND_MAX + 0.1)));
}

int randomI() {
    return ((int) 1000.0 * (rand() / (RAND_MAX + 0.1)));
}
typedef struct {
    float temp;
    int press;
    char ordre;
} laStruct;


int main(int argc, char** argv) {

   
    int id;
    key_t key;
    struct donnees lesDonnees;
    


    if ((key = ftok("/tmp/bidon_td7", 5678)) == -1) {
        perror("problème avec ftok\n");
        exit(2);
    }

    id = msgget(key, IPC_CREAT | 0600);
    
    if (id == -1) {
        perror("problème avec msgget\n");
        exit(3);
    }
}