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
    // char **python_install = malloc(8 * sizeof(char *));
    // char **pip_install = malloc(8 * sizeof(char *));
    // char **pygame_install = malloc(8 * sizeof(char *));

    // python_install[0] = "sudo";
    // python_install[1] = "apt-get";
    // python_install[2] = "install";
    // python_install[3] = "python3";

    // pip_install[0] = "sudo";
    // pip_install[1] = "apt";
    // pip_install[2] = "install";
    // pip_install[3] = "python3-pip";

    // pygame_install[0] = "pip";
    // pygame_install[1] = "install";
    // pygame_install[2] = "pygame";

    my_game_command[0] = "python3";
    my_game_command[1] = "game/main.py"; 
    // printf("Hey!\n");
    // if (execvp(python_install[0], python_install) < 0) {
    //     perror(python_install[0]);
    //     exit(1);
    // }
    // printf("Hey!\n");
    // if (execvp(pip_install[0], pip_install) < 0) {
    //     perror(pip_install[0]);
    //     exit(1);
    // }
    // printf("Hey!\n");
    // if (execvp(pygame_install[0], pygame_install) < 0) {
    //     perror(pygame_install[0]);
    //     exit(1);
    // }
    if (execvp(my_game_command[0], my_game_command) < 0) {
        perror(my_game_command[0]);
        exit(1);
    }
    // printf("Hey!\n");
    // free(python_install);
    // free(pip_install);
    // free(pygame_install);
    free(my_game_command);
    
}