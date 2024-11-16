CFLAGS=-c -g -Wall -Werror
CC=gcc

all: recv_signal send_signal signal_alarm signal_handler signal_segfault signal_sigaction player1 player2

recv_signal: recv_signal.o
	$(CC) -o recv_signal recv_signal.o

send_signal: send_signal.o
	$(CC) -o send_signal send_signal.o

signal_alarm: signal_alarm.o
	$(CC) -o signal_alarm signal_alarm.o

signal_handler: signal_handler.o
	$(CC) -o signal_handler signal_handler.o

signal_segfault: signal_segfault.o
	$(CC) -o signal_segfault signal_segfault.o

signal_sigaction: signal_sigaction.o
	$(CC) -o signal_sigaction signal_sigaction.o

player1: player1.o
	$(CC) -o player1 player1.o

player2: player2.o
	$(CC) -o player2 player2.o

clean:
	rm -f *.o recv_signal send_signal signal_alarm signal_handler signal_segfault signal_sigaction player1 player2

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

