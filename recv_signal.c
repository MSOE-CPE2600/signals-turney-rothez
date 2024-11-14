/******************************************************************************
 * @file    recv_signal.c
 * @brief   Sets a signal handler for SIGUSR1, 
 *          upon signal reception, the handler prints the received number
 * Modified by: Zane Rothe
 * CPE 2600-111
 * Lab 10
 * Send number from send_signal program
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig, siginfo_t *info, void *ucontext);

int main() 
{
    struct sigaction myaction; // struct of sigacition options
    myaction.sa_sigaction=signal_handler; // Register function
    myaction.sa_flags=SA_SIGINFO; // Indicate info required
    sigaction(SIGUSR1,&myaction,NULL); // Register signal
    printf("PID: %d\n", getpid()); // show pid for sending program to use
    while (1)
    {
        //Do nothing
    }
    return 0;
}

void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
    // Print pid of process that sent signal
    printf("I received %d\n", (*info).si_value.sival_int);
}