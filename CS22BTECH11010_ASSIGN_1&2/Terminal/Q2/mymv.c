#include "header.h"

#define MAX_LINE_LENGTH 1000

void mymv(char *arguement0, char *arguement1, char *arguement2)
{
    struct stat source_stat;
    if (!strcmp(arguement0,"-v"))
    {
        if (stat(arguement1, &source_stat) == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
        }
        
        printf("\"%s\" -> \"%s\"\n", arguement1, arguement2);
        mymv(arguement1, arguement2,NULL);
    }
    
    
    else{
        if (!strcmp(arguement0,"--help"))
    {
        FILE *file = fopen("mymv.txt", "r");

        printf("enetered");
        if (file == NULL) {
            printf("Error: Unable to open file %s\n", arguement1);
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

        
    else{
    if (stat(arguement0, &source_stat) == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    if (S_ISDIR(source_stat.st_mode)&&(!strcmp(arguement0,"-r"))) move_directory(arguement0, arguement1);
    else if (!strcmp(arguement0,"-n"))
    {
        struct stat statBuffer;
        if(stat(arguement2, &statBuffer) == 0) {
        printf("%s already exists. Skipping.\n", arguement2);
        exit(EXIT_FAILURE);
        }
        else move_file(arguement1,arguement2);
    }
    else if (!strcmp(arguement0,"-f"))
    {
        move_file(arguement1,arguement2);
    }
    else if (!strcmp(arguement0,"-i"))
    {
        char permission;
        printf("Do you wnat to overwrite (Y/N): ");
        permission = getchar();
        if (permission == 'Y' || permission == 'y') move_file(arguement1,arguement2);
        else if (permission == 'N' || permission == 'n') 
        {
            struct stat statBuffer;
            if(stat(arguement2, &statBuffer) == 0) 
            {
                printf("%s already exists. Skipping.\n", arguement2);
                exit(EXIT_FAILURE);
            }
            else move_file(arguement1,arguement2);
        }
        

    }
    
    
    
    else move_file(arguement0, arguement1);


}  
    }     
}


void move_file(char *source_path, char *destination_path) {
    if (rename(source_path, destination_path) == -1) exit(EXIT_FAILURE);
    
}

void move_directory(char *source_path, char *destination_path) {
    if (mkdir(destination_path, 0777) == -1) exit(EXIT_FAILURE);

    DIR *directory = opendir(source_path);
    if (directory == NULL) exit(EXIT_FAILURE);

    struct dirent *entity;
    while ((entity = readdir(directory)) != NULL) {
        if (strcmp(entity->d_name, ".") == 0 || strcmp(entity->d_name, "..") == 0) {
            continue;
        }

        char *sub_source_path = malloc(strlen(source_path) + strlen(entity->d_name) + 2);
        sprintf(sub_source_path, "%s/%s", source_path, entity->d_name);

        char *sub_destination_path = malloc(strlen(destination_path) + strlen(entity->d_name) + 2);
        sprintf(sub_destination_path, "%s/%s", destination_path, entity->d_name);

        struct stat sub_source_stat;
        if (stat(sub_source_path, &sub_source_stat) == -1) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        if (S_ISDIR(sub_source_stat.st_mode)) move_directory(sub_source_path, sub_destination_path);
        else move_file(sub_source_path, sub_destination_path);

        free(sub_source_path);
        free(sub_destination_path);
    }

    closedir(directory);

    if (rmdir(source_path) == -1) {
        exit(EXIT_FAILURE);
    }
}