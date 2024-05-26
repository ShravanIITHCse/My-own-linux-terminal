# My-own-linux-terminal
This repository contains stimulation of linux terminal that was made by me for an assignment of ours

# There are two questions in the repo following is the readme for both the questions

## Q1
This terminal can execute any command a normal terminal can:

Type 'help' and ENTER for detailed usage of options for every command.
	
Commands are getting executed through system().
cd is getting executed with the help of chdir().

The requirements to execute this terminal are :
-> A Linux Ubuntu machine.
-> GCC should be installed in the machine:
	If GCC is not installed in your machine, do the following:
	Open the terminal on your machine and run the following commands:
		-> "sudo apt update"
		-> "sudo apt install build-essential"
		OR
		-> "sudo apt install gcc"
	To check if install then run the following command:
	        -> "gcc --version"
-> libreadline :
Install libreadline in your machine:
For that run the following command on your terminal:
		-> "sudo apt-get install libreadline8 libreadline-dev"
Now you are ready to run this terminal!

Steps to execute:

-> Change the directory to the directory where the files are located.
-> Now run the following commands: 
    -> "make" (To compile the executable files.)
    -> "./Myshell" (To execute the terminal.)

Now you can run whichever command you want to run from the above mentioned commands.
