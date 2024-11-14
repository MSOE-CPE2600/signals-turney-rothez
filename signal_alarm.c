/******************************************************************************
 * @file    signal_alarm.c
 * @brief   Sets an alarm signal for 5 seconds. 
 *          Upon alarming, the handler prints a message and then quits
 * Modified by: Zane Rothe
 * CPE 2600-111
 * Lab 10
 *****************************************************************************/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void handle_alarm();

int main() 
{
    signal(SIGALRM, handle_alarm); // Register the signal handler
    alarm(5); // Set an alarm for 5 seconds
    printf("Set alarm\n");
    while(1)
    {
        printf("Waiting for alarm...\n"); //wait
        sleep(1);
    }
    return 0;
}

void handle_alarm() //alarm signal handler
{
    printf("Alarm received!\n");
    exit(1);
}