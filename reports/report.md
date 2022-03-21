# Building a Unix Shell in C
### Simrun Mutha and Vedaant Kuchhal
## Goals
The goal of our project is to create a shell in C. As our MVP, we want to implement 5 commands which include `ls`, `cd`, `history`, `sleep` and `rm`.  As a stretch goal, we want to add in additional redirect commands as well as custom commands.

## Learning Goals
**Simrun**: I want to get more comfortable coding in C. I have not worked on a low level project before and don’t know a lot about how a computer runs various processes so I want to gain more familiarity with that as well.

**Vedaant**: I want to take advantage of coding in C to implement programs that would best be done in a low-level language. Creating a shell will be a useful way for me to gain insight into UNIX operating systems while improving my C programming skills.

## Resources
We have largely worked with [this tutorial](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/), written in three parts, to understand how to implement a shell in C. Through this, we have a gotten a sense of the basic workflow for implementing a shell command, and we have implemented all of our MVP commands of `ls`, `cd`, `sleep`, `history`, and `rm`. To supplement our understanding of what is actually going on in the code, we have found Chapter 4 of Head First C to be very helpful. Additionally, as we learn new features, we try to implement them in our code (such as organizing into code and header files and using a `Makefile` to compile).

Overall, we think that we have a pretty good sense of how to navigate these resources and find new ones as required. The tutorial linked to above was fairly simple to follow although it was a bit of a learning curve in terms of various C features and the idea of forking. At this stage, we have a basic understanding of what our implementations of various command-line functions should look like in order to approach building new ones, or seeking out resources to do so.

## Implementation

**History:**
The `history` commands allows the user to see all the previous commands entered within the shell. It also allows the user to use the up and down arrow keys to go through all the past commands. To implement this command, we used the GNU readline library. Through, this library, it is possible to store all the previous commands by using the add_history function. This is the function used to print out all the previous history.  
```
void print_history(){
    register HIST_ENTRY **hist_list; // The keyword register hints to compiler that a given variable can be put in a register.
    int i;
    hist_list = history_list ();
    for (i = 0; hist_list[i]; i++){
        printf ("%d: %s\n", i + history_base, hist_list[i] -> line);
    }
}
```
**Redirection**

[Link to Github](https://github.com/olincollege/SoftSysShell) 
