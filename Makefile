CC = gcc
CFLAGS = -Wall -Wextra -g

all : mishell
	@$(CC) $(CFLAGS) -o mishell mishell.c

clean : 
	@rm mishell
