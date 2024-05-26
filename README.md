# My-own-linux-terminal
This repository contains stimulation of linux terminal that was made by me for an assignment of ours

# There are two questions in the repo following is the readme for both the questions

## Q1
This terminal can execute any command a normal terminal can:

Type 'help' and ENTER for detailed usage of options for every command.
	
Commands are getting executed through system().
cd is getting executed with the help of chdir().

### The requirements to execute this terminal are :
- A Linux Ubuntu machine.
- GCC should be installed in the machine:
	- If GCC is not installed in your machine, do the following:
	- Open the terminal on your machine and run the following commands:
		- "sudo apt update"
		- "sudo apt install build-essential"
		 OR
		- "sudo apt install gcc"
	- To check if install then run the following command:
	        - "gcc --version"
- libreadline :
	- Install libreadline in your machine:
	- For that run the following command on your terminal:
		- "sudo apt-get install libreadline8 libreadline-dev"
- Now you are ready to run this terminal!

### Steps to execute:

- Change the directory to the directory where the files are located.
- Now run the following commands: 
	- "make" (To compile the executable files.)
	- "./Myshell" (To execute the terminal.)

Now you can run whichever command you want to run from the above mentioned commands.


## Q2
    
### This terminal can execute myls,myps,mycp,mymv and mygrep with few options:

1. myls:
	- myls [OPTION]
	- This works as original command ls.
	- This can be executed with following options:
	- 1) -l   2) -S   3) -s   4) -g   5) -o   6) -r   7) -ls  8) -lS 
2. myps:
	- myps [OPTION]
	- This works as original command ps.
	- This can be executed with following options:
	- 1) -e   2) -a   3) -F   4) -aF
3. mycp:
	- mycp [OPTION] [SOURCE] [TARGET]
	- mycp [SOURCE] [SOURCE]..... [DIRECTORY]
	- This works as original command cp.
	- This can be executed with following options:
	- 1) -r   2) -n    3) -f   4) -i
4. mymv:
	- mymv [OPTION] [SOURCE] [TARGET]
	- mymv [SOURCE] [SOURCE]..... [DIRECTORY]
	- This works as original command mv.
	- This can be executed with following options:
	- 1) -v   2) -n   3) -f   4) -r   5) -i
5. mygrep:
	- mygrep [OPTION] PATTERN [FILE] [FILE]...
	- This works as original command grep.
	- This can be executed with following options:
	- 1) -m   2) -v   3) -o   4) -n 

- Type 'help' and ENTER for detailed usage of options for every command.
- Type '[COMMAND] --help' and ENTER for detailed usage of options for a particular command.
	
Other commands are getting executed through system().
cd is getting executed with the help of chdir().

### The requirements to execute this terminal are :
- A Linux Ubuntu machine.
- GCC should be installed in the machine:
	- If GCC is not installed in your machine, do the following:
	- Open the terminal on your machine and run the following commands:
		- "sudo apt update"
		- "sudo apt install build-essential"
		 OR
		- "sudo apt install gcc"
	- To check if install then run the following command:
	        - "gcc --version"
- libreadline :
	- Install libreadline in your machine:
	- For that run the following command on your terminal:
		- "sudo apt-get install libreadline8 libreadline-dev"
- Now you are ready to run this terminal!

### Steps to execute:

- Change the directory to the directory where the files are located.
- Now run the following commands: 
	- "make" (To compile the executable files.)
	- "./Myshell" (To execute the terminal.)

Now you can run whichever command you want to run from the above mentioned commands.




