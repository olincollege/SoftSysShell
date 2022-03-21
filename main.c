#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "helper_commands.h"
#include "custom_commands.h"

int main() {
    char **command;    
    char **command_and_file;    
    char *file_name;
    char *input;
    int saved_stdout;
    pid_t child_pid;
    int stat_loc;
    using_history();

    while (1) {
        input = readline("unixsh> ");        
        // adding the input to history
        add_history(input);
        // check for redirection
        int redirect = redirection_check(input);
        if (redirect){
            saved_stdout = dup(1);
            switch (redirect){
                case 1:
                    command_and_file = get_input(input, ">>"); 
                    redirect_out_append(trim(command_and_file[1]));                   
                    break;
                case 2:
                    command_and_file = get_input(input, ">");
                    redirect_out(trim(command_and_file[1]));
                    break;
                case 3:
                    command_and_file = get_input(input, "<");
                    redirect_out(trim(command_and_file[1]));
                    break;
            }
            command = get_input(command_and_file[0], " ");
        } else {
            command = get_input(input, " ");
        } 

        if (!command[0]) {/* Handle empty commands */
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
            print_history();
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
            if (execvp(command[0], command) < 0) {
                perror(command[0]);
                exit(1);
            }
        } else {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }
        dup2(saved_stdout, 1);
        close(saved_stdout);

        free(input);
        free(command);
    }

    return 0;
}

