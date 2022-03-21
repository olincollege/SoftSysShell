#include "helper_commands.h"
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <stdio.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

char **get_input(char *input, char *separator) {
    char **command = malloc(8 * sizeof(char *));
    if (command == NULL) {
        perror("malloc failed");
        exit(1);
    }

    // char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
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
