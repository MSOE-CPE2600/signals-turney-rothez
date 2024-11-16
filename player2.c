/******************************************************************************
 * @file    player2.c
 * @brief   Player 2 for signal table tennis 
 *          User must initialize this prgram first
 *          This program receives and sends a signal with player 1 program
 *          Define skill level in the macro
 * Created by: Zane Rothe
 * CPE 2600-111
 * Lab 10
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#define SKILL 6 // skill level 0-9

void signal_handler(int sig, siginfo_t *info, void *ucontext);

int main() 
{
    srand(time(NULL)); //seed random number
    struct sigaction myaction; // struct of sigacition options
    myaction.sa_sigaction=signal_handler; // Register function
    myaction.sa_flags=SA_SIGINFO; // Indicate info required
    sigaction(SIGUSR1,&myaction,NULL); // Register signal SIGUSR1
    printf("Player 2 PID: %d, skill level %d\n", getpid(),SKILL); // show pid
    printf("Welcome to Signal Table Tennis!\n");

    while (1)
    {
        pause(); //wait for next signal
    }
    return 0;
}

void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
    int recv_pid=(*info).si_pid; // read sending programs pid 
    int ball=(*info).si_value.sival_int+1; //ball is the nth hit
    sleep(1);
    if (ball==1) //first hit in volley
    {
        printf("\n");
    }
    printf("I received the ball   <--\n");
    usleep(1000000+rand()%1000000); //wait random time 1-2s
    if (rand()%10>SKILL) // if player 2 fault
    {
        printf("I missed the ball     --X\n");
        ball=-1;
    }
    else // successfully returned ball
    {
        printf("I hit the ball        -->\007\n");
    }
    union sigval mysig; // union contains info to send
    mysig.sival_int=ball; // set ball to nth hit
    sigqueue(recv_pid, SIGUSR1, mysig); //send value via sigusr1 back
}

