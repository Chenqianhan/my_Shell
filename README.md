# ReadMe
This is a toy shell project that is implemented using different system calls
 and enables us to interact with operating
 system. Commends like ls, wc, cd, cat, echo with 
combinations of piping and output redirection etc are supported. Multiple pipes are
 allowed but redirections is assumed to be one.  
## Author:
* Lu Wang lw491
* Qianhan Chen qc92
##Features
* outer commands are supported via system call execvp.
* inner commands like pwd, ls, cd are took care separately which will be
explained in full detail in Logic part.
* We allow pipe and redirection. While multiple pipes are supported, only
one redirection is allowed in our toy shell.
* ; is supported
* when "ctrl-c" is typed, it will kill a running command.
* typing "exit" will quit the shell.
##Getting started
1. First do a make clean and make
   * $: make clean
   * $: make
2. Run cshell
   * $: ./cshell
3. All set! Please type different commands to play with our shell!!
## Some Examples
*  ls:
  
  
    /ilab/users/lw491/my_Shell $ ls
    cshell	cshell.c  cshell.h  file  Makefile  README.md
* pwd:

           
    /ilab/users/lw491/my_Shell $ pwd
    /ilab/users/lw491/my_Shell
  
* wc:


    /ilab/users/lw491/my_Shell $ wc cshell.h
      52  126 1068 cshell.h
* echo:

    
    /ilab/users/lw491/my_Shell $ echo 'hell world'
    'hell world'
* redirection, ls and cat:


    /ilab/users/lw491/my_Shell $ wc cshell.h > test
    
    /ilab/users/lw491/my_Shell $ ls
    cshell	cshell.c  cshell.h  file  Makefile  README.md  test
    
    /ilab/users/lw491/my_Shell $ cat test
      52  126 1068 cshell.h
* pipe (ls then sort):


    /ilab/users/lw491/my_Shell $ ls
    cshell	cshell.c  cshell.h  file  Makefile  README.md  test
    
    /ilab/users/lw491/my_Shell $ ls | sort -r
    test
    README.md
    Makefile
    file
    cshell.h
    cshell.c
    cshell

* ; (ls; echo "hello world"):


    /ilab/users/lw491/my_Shell $ ls; echo "hello world"
    cshell	cshell.c  cshell.h  file  Makefile  README.md  test
    "hello world"
*  pipe (ls |wc -l) :


    /ilab/users/lw491/my_Shell $ ls |wc -l
    7
* exit:


    /ilab/users/lw491/my_Shell $ exit
    lw491@ilab3:~/my_Shell$ 

##Logic
Our project can be divided into several steps as shown below.
* Parse command: for any input command, we will parse it first. This include
    * check whether we can use inner function (like cd ,pwd) by running is_inner()
    * then get the first command using get_cmd(0)
    * check whether we have redirect and deal with it : we need to differentiate between > and >>, it decide whether we append it or replace it
       This is taken care of by is_append variable.
    * pipe is taken care of by a for loop, since we allows for multiple pipes.
    * check whether we have ';' and deal with it
    * check whether we finish parsing.
* After we finish parsing command, we will continue based on whether the command is inner or outer.
 More specifically, inner command like cd, pwd, ls will be taken care of
  separately. Outer command will be executed using execvp(). Before we use execvp(), we will call fork() first.
  Parent process will be waiting for child process in this case.
* Since we allows redirection. We need a structure called cmd to deal with it. Each cmd can have many arguments
  like -l, and it will have an input and output. More specifically, when we want to type 'ls -l > test'. The output
  of 'ls -l' will be the input of 'test'. We use fork_exec() function to deal with
  redirection. cmd will be reused many times. This may be a weaker part in our project.
* Inner functions will be explained below:
  * cd: is implemented by using fchdir(). Please refer to function CD() for more detail.
  * pwd: is implemented by using getcwd(). Please refer to function PWD() for more detail.
  * exit is implemented by calling exit(). Please refer to function exit() for more detail.
* Ctrl C signal handling: This feature is taken care of by calling functions below.


    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
## Future improvement
* As we have mentioned in Logic part. One biggest weaker part is that we reuse our structure cmd many times for separate commands. The structure of 
cmd is shown below.


    typedef struct cmd{
        char *args[ARG_SIZE];
        int input;
        int output;
    }CMD;
 Since we have '>', a better implementation will be using a CMD linked list to connect many
 CMDs rather than reuse the same CMD again and again. This will be more clear for sophisticated inputs.
 * If we have more time, we will implement more features like <, & etc.
 ## Most difficult part
 We should say, the most difficult part will be parsing the input command properly. As we have mentioned in Future improvement part, a better 
 implementation will be using a linked list to store different commands along with their own arguments. But we
 only reuse a single cmd command. Although we store the input and output information for the 
 current command before we init it for reuse. This is definitely not the best solution.
 
 Other than parsing the input. We think the following steps are clear and easy. We take care of each command based on whether they're inner or outer.
 Then deal with them properly. 