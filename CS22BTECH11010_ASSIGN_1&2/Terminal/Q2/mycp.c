#include "header.h"

#define MAX_LINE_LENGTH 1000

void mycp(char *arguement0, char *arguement1, char *arguement2)
{
    if (!strcmp(arguement0,"-r"))
    {
        copy_directory(arguement1,arguement2);
    }
    else if (!strcmp(arguement0,"-n"))
    {
        struct stat statBuffer;
        if(stat(arguement2, &statBuffer) == 0) {
        printf("%s already exists. Skipping.\n", arguement2);
        exit(EXIT_FAILURE);
        }
        else copy_file(arguement1,arguement2);
    }

    else if (!strcmp(arguement0,"-f"))
    {
        copy_file(arguement1,arguement2);
    
    }
    else if (!strcmp(arguement0,"-i"))
    {
        char permission;
        printf("Do you wnat to overwrite (Y/N): ");
        permission = getchar();
        if (permission == 'Y' || permission == 'y')
        copy_file(arguement1,arguement2);
        else if (permission == 'N' || permission == 'n') 
        {
            struct stat statBuffer;
            if(stat(arguement2, &statBuffer) == 0) 
            {
                printf("%s already exists. Skipping.\n", arguement2);
                exit(EXIT_FAILURE);
            }
            else copy_file(arguement1,arguement2);
        }
    }
    else if (!strcmp(arguement0,"--help"))
    {
        FILE *file = fopen("mycp.txt", "r");

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
    
    else
    {   
        copy_file(arguement0,arguement1);
    }
}

void copy_file(char* source_path, char* dest_path) {
    FILE* source_file = fopen(source_path, "rb");
    FILE* destination_file = fopen(dest_path, "wb");
    char data[1024];
    size_t data_size;

    if (source_file == NULL) {
        printf("Error opening source file %s\n", source_path);
        exit(1);
    }

    if (destination_file == NULL) {
        printf("Error creating destination file %s\n", dest_path);
        exit(1);
    }

    while ((data_size = fread(data, 1, sizeof(data), source_file)) > 0) {
        fwrite(data, 1, data_size, destination_file);
    }

    fclose(source_file);
    fclose(destination_file);
}

void copy_directory(char* source_directory, char* destination_directory) {
    struct dirent *entity;
    DIR *directory = opendir(source_directory);

    if (directory == NULL) {
        printf("Error opening source directory %s\n", source_directory);
        exit(1);
    }

    if (mkdir(destination_directory, 0777) != 0) {
        printf("Error creating destination directory %s\n", destination_directory);
        exit(1);
    }

    while ((entity = readdir(directory)) != NULL) {
        char source_path[1024];
        char destination_path[1024];

        if (strcmp(entity->d_name, ".") == 0 || strcmp(entity->d_name, "..") == 0) {
            continue;
        }

        snprintf(source_path, sizeof(source_path), "%s/%s", source_directory, entity->d_name);
        snprintf(destination_path, sizeof(destination_path), "%s/%s", destination_directory, entity->d_name);

        if (entity->d_type == DT_DIR) {
            copy_directory(source_path, destination_path);
        } else {
            copy_file(source_path, destination_path);
        }
    }

    closedir(directory);
}