main: command_reader.o main.c
	gcc -g -o main command_reader.o main.c -lreadline


command_reader.o: command_reader.h command_reader.c
	gcc command_reader.c -c