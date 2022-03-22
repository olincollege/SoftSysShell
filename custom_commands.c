#include <stdio.h>
#include <stdlib.h>
#include "custom_commands.h"
#include "helper_commands.h"
#include <unistd.h>

void hype_me(){
    char name[100];
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Hey %s, you're the best!\n", name);
}

void game(){
    char **my_game_command = malloc(3 * sizeof(char *));
    my_game_command[0] = "python3"; 

    my_game_command[1] = "game/main.py";
    my_game_command[2] = NULL;
    if (execvp(my_game_command[0], my_game_command) < 0) {
        perror(my_game_command[0]);
        exit(1);
    }
    free(my_game_command);
    
}