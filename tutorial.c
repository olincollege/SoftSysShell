/* Following tutorial at this link:
https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/ */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void sigint_handler(int signo) {
    printf("Caught SIGINT\n");
}

char **get_input(char *input){
    // Seperating the input string by space to return an array of strings
    char **command = malloc(8 * sizeof(char *)); //double asterisk is a double pointer(pointer to a pointer)
    char *delimeter = " ";
    char *parsed;
    int i = 0;
    // using strtok to seperate string by space
    parsed = strtok(input, delimeter);
    while (parsed != NULL) {
        command[i] = parsed;
        i++;

        parsed = strtok(NULL, delimeter);
    }
    command[i] = NULL;
    return command;
}

int cd(char *path){
    return chdir(path);
}

int main(){

    // fork system returns twice: a parent and a child process
    // you cannot control which process will run first by default

    pid_t child_pid; // pid_t datatype represents process IDs
    pid_t wait_result;
    int status_location;
    char *input;
    char **command;

    // The child PID is 0 for one of the cases because
    // it is calling the getpid on the child of the child which doesnt exist

    
    signal(SIGINT, sigint_handler);
    while(1){

        input = readline("shell> ");
        command = get_input(input);

        if (strcmp("cd", command[0]) == 0){            
            if (cd(command[1]) < 0){
                perror(command[1]);
            };
            continue;
        }

        child_pid= fork(); 
        // everything under 'if' is the child process
        if (child_pid == 0){
            // execvp executes a command where the first argument is the 
            // command and the seconnd arguement is the command plus all the optioons
            // it always ends with a null character
            execvp(command[0], command); 
            printf("CHILD Current PID: %d and Child PID: %d\n",
                    getpid(), child_pid);
            sleep(1);
        }

        // everything under 'else' is the parent process
        else{
            // waitpid documentation here: https://linux.die.net/man/2/waitpid
            // waits until child process is over to execute this.
            wait_result = waitpid(child_pid, &status_location, 0);

            printf("PARENT Current PID: %d and Child PID: %d\n",
                getpid(), child_pid);
            // Prints the results from waitpid.
            printf("Results of waitpid:\nReturn- %d, Status - %i \n", 
                wait_result, status_location);         
        }
        free(input);
        free(command);
    }
    return 0;
}

// Compile using gcc -g -lreadline shell.c