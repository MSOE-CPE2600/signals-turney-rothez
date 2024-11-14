/******************************************************************************
 * @file    signal_handler.c
 * @brief   Sets a signal handler for SIGINT, 
 *          upon signal reception, the handler prints a message and then quits
 * Modified by: Zane Rothe
 * CPE 2600-111
 * Lab 10
 * Brief summary of modifications:
 *  commented out exit(1) in signal handler
 *  signal handler triggered by ctrl+C (sigint)
 *  can kill process from another terminal with $ kill -SIGKILL <pid>
 *  can kill the process with CTRL+Z, whick sends sigkill
 *****************************************************************************/


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void handle_signal();

int main() 
{

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    printf("PID: %d\n",getpid());
    while(1) 
    {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}

// Signal handler for SIGINT - prints a message and returns
void handle_signal() 
{
    printf("Received a signal\n");
    //exit(1);
}