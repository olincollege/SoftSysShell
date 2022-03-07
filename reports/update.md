# Building a Unix Shell in C
### Simrun Mutha and Vedaant Kuchhal
## Goals
The goal of our project is to create a shell in C. As our MVP, we want to implement 5 commands which include `ls`, `cd`, `history`, `sleep` and `rm`.  As a stretch goal, we want to add in additional commands like `mkdir`, `cp`, `mv` as well as implement error handling. 

## Learning Goals
**Simrun**: I want to get more comfortable coding in C. I have not worked on a low level project before and don’t know a lot about how a computer runs various processes so I want to gain more familiarity with that as well.

**Vedaant**: I want to take advantage of coding in C to implement programs that would best be done in a low-level language. Creating a shell will be a useful way for me to gain insight into UNIX operating systems while improving my C programming skills.

## Resources
We have largely worked with [this tutorial](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/), written in three parts, to understand how to implement a shell in C. Through this, we have a gotten a sense of the basic workflow for implementing a shell command, and we have implemented all of our MVP commands of `ls`, `cd`, `sleep`, `history`, and `rm`. To supplement our understanding of what is actually going on in the code, we have found Chapter 4 of Head First C to be very helpful. Additionally, as we learn new features, we try to implement them in our code (such as organizing into code and header files and using a `Makefile` to compile).

Overall, we think that we have a pretty good sense of how to navigate these resources and find new ones as required. The tutorial linked to above was fairly simple to follow although it was a bit of a learning curve in terms of various C features and the idea of forking. At this stage, we have a basic understanding of what our implementations of various command-line functions should look like in order to approach building new ones, or seeking out resources to do so.


## Current Work
1. We are attempting some of our stretch goal implementations, such as `mkdir` and `cp`. We do have enough time to try these, and a tangible completion of this goal would be a successful implementation of at least one of these functions (*Simrun*)
2. Carrying out an implementation of a custom command that does something cool. We don't know what this quite looks like yet, but we know how to implement the basic flow using forking (*Vedaant*). 
3. At this point, we are at a stage where we almost completely understand our code, but there is a little more scope for re-organizing it/refactoring it. We are looking into that would make our code more neat and accessible and give is greater clarity as to what is going on. A criteria for completeness would be that we are able to move at least one of our command implementations outside the `main` function (*both*).


[Link to Todoist](https://todoist.com/app/project/2285403984) (which we frankly haven't been using much)

[Link to Github](https://github.com/olincollege/SoftSysShell) 
