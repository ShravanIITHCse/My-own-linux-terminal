#include "header.h"

#define PROC_PATH "/proc/"
#define MAX_LINE_LENGTH 1000

struct process_info
{
    char command[100];
    long int pid;
    char t[20];
    char stime[10];
    unsigned int ppid;
    unsigned int psr;
    unsigned long sz, rss, c ,startime;
    char time[10];
};

void myps(char *arguement0)
{
    struct process_info process[1000];
    DIR *directory;
    struct dirent *entity;
    struct tm *time_info;
    directory = opendir(PROC_PATH); //Here we have opened the proc directory
    int count = 0;
    char *user_id = getlogin(); //Here user id is stored in that pointer
    
    while ((entity=readdir(directory))!=NULL) //This loop will run until it recahes the end of the directory
    {
        // if(isdigit(*entity->d_name)) // This skips the file which did not start with digit
        if (entity->d_type == DT_DIR && isdigit(entity->d_name[0]))
        {
            struct stat stat_directory;
            char *pid = entity->d_name; //That digit is stored as pid
            char stat_directory_path[200];
            
            sprintf(stat_directory_path,"/proc/%ld/stat",atol(pid)); //In this we are atol changes string into long and it is replaced with ld and then the path is stored in stat_file_path
            if(stat(stat_directory_path,&stat_directory)!=0) continue;//Here the info about the file specified is stored in the structure stat file and the condition is to check wether it run or not

            char descriptor0_path[200];

            sprintf(descriptor0_path,"/proc/%ld/fd/0", atol(pid)); // in this descriptoro_path stores path of descriptor0
            if((arguement0 == NULL) /*|| (!strcmp(arguement0,"-e"))*/) 
            {
                if(access(descriptor0_path,F_OK)!=0) continue; //Access function checks can access a file or not in this context first arguement is file path and F_OK is value which helps to check wether the file exist 
                int descriptor0_file;
                if((descriptor0_file=open(descriptor0_path,O_RDWR))<0) continue; //O_RDWR is a flag used to open the file for reading and writing
                if(ttyname(descriptor0_file)==NULL)//This is the file which checks if the file is of the terminal or not 
                {
                    close(descriptor0_file);
                    continue;
                }
            }

            
                if(access(descriptor0_path,F_OK)!=0) continue;
                int descriptor0_file;
                if((descriptor0_file=open(descriptor0_path,O_RDWR))<0) continue;
                if(ttyname(descriptor0_file)==NULL)
                {
                    close(descriptor0_file);
                    continue;
                }
            
            
            FILE *stat_file;
            stat_file = fopen(stat_directory_path,"r"); //Opens the file of which the path is read mode

            process[count].pid = atol(pid); //pid stored in pid of one element of process

            char start_command[100];
            unsigned int process_ID,ppid,psr;
            unsigned long int sz, rss, c ,stime, utime;
            unsigned long long int starttime;
            char current_state;
            char tty[20];


            fscanf(stat_file, "%u %s %c %u %*u %*u %*u %*u %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %*s %lu %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %u %lu ",//%* is to avoid the input
                &process_ID, start_command ,&current_state, &ppid, &utime ,&stime, &starttime, &rss ,&psr,&c);// this is storin all the info got from stat_file

            FILE *statm_file =fopen("/proc/self/statm","r");
            fscanf(statm_file,"%lu",&sz);
            statm_file = fopen("/proc/uptime","r");
            double uptime;
            fscanf(statm_file,"%lf",&uptime);

            if (arguement0!=NULL)
            {
                if (strcmp(arguement0,"-a")==0||strcmp(arguement0,"-aF")==0)
            {
                pid_t sid;
                sid = getsid(atoi(pid));
                if (sid!=atoi(pid)) continue;
                if(current_state=='Z' || current_state=='T') continue;
            }
            
            }
            
            
            ssize_t nbytes = readlink(descriptor0_path,tty,20);
            if(nbytes>=0) tty[nbytes] = '\0';
            else 
            {
                tty[0] = '?';
                for (int i = 1; i < 9; i++)
                {
                    tty[i] = ' ';
                }
                tty[9]='\0';
            }

            strcpy(process[count].command,start_command);

            int tim =(int)(float)(stime+utime)/sysconf(_SC_CLK_TCK);
            sprintf(process[count].time,"%02d:%02d:%02d",(tim/3600)%3600,(tim/60)%60,tim%60);

            time_t st = time(NULL)-((double)uptime-((double)starttime/sysconf(_SC_CLK_TCK)));
            time_info = localtime(&st);
            char timet[10];
            strftime(timet,10,"%H:%M", time_info);
            strcpy(process[count].stime,timet);
            strcpy(process[count].t,tty);
            
            process[count].ppid = ppid;
            process[count].psr = psr;
            process[count].sz = sz;
            process[count].rss = rss;
            process[count].c = c;
            count++;
        
        }
    }
    if (arguement0==NULL)
    {
        printf("PID\t TTY\t\t TIME\t\t CMD\n");
        for (int i = 0; i < count; i++)
        {
            printf("%ld\t %s\t %s\t %s\n",process[i].pid,process[i].t,process[i].time,process[i].command);
        }
    }

    else if ((!strcmp(arguement0,"-aF"))||(!strcmp(arguement0,"-F")))
    {
         printf("UID\t\tPID\tPPID\tc\tSZ\tRRS\tPSR\tSTIME\tTTY\t\tTIME\t\tCMD\n");
            for (int i = 0; i < count; i++)
         {
             printf("%s\t\t%ld\t%u\t%lu\t%lu\t%lu\t%u\t%s\t%s\t%s\t%s\n",user_id,process[i].pid,process[i].ppid,process[i].c,process[i].sz,process[i].rss,process[i].psr,process[i].stime,process[i].t,process[i].time,process[i].command);

         }
    }

    
    else if (!strcmp(arguement0,"-a"))
    {
        printf("PID\t TTY\t\t TIME\t\t CMD\n");
        for (int i = 0; i < count; i++)
        {
            printf("%ld\t %s\t %-10s\t %-10s\n",process[i].pid,process[i].t,process[i].time,process[i].command);
        }
    }

    else if (!strcmp(arguement0,"--help"))
    {
        FILE *file = fopen("myps.txt", "r");

        if (file == NULL) {
            printf("Error: Unable to open file %s\n", arguement0);
            exit(EXIT_FAILURE);
        }

        char line[MAX_LINE_LENGTH];
        int count=0;

        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
                printf("%s", line);            
        }
        printf("\n");
        fclose(file);
    }
}

