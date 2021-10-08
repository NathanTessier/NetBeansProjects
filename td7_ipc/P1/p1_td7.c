/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 7 octobre 2021, 15:25
 */

#include "zone.h"


float randomF() {
    return ((float) 50.0 * (rand() / (RAND_MAX + 0.1)));
}

int randomI() {
    return ((int) 1000.0 * (rand() / (RAND_MAX + 0.1)));
}



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


    // poussé en continue des valeurs dans la file
    int press;
    float temp;
    
    while (1) {
        
       temp = randomF();
       snprintf(lesDonnees.texte,8,"%.2f",temp);
       lesDonnees.type = 2;
       msgsnd(id,(void *)&lesDonnees,sizeof(lesDonnees),IPC_NOWAIT);
       printf("type : %ld temperature : %s\n",lesDonnees.type,lesDonnees.texte);        
               
               
       press = randomI();       
       snprintf(lesDonnees.texte,8,"%d",press);
       lesDonnees.type = 4;
       msgsnd(id,(void *)&lesDonnees,sizeof(lesDonnees),IPC_NOWAIT);
       printf("type : %ld pression : %s\n",lesDonnees.type,lesDonnees.texte);
      
       sleep(1);
    }

    return (EXIT_SUCCESS);
}