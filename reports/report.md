# Building a Unix Shell in C
### Simrun Mutha and Vedaant Kuchhal
## Goals
The goal of our project is to create a shell in C. As our MVP, we want to implement 5 commands which include `ls`, `cd`, `history`, `sleep` and `rm`.  As a stretch goal, we want to add in additional redirect commands as well as custom commands.

## Learning Goals
**Simrun**: I want to get more comfortable coding in C. I have not worked on a low level project before and don’t know a lot about how a computer runs various processes so I want to gain more familiarity with that as well.

**Vedaant**: I want to take advantage of coding in C to implement programs that would best be done in a low-level language. Creating a shell will be a useful way for me to gain insight into UNIX operating systems while improving my C programming skills.

## Resources
We have largely worked with [this tutorial](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/), written in three parts, to understand how to implement a shell in C. Through this, we have a gotten a sense of the basic workflow for implementing a shell command, and we have implemented all of our MVP commands of `ls`, `cd`, `sleep`, `history`, and `rm`. To supplement our understanding of what is actually going on in the code, we have found Chapter 4 of Head First C to be very helpful. Additionally, as we learn new features, we try to implement them in our code (such as organizing into code and header files and using a `Makefile` to compile).

Overall, we think that we have a pretty good sense of how to navigate these resources and find new ones as required. The tutorial linked to above was fairly simple to follow although it was a bit of a learning curve in terms of various C features and grasping the idea of forking. At this stage, we have a basic understanding of what our implementations of various command-line functions should look like in order to approach building new ones, or seeking out resources to do so.

## Implementation

We were able to get quite a bit more done than we expected! Our original plan was to implement just `ls`, `cd`, `sleep`, `history`, and `rm` commands, but we were able to go much further and implement a few custom commands, as well as figuring out how to include redirection in our shell!
The process of how our code works, including each implementation, is outlined as follows-

### **Input:**
The first steps involve using the GNU readline library, which allows us to use its custom commands `readline` and `add_history` to read the line input and store it in the shell's history (further discussed in the implementation of `history`). These occur in [the main loop](https://github.com/olincollege/SoftSysShell/blob/main/main.c).

```
/* Read the user input. */
input = readline("unixsh> ");        
/* adding the input to history */
add_history(input);
```

After checking for redirection (discussed later) we use a helper function `get_input` that we got from the tutorial to split the command up into an array of space-separated words. 
 ```
 command = get_input(input, " ");
 ``` 

This works by splitting the string into an array by using `strtok` from the string library to check for whitespaces, the implementation can be found in the [helper functions file](https://github.com/olincollege/SoftSysShell/blob/main/helper_commands.c).


### **Forking:**

The key new thing that we learned from this project was understanding forking. Essentially, when entering a command in a shell process, the command shouldn't be run in the current process since an incorrect command would crash the shell and isolation of processes is always desirable. Therefore, we create a *copy* of the current process, called a `fork`. The command is executed in this copy (called the 'child process'), and once it's done executing, the program exits the copy and returns to the original process (called the 'parent process').

Note that *not all commands are executed in the fork*. This includes `cd` and `history`, and these will be discussed shortly. 

A fork is quite simple to create -
```
child_pid = fork();
```

Once we're in the forked 'child' process, we can execute various commands - the easiest ones to execute are the Unix Binaries.

### **Unix Binaries:**
```
unixsh> ls
LICENSE   README.md          custom_commands.h  game               helper_commands.h  main    reports
Makefile  custom_commands.c  custom_commands.o  helper_commands.c  helper_commands.o  main.c
unixsh>
```
Once a command has been read and split up into its individual parts, it can now be implemented. We found that the C Unix standard library has a function that can implement most Unix binaries - this includes `ls`, `sleep`, `rm`, and many others! The function is `execvp`:

```
if (execvp(command[0], command) < 0) {
    perror(command[0]);
    exit(1);
}
```
The input command is executed in the fork and any errors are handled. This allows us to cover a large amount of our target commands, including other common ones like `mkdir`. Our other two MVP commands were `cd` and `history`, both of which are executed outside the fork.

### **cd**:
```
unixsh> cd reports/
unixsh> ls
proposal.md  report.md  update.md
unixsh>
```
If `cd` was called in a fork, the moment the child process was exited, the current working directory would switch back to the original one of the parent process, rendering the command useless. Therefore, this command is called outside a fork so that the changes to the current working directory remain in the parent process.
```
 /* Implementation for cd. */
if (strcmp(command[0], "cd") == 0) {
    if (cd(command[1]) < 0) {
        perror(command[1]);
    }
    /* Skip the fork */
    continue;
}
```
Additionally, `cd` is not a system command with its own Unix binary file in the same way that, for example, `ls` is. Hence, `execvp` won't work on it, but a call to `chdir` does this for us.

```
int cd(char *path) {
    return chdir(path);
}
```
This function is also defined in the [helpers functions file](https://github.com/olincollege/SoftSysShell/blob/main/helper_commands.c).


### **history:**
```
unixsh> history
1: cd reports/
2: ls
3: history
unixsh>
```
The `history` commands allows the user to see all the previous commands entered within the shell. The user can also use the up and down arrow keys to go through all the past commands. As discussed earlier the GNU readline library's `add_history` function was used to store all the previous commands. The follwing function is called to print out all the previous history when the `history` command is entered.  
```
void print_history(){
    /* 'register' informs compiler that a variable can be put in a register */
    register HIST_ENTRY **hist_list; 
    int i;
    hist_list = history_list ();
    /* Loop and print each command in history */
    for (i = 0; hist_list[i]; i++){
        printf ("%d: %s\n", i + history_base, hist_list[i] -> line);
    }
}
```
**Redirect Output:**
```
unixsh> ls -l > hello.txt
unixsh> ls
hello.txt  proposal.md  report.md  update.md
unixsh>
```
This shell implements two different ways to redirect output. The `>` operator redirects stdout to any specified file. For example `ls -l > hello.txt` will redirect the output from `ls -l` to the file `hello.txt`. The `>>` operator will also redirect output to a file but instead of overwriting the contents of that file, it will append the new output to the end of the file. To check if the input command had a redirect operator, we used this function:

```
int redirection_check(char *input){
    char *out_append = strstr(input, ">>");
    char *out = strstr(input, ">");
    char *in = strstr(input, "<");

    if (out_append != NULL){return 1;}
    else if (out != NULL){return 2;}
    else if (in != NULL){return 3;}
    else {return 0;}    
}
```
To redirect output with the > operator, this function was implemented:

```
void redirect_out(char *file_name){
    int out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    dup2(out, 1);
    close(out);
}
```

Similarly to redirect output with the >> operator, this function was implemented:

```
void redirect_out_append(char *file_name){
    int out_append = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0600);
    dup2(out_append, 1);
    close(out_append);
}
```

All the above functions can once again be found in the [helpers functions file](https://github.com/olincollege/SoftSysShell/blob/main/helper_commands.c).

Finally in the main loop, we used a switch case to run the correct function based on the input. Even though there were only two options, we decided to use a switch case because this part of the code could be expanded to also redirect input which would be another case.

```
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
            }
            command = get_input(command_and_file[0], " ");
        }
```
You may have noticed the use of `trim`, which is an additional helper function we found [online](https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way) to get rid of leading and trailing whitespaces.



### **Custom Commands:**
In addition to the above commands, we made some of our own custom commands, `hype` and `surprise` that we implemented in the fork. These can be found in the [custom commands file](https://github.com/olincollege/SoftSysShell/blob/main/custom_commands.c).

#### **hype:** 
```
unixsh> hype
Enter your name: Steve
Hey Steve, you're the best!
unixsh>
```
This was a basic implementation of a command that asks for user input and prints out a statement, and it was used as a confidence test for forking that didn't involve calling `execvp`. 
```
void hype_me(){
    char name[100];
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Hey %s, you're the best!\n", name);
}
```
#### **surprise:**
The output for this is, well, a ~surprise~... All we can tell you is that it involved downloading a previous SoftDes final project and sneakily executing it in Python with the following lines of code:
```
char **my_game_command = malloc(3 * sizeof(char *));
my_game_command[0] = "python3"; 
my_game_command[1] = "game/main.py";
my_game_command[2] = NULL;
if (execvp(my_game_command[0], my_game_command) {
```
We used the `execvp` command and instead of supplying it with the output of `get_input`, we created our own array of strings to enter into it.

And that's our project! We learned a lot on the way much beyond what is visible in the code, and we had the satisfaction of implementing things we learned from class during the project. A quick example is how we organized all of our code and compiled it using a Makefile:

```
main: helper_commands.o custom_commands.o main.c
	gcc -o main helper_commands.o custom_commands.o main.c -lreadline

helper_commands.o: helper_commands.h helper_commands.c
	gcc helper_commands.c -c

custom_command.o: custom_commands.h custom_commands.c
	gcc custom_commands.c -c
```
Here, we were able to compile our helper and custom commands separately before including it in the main file. It helped declutter the main function a lot, and helped us not recompile everything at once.

An important design decision we made was to keep a simple flow for our code when implementing various commands. Using a series of `if` statements in the main loop, we ensured the following overall flow:
```
/* Read the user input. */
input = readline("unixsh> ");
...
if (!command[0]) {/* Handle empty commands */
...
/* Implement non-forked commands. */
...
/* Otherwise, create a fork. */
child_pid = fork();
...
/* Check for custom commands. */
...
/* Execute remaining commands. */
else if (execvp(command[0], command) < 0) {
...
```
This logical, intentionally built structure allowed us to have a clear picture of where various commands in our shell were being implemente, and enabled us to add new commands wherever appropriate so that we can focus on isolated implementation. There are many ways to implement the various levels of commands, but this flow seemed the most appropriate to us.


[Link to Github](https://github.com/olincollege/SoftSysShell) 
