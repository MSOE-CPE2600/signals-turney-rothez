/******************************************************************************
 * @file    signal_sigaction.c
 * @brief   Sets a signal handler for SIGUSR1, 
 *          upon signal reception, the handler prints the senser's pid
 * Modified by: Zane Rothe
 * CPE 2600-111
 * Lab 10
 * Send signal with $ kill -SIGUSR1 <pid>
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
    printf("PID: %d\n", getpid());
    while (1)
    {
        //Do nothing
    }
    return 0;
}

void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
    // Print pid of process that sent signal
    printf("Signal sent by process %d\n", (*info).si_pid);
}