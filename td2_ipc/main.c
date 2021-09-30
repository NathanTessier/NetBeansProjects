/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ntessier
 *
 * Created on 22 septembre 2021, 10:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pid1, pid2;
    char message[255];
    pid_t retourWait;
    int wstatus;
    pid1 = fork(); //p1
    if (pid1 == 0) { //p2
        sprintf(message, "mon pid est %d, le pid de mon pere est %d", getpid(), getppid());
        boite("boite2", message);


    } else {// p1
       
        retourWait
        sprintf(message, "mon pid est %d, le pid de mon pere est %d", getpid(), getppid());
        boite("boite1", message);
    return EXIT_SUCCESS;
}