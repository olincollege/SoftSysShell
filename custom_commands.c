#include <stdio.h>
#include <stdlib.h>
#include "custom_commands.h"
#include "command_reader.h"
#include <unistd.h>

// char *a = "python";
// my_game_command[0] = a;
// my_game_command[1] = "game/test.py"; 
void hype_me(){
    char name[100];
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Hey %s, you're the best!\n", name);
}

void game(){
    // printf("Hey!\n");
    char **my_game_command = malloc(8 * sizeof(char *));
    my_game_command[0] = "python3";
    my_game_command[1] = "game/main.py"; 
    // printf("Hey!\n");
    if (execvp(my_game_command[0], my_game_command) < 0) {
        perror(my_game_command[0]);
        exit(1);
    }
    free(my_game_command);
}