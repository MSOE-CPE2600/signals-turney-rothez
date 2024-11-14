/******************************************************************************
 * @file    send_signal.c
 * @brief   Sends a random number via SIGUSR1, 
 *          user must enter the receiving program's pid as an argument
 * Modified by: Zane Rothe
 * CPE 2600-111
 * Lab 10
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]) 
{
    int recv_pid=atoi(argv[1]); // read receiving programs pid from cmd line
    srand(time(NULL)); // seed random number
    union sigval mysig; // union contains info to send
    mysig.sival_int=rand(); // stage random number to send
    printf("I am sending %d\n",mysig.sival_int);
    sigqueue(recv_pid, SIGUSR1, mysig); //send value via sigusr1
    return 0;
}

