/******************************************************************************
 * @file    player1.c
 * @brief   Player 1 for signal table tennis 
 *          User must enter the receiving program's pid as an argument
 *          This program initializes table tennis game with player 2 program
 *          Define skill level and winning score in the macro
 * Created by: Zane Rothe
 * CPE 2600-111
 * Lab 10
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SKILL 6 // skill level 0-9
#define WIN 11 // score needed to win

void signal_handler(int sig, siginfo_t *info, void *ucontext);

static int score; //scoring variable communicates from handler

int main(int argc, char* argv[]) 
{
    srand(time(NULL)); //seed random number
    struct sigaction myaction; // struct of sigacition options
    myaction.sa_sigaction=signal_handler; // Register function
    myaction.sa_flags=SA_SIGINFO; // Indicate info required
    sigaction(SIGUSR1,&myaction,NULL); // Register signal
    printf("Player 1 PID: %d, skill level %d\n", getpid(),SKILL);
    printf("Welcome to Signal Table Tennis!\n");
    printf("First to %d, win by 2\n",WIN);
    int score1=0; // score for player 1
    int score2=0; // score for player 1

    while (1)
    {
        int recv_pid=atoi(argv[1]); // read receiving programs pid from cmd line
        int ball=0; //set n hits to 0
        union sigval mysig; // union contains info to send
        mysig.sival_int=ball;
        printf("\nScore: Player 1: %d\n       Player 2: %d\n",score1,score2);
        sleep(3);
        printf("I am serving the ball -->\007\n");//%d\n",mysig.sival_int);
        sigqueue(recv_pid, SIGUSR1, mysig); //send value via sigusr1
        score=0;
        while (1)
        {
            pause(); //wait for return signal
            if(score==1) 
            {
                score1++;
                break;
            } 
            else if(score==2) 
            {
                score2++;
                break;
            }
        }
        if ((score1>=WIN)&&((score1-score2)>1))
        {
            printf("\nPlayer 1 wins %d-%d\n",score1,score2);
            kill(recv_pid,SIGKILL);
            break;
        }
        else if ((score2>=WIN)&&((score2-score1)>1))
        {
            printf("\nPlayer 2 wins %d-%d\n",score2,score1);
            kill(recv_pid,SIGKILL);
            break;
        }
    }
    return 0;
}

void signal_handler(int sig, siginfo_t *info, void *ucontext)
{

    sleep(1);
    int ball=(*info).si_value.sival_int;
    int recv_pid=(*info).si_pid; // read receiving programs pid 

    if(ball==-1)
    {
        printf("\nPlayer 2 fault\n");
        score=1;
        return;
    }
    else if (rand()%10>SKILL)
    {
        printf("I received the ball   <--\n");//%d\n", ball);
        sleep(1);
        printf("I missed the ball     --X\n\n");
        sleep(1);
        printf("Player 1 fault\n");
        score=2;
        return;
    }
    printf("I received the ball   <--\n");//%d\n", ball);
    ball++;
    union sigval mysig; // union contains info to send
    mysig.sival_int=ball;
    usleep(1000000+rand()%1000000); //wait random time 1-2s
    printf("I hit the ball        -->\007\n");// %d\n",mysig.sival_int);
    sigqueue(recv_pid, SIGUSR1, mysig); //send value via sigusr1
    return;
}
