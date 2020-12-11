# ReadMe
This is a toy shell project that is implemented using different system calls
 and enables us to interact with operating
 system. Commends like ls, wc, cd, cat, echo with 
combinations of piping and output redirection etc are supported. Multiple pipes are
 allowed but redirections is assumed to be one.  

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

##Logic

* 
 
