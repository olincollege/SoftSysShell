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
// all MVP commands work

int cd(char *);

// initialize the history variables

int main() {
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;
    using_history();

    while (1) {
        input = readline("unixsh> ");        
        // adding the input to history
        add_history(input);
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
            /* Never returns if the call is successful */
            if (execvp(command[0], command) < 0) {
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
