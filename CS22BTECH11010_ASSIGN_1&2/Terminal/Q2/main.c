/*
 * 	Name -: Shravan Badgujar
 * 	Roll no. -: CS22BTECH11010
 * 	Assignment -: 1 
 * 	Q2.
 */

#include "header.h"

void mypse();

void main()
{
    
	while(1){
        char *command_buff; // This is used to get the command 
        char store[100];
        char *user; // In this username will be stored
        char host[225]; // This is used to the host name
        char CWD[PATH_MAX+2]; // This is used to store Current Working Directory
        char *CLI; // This is used to Command Line
        char *command; //This is used to store the command
        char *arguement[5]; // This is used to store the arguement
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


		command_buff = readline(CLI);//Readline is just like input in python
		if(strlen(command_buff)>0) { add_history(command_buff); } // This is used to store command history
        strcpy(store,command_buff);
        command = strtok(command_buff," "); // strtok just break the string in two part on the basis of restrictor
        arguement[0] = strtok(NULL," ");
        arguement[1] = strtok(NULL," ");
        arguement[2] = strtok(NULL," ");
        arguement[3] = strtok(NULL," ");
        arguement[4] = strtok(NULL," ");
        arguement[5] = strtok(NULL," ");
        

        if (!strcmp(command,"myls")) myls(arguement[0]);
        else if (!strcmp(command,"mycp")) mycp(arguement[0],arguement[1],arguement[2]);
        else if (!strcmp(command,"mymv")) mymv(arguement[0],arguement[1],arguement[2]);
        else if (!strcmp(command,"myps")) 
        {
            printf("%s", arguement[0]);
            if (arguement[0]==NULL) myps(arguement[0]);
            else if (!strcmp(arguement[0],"-e")) mypse();
            else myps(arguement[0]);
        }
        else if (!strcmp(command,"grep")) mygrep(arguement[0],arguement[1],arguement[2],arguement[3]);
        
        
        
        else if (!strcmp(command,"mycd"))
        {
            if (arguement[0]==NULL)
			{
				fprintf(stderr, "cd:Something expected as arguement\n");
				continue;
			}
			chdir(arguement[0]);
            
        }

        else
        {
            system(store);
		    if(!strcmp(store, "exit") || !strcmp(store, "quit") || !strcmp(store, "q")){ break; }
		    else if(!strcmp(store, "help")) { system("bash -c help"); }
        }

        
        

		

	}
}


