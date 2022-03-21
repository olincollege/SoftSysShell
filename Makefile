main: command_reader.o custom_commands.o main.c
	gcc -o main command_reader.o custom_commands.o main.c -lreadline

command_reader.o: command_reader.h command_reader.c
	gcc command_reader.c -c

custom_command.o: custom_commands.h custom_commands.c
	gcc custom_commands.c -c