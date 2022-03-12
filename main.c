/* Following tutorial at this link:
https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/ */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "command_reader.h"
#include "custom_commands.h"
// all MVP commands work

int cd(char *);
void send_output(char *input, char *path);
int redirection_check(char *input);
void redirect_in(char *file_name);
void redirect_out(char *file_name);
void redirect_out_append(char *file_name);
char *trim(char *str);
void print_history();
void redirect_command(int redirect, int saved_stdout, char **command_and_file, char *input);

int main() {
    char **command;    
    char **command_and_file;    
    char *file_name;
    char *input;
    int saved_stdout;
    pid_t child_pid;
    int stat_loc;
    // allocation memory
    command = malloc(20 * sizeof(command));
    command_and_file = malloc(20 * sizeof(command_and_file));
    input = malloc(20 * sizeof(input));
    // initialize the history variables
    using_history();
    


    while (1) {
        // implement exit and current working directory
        
        input = readline("unixsh> ");        
        // adding the input to history
        add_history(input);
        // check for redirection
        int redirect = redirection_check(input);
        if (redirect){
            // redirect_command(redirect, saved_stdout, command_and_file, input);
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
        puts("here");

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

int cd(char *path) {
    return chdir(path);
}

void redirect_out(char *file_name){
    int out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    dup2(out, 1);
    close(out);
}

void redirect_out_append(char *file_name){
    int out_append = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0600);
    dup2(out_append, 1);
    close(out_append);
}

void redirect_in(char *file_name){
    int in = open(file_name, O_RDONLY);
    dup2(in, 0);
    close(in);
}

int redirection_check(char *input){
    char *out_append = strstr(input, ">>");
    char *out = strstr(input, ">");
    char *in = strstr(input, "<");

    if (out_append != NULL){return 1;}
    else if (out != NULL){return 2;}
    else if (in != NULL){return 3;}
    else {return 0;}    
}


char *trim(char *str){
    /* Taken from https://stackoverflow.com/questions
    /122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way*/
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if( frontp != str && endp == frontp )
            *str = '\0';
    else if( str + len - 1 != endp )
            *(endp + 1) = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }
    return str;
}

void print_history(){
    register HIST_ENTRY **hist_list; // The keyword register hints to compiler that a given variable can be put in a register.
    int i;
    hist_list = history_list ();
    for (i = 0; hist_list[i]; i++){
        printf ("%d: %s\n", i + history_base, hist_list[i] -> line); // is -> the equiv of .?
    }
}

// void redirect_command(int redirect, int saved_stdout, char **command_and_file, char *input){
//     saved_stdout = dup(1);
//     switch (redirect) {
//         case 1:
//             command_and_file = get_input(input, ">>"); 
//             redirect_out_append(trim(command_and_file[1]));                   
//             break;
//         case 2:
//             command_and_file = get_input(input, ">");
//             redirect_out(trim(command_and_file[1]));
//             break;
//         case 3:
//             command_and_file = get_input(input, "<");
//             redirect_out(trim(command_and_file[1]));
//             break;
//         }
// }