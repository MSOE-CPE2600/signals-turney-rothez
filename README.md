## Repo for Lab Week 10
Complete assignment as assigned.

Note, no make file is provided.  It is suggested you create one to be more efficient building your programs.

# Lab 10: Signals
By Zane Rothe

The purpose of this lab is to research and practice using signals. Signals are used to communicate between processes. C programs can issue and handle these signals in different ways. For example, a program can contian the line `kill(<pid>,SIGKILL)` to kill the process with the entered pid. The user can also issue signals from the command line, with a command like `kill -SIGKILL <pid>`, which performs the same task as the aforementioned programatic command. Each type of signal carries a _disposition_. A disposition determines how a process responds to that signal. The five main signal dispositions are Terminate, Ignore, Core dump, Stop, and Continue. Upon reception of a signal, a program's signal handler function is called, which interprets the incoming signal. This repository contains a few examples of common uses of signals in C programming. 

## signal_handler.c
This program demonstrates the usage of a signal handler. The handler responds to the `SIGINT` signal and modifies the default disposition of terminate. Instead, the program will return to main. This program can either be ended by ctrl+z, shich calls `SIGSTP` (stop disposition) or by issuing `kill -SIGKILL <pid>` which issues the `SIGKILL` signal (terminate disposition).

## signal_alarm.c
This program demonstrates the ability to set timed alarms with signals. An alarm is set for five seconds, after which the `SIGALRM` signal is sent and received. While the defualt disposition of `SIGALRM` is terminate, this program modifies that behavior to simply print a message and return to main.

## signal_segfault.c
This program demonstrates the ability to create a process that is triggered by a segmentation fault, which occurs repeatedly in main. Upon such a fault, the `SIGSEGV` signal is issued. The default disposition is to core dump, however, this program simply will return to main. The program returns to the exact line where the segmentation fault originated, resulting in an endless loop of segmentation faults.

## signal_sigaction.c
This program demonstrates the ability of a program to retreive information about the signal it has just received. Using the `sigaction()` function to register the desired signal, the receiving program has access to a struct contianing information about the sender or other useful items. This program receives `SIGUSR1` and then displays the process id of the sender. The signal can be sent from the command line with `kill -SIGUSR1 <pid>`. It can be observed from the process list that the pid the sender is from 'bash' (command line).

## send_signal.c, recv_signal.c
This program demonstrates the ability of programs to send and receive information: specifically an integer or a pointer. The sending program uses the function `sigqueue()` to send a random integer via `SIGUSR1` to the receiving program, which then employes `sigaction()` to read the received random integer.

## player1.c, player2.c
As an extra exercise to demonstrate the abilities of inter-process communication using signals, these programs play a game of signal table tennis, using a signal as the 'ball'. Player 2 must be run first. Player 1 can than be run with the displayed pid from Player 2 entered as an argument to Player 1. The game will then begin. Player 1 will "serve" the ball to Player 2 via the `SIGUSR1` signal. `sigqueue()` is used to send an integer with the signal, which is incremented each time a player gets the ball. Player 2 receives the signal with `sigaction()` and sends the ball back with `sigqueue()`. This process then repeats. A macro-defined skill level for each player governs the probability that that the player will miss the ball. Player 1 keeps score of the game and serves after every point. Scoring is per table-tennis rules: first to 11 points, win by 2. When the game is over, Player 1 kills Player 2 via `SIGKILL` due to the fact that they are long-time table tennis rivals.




