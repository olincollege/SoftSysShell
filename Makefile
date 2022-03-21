main: helper_commands.o custom_commands.o main.c
	gcc -o main helper_commands.o custom_commands.o main.c -lreadline

helper_commands.o: helper_commands.h helper_commands.c
	gcc helper_commands.c -c

custom_command.o: custom_commands.h custom_commands.c
	gcc custom_commands.c -c