
/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 30 septembre 2021, 16:47
 */

#include <sys/types.h> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <errno.h> 
#include <time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>
#include <sys/ipc.h>
#include <string.h>

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

    laStruct *mesure;
    int id;
    key_t key;


    if ((key = ftok("/tmp/bidon", 1234)) == -1) {
        perror("problème avec ftok\n");
        exit(2);
    }

    id = shmget(key, sizeof ( mesure), IPC_CREAT | 0600);
    
    if (id == -1) {
        if (errno != EEXIST) {
            printf("pb memoire partagée : %s\n", strerror(errno));
            exit(errno);
        }
        
    }

    // attribution 

    mesure = (struct laStruct *) shmat(id, NULL, SHM_W);
    if (mesure == NULL) {
        perror("probleme ave shmat\n");
        exit(1);
    }

    // ecriture en continue

    while (1) {
        mesure->temp = randomF();
        mesure->press = randomI();
        printf("temp : %.2f press : %d\n", mesure->temp, mesure->press);
        sleep(1);

    }

    return (EXIT_SUCCESS);
}