/******************************************************************************
 * @file    signal_segfault.c
 * @brief   Program that dereferences a null pointer causing a seg fault
 * Modified by: Zane Rothe
 * CPE 2600-111
 * Lab 10
 * Brief summary of modifications:
 *  created seg fault signal handler
 *  handler displays that there was a seg fault
 *  program returns to line that causes seg fault; stuck in infinite loop
 *****************************************************************************/


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_segv();

int main (int argc, char* argv[]) {
    
    signal(SIGSEGV,handle_segv); //register handler

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}

// Signal handler for SIGSEGV - prints a message and returns
void handle_segv()
{
    printf("Segmentation Fault\n");
}