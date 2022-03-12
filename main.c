/* Following tutorial at this link:
https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/ */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command_reader.h"
#include "custom_commands.h"
// all MVP commands work

int cd(char *);
void send_output(char *input, char *path);


int main() {
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;
    // initialize the history variables
    using_history();

    while (1) {
        // try to implement exit, current working directory and redirect operators
        
        input = readline("unixsh> ");        
        // adding the input to history
        add_history(input);
        // check for redirection
        // int redirect = redirection_check(input);
        // seperate input into list of words divided by a space
        command = get_input(input);

        if (!command[0]) {      /* Handle empty commands */
            free(input);
            free(command);
            continue;
        }


        if (strcmp(command[0], "cd") == 0) {
            if (cd(command[1]) < 0) {
                perror(command[1]);
            }
            /* Skip the fork */
            continue;
        }
        if (strcmp(command[0], "history") == 0) {
            register HIST_ENTRY **hist_list; // The keyword register hints to compiler that a given variable can be put in a register.
            int i;
            hist_list = history_list ();
            for (i = 0; hist_list[i]; i++){
                // printf("History length: %d\n", history_length);
                printf ("%d: %s\n", i + history_base, hist_list[i] -> line); // is -> the equiv of .?
            }
            /* Skip the fork */
            continue;
        }

        child_pid = fork();
        if (child_pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (child_pid == 0) {
            if (strcmp(command[0], "hype") == 0) {
                hype_me();
            } else if (strcmp(command[0], "surprise") == 0)
            {
                game();
            }
            
            /* Never returns if the call is successful */
            else if (execvp(command[0], command) < 0) {
                perror(command[0]);
                exit(1);
            }
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        free(input);
        free(command);
    }

    return 0;
}

int cd(char *path) {
    return chdir(path);
}

void send_output(char *input, char *path){
    
}

// int redirection_check(input){
//     char *out_append = strstr(input, ">>");
//     char *out = strstr(input, ">");
//     char *in = strstr(input, "<");

//     if (out_append != NULL){return 1;}
//     else if (out != NULL){return 2;}
//     else if (in != NULL){return 3;}
//     else {return 0;}
    
// }

// void parse_string(input){
//     delim = ">"
// }
