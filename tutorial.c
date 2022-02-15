/* Following tutorial at this link: 
https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(){
 
    // fork system returns twice: a parent and a child process
    // you cannot control which process will run first by default
    
    pid_t child_pid= fork(); // pid_t datatype represents process IDs
    pid_t wait_result;
    int status_location;
    
    // The child PID is 0 for one of the cases because 
    // it is calling the getpid on the child of the child which doesnt exist

    // everything under 'if' is the child process
    if (child_pid == 0){
        printf("CHILD Current PID: %d and Child PID: %d\n",
                getpid(), child_pid);
        sleep(1);
    } 
    
    // everything under 'else' is the parent process
    else{
        // waitpid documentation here: https://linux.die.net/man/2/waitpid
        // waits until child process is over to execute this.
        wait_result = waitpid(child_pid, &status_location, WUNTRACED);

        printf("PARENT Current PID: %d and Child PID: %d\n",
               getpid(), child_pid);

    }
    return 0;
}