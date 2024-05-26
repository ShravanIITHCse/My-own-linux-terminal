#include "header.h"

#define MAX_LINE_LENGTH 1000

struct file_info
{
    char *permissions;
    int head_link;
    char *fowner_name;
    char *fgroup_name;
    long int file_size;
    char *date_time;
    char *file_name;
    long int block_size;
};

void myls(char* arguement)
{
    DIR *directory; //This is the diractory pointer like file pointer defined in dirent.h
    struct dirent *entity; //This is struct defined in dirent.h which is going to store the file in current working directory
    struct stat file_stat; //USeful below in finding many details of file
    struct tm *time;
    struct passwd *owner_name; //Used for username
    struct group *group_name ; // Used for group name
    int total;
    

    directory = opendir(".");
    struct file_info list[100];
    
    
    if (directory == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    int i=0;
    while ((entity=readdir(directory))!=NULL)
    {
        if (entity->d_name[0]=='.') continue;
        stat(entity->d_name,&file_stat);
        char fpermission[11];
        fpermission[0] = S_ISDIR(file_stat.st_mode) ? 'd' : '-'; //If the entity is directory it will return d else-        
        fpermission[1] = file_stat.st_mode & S_IRUSR ? 'r' : '-'; // Checks if owner of the file has read permission or not
        fpermission[2] = file_stat.st_mode & S_IWUSR ? 'w' : '-'; // Checks if owner of the file has write permission or not
        fpermission[3] = file_stat.st_mode & S_IXUSR ? 'x' : '-'; // Checks if owner of the file has execute permission or not
        fpermission[4] = file_stat.st_mode & S_IRGRP ? 'r' : '-'; // Checks if group owner of the file has read permission or not
        fpermission[5] = file_stat.st_mode & S_IWGRP ? 'w' : '-'; // Checks if group owner of the file has write permission or not
        fpermission[6] = file_stat.st_mode & S_IXGRP ? 'x' : '-'; // Checks if group owner of the file has execute permission or not
        fpermission[7] = file_stat.st_mode & S_IROTH ? 'r' : '-'; // Checks if others of the file has read permission or not
        fpermission[8] = file_stat.st_mode & S_IWOTH ? 'w' : '-'; // Checks if others of the file has write permission or not
        fpermission[9] = file_stat.st_mode & S_IXOTH ? 'x' : '-'; // Checks if others of the file has execute permission or not
        fpermission[10] = '\0';
        list[i].permissions = fpermission;

        list[i].head_link = (int)file_stat.st_nlink;

        owner_name = getpwuid(file_stat.st_uid);
        list[i].fowner_name = owner_name->pw_name;

        group_name = getgrgid(file_stat.st_gid);
        list[i].fgroup_name = group_name->gr_name;

        list[i].file_size = file_stat.st_size;

        char time[80];
        strftime(time, sizeof(time), "%Y-%m-%d %H:%M", localtime(&file_stat.st_mtime));
        list[i].date_time=time;

        list[i].file_name = entity->d_name;

        if((list[i].file_size%4096)==0) list[i].block_size=(((list[i].file_size)/4096)*4);
        else list[i].block_size=(((list[i].file_size)/4096+1)*4);

        i++;
    }

    long int sum = 0;
    for (int j = 0; j < i; j++)
    {
        if((list[j].file_size%4096)==0) sum+=(((list[i].file_size)/4096)*4);
        else sum+=(((list[j].file_size)/4096+1)*4);
    }
    

    if (arguement==NULL)
    {
        for (int k = 0; k < i; k++)
        {
            printf("%s\n", list[k].file_name);
        }
        
    }

    else if (!strcmp(arguement,"-l"))
    {
        printf("Total\t\t");
        printf("%ld\n", sum);

        for (int k = 0; k < i; k++)
        {
            printf("%s ", list[k].permissions);
            printf("%d ", list[k].head_link);
            printf("%s ", list[k].fowner_name);
            printf("%s ", list[k].fgroup_name);
            printf("%ld ", list[k].file_size);
            printf("%s ", list[k].date_time);
            printf("%s ", list[k].file_name);
            printf("\n");
        }
    }

    else if (!strcmp(arguement,"-S"))
    {
        struct file_info temp;
        for (int j = 0; j < i; j++)
        {
            for (int k = j; k < i; k++)
            {
                if(list[j].file_size<list[k].file_size) 
                {
                    temp = list[j];
                    list[j] = list[k];
                    list[k] = temp;
                }
            }
        }
        for (int k = 0; k < i; k++)
        {
            printf("%s ", list[k].file_name);
            printf("\n");
        }
        
    }
    
    else if (!strcmp(arguement,"-s"))
    {   
        for (int k = 0; k < i; k++)
        {
            printf("%ld ", list[k].block_size);
            printf("%s ", list[k].file_name);
            printf("\n");
        }
        
    }

    else if (!strcmp(arguement,"-lS"))
    {
        struct file_info temp;
        for (int j = 0; j < i; j++)
        {
            for (int k = j; k < i; k++)
            {
                if(list[j].file_size<list[k].file_size) 
                {
                    temp = list[j];
                    list[j] = list[k];
                    list[k] = temp;
                }
            }
        }
        for (int k = 0; k < i; k++)
        {
            printf("%s ", list[k].permissions);
            printf("%d ", list[k].head_link);
            printf("%s ", list[k].fowner_name);
            printf("%s ", list[k].fgroup_name);
            printf("%ld ", list[k].file_size);
            printf("%s ", list[k].date_time);
            printf("%s ", list[k].file_name);
            printf("\n");
        }
        
    }

     else if (!strcmp(arguement,"-ls"))
    {   
        for (int k = 0; k < i; k++)
        {
            printf("%ld ", list[k].block_size);
            printf("%s ", list[k].permissions);
            printf("%d ", list[k].head_link);
            printf("%s ", list[k].fowner_name);
            printf("%s ", list[k].fgroup_name);
            printf("%ld ", list[k].file_size);
            printf("%s ", list[k].date_time);
            printf("%s ", list[k].file_name);
            printf("\n");
        }
        
    }

    else if (!strcmp(arguement,"-g"))
    {
        printf("Total\t\t");
        printf("%ld\n", sum);

        for (int k = 0; k < i; k++)
        {
            printf("%s ", list[k].permissions);
            printf("%d ", list[k].head_link);
            printf("%s ", list[k].fgroup_name);
            printf("%ld ", list[k].file_size);
            printf("%s ", list[k].date_time);
            printf("%s ", list[k].file_name);
            printf("\n");
        }
    }

    else if (!strcmp(arguement,"-o"))
    {
        printf("Total\t\t");
        printf("%ld\n", sum);

        for (int k = 0; k < i; k++)
        {
            printf("%s ", list[k].permissions);
            printf("%d ", list[k].head_link);
            printf("%s ", list[k].fowner_name);
            printf("%ld ", list[k].file_size);
            printf("%s ", list[k].date_time);
            printf("%s ", list[k].file_name);
            printf("\n");
        }
    }

    else if (!strcmp(arguement,"-r"))
    {
        struct file_info temp;
        for (int j = 0; j < i; j++)
        {
            for (int k = j; k < i; k++)
            {
                if(list[j].file_size>list[k].file_size) 
                {
                    temp = list[j];
                    list[j] = list[k];
                    list[k] = temp;
                }
            }
        }
        for (int k = 0; k < i; k++)
        {
            printf("%s ", list[k].file_name);
            printf("\n");
        }
        
    }
    else if (!strcmp(arguement,"--help"))
    {
        FILE *file = fopen("myls.txt", "r");

        printf("enetered");
        if (file == NULL) {
            printf("Error: Unable to open file myls.txt\n");
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




    
    
    
    closedir(directory);

}