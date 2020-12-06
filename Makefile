all: cshell

cshell:
	gcc cshell.c -o cshell
clean:
	rm -rf cshell