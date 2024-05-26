/*
 * 	Name -: Shravan Badgujar
 * 	Roll no. -: CS22BTECH11010
 * 	Assignment -: 1 
 * 	Q1.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<unistd.h>
#include<sys/types.h>
#include<limits.h>
#include<errno.h>
void main()
{
	while(1){
	char *command_buff; // This is used to get the command 
	char *user; // In this username will be stored
	char host[225]; // This is used to the host name
	char CWD[PATH_MAX+2]; // This is used to store Current Working Directory
	char *CLI; // This is used to Command Line
	char *command_cd; //Just to store cd command
	char *arguement; //While using CD command we store the path where we want to go in this pointer
	int status; //This would be used to take the return from the chdirSS
	// If we keep host and CWD as a pointer then it gives segmentation fault due to the data leak

	user = getlogin(); // Saving username
	gethostname(host, HOST_NAME_MAX+1); // Saving Host Name
	getcwd(CWD, sizeof(CWD)); // Saving CWD
	// Start of the process for printing CWD
	CLI = strcat(user, "@");
	CLI = strcat(CLI, host);
	CLI = strcat(CLI, ":");
	CLI = strcat(CLI, CWD);
	CLI = strcat(CLI, "$ ");
	// End of the process
	
	
	
		command_buff = readline(CLI);
		if(strlen(command_buff)>0) { add_history(command_buff); } // This is used to store command history
		// CD command part starts from here
		
		if ((command_buff[0]=='c')&& (command_buff[1]=='d'))
		{
			command_cd= strtok(command_buff," ");
			arguement= strtok(NULL," ");
			if (arguement==NULL)
			{
				fprintf(stderr, "cd:Something expected as arguement\n");
				continue;
			}
			status = chdir(arguement);
			if (status == -1)
			{
				fprintf(stderr, "cd : %s %s\n", arguement, strerror(errno));
			}
			else{
				system(command_buff);
			}

			
		}
		//CD command part ends here
		
		else{
		//command_buff = strcat(command_cd," ");
		//command_buff = strcat(command_buff,arguement);
		system(command_buff);
		if(!strcmp(command_buff, "exit") || !strcmp(command_buff, "quit") || !strcmp(command_buff, "q")){ break; }
		else if(!strcmp(command_buff, "help")) { system("bash -c help"); }
		}

	}
}
