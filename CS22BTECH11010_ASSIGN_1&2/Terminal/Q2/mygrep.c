#include"header.h"

#define MAX_LINE_LENGTH 1000

void mygrep(char *arguement0 , char *arguement1, char *arguement2,char *arguement3)
{
    if (arguement3!=NULL && (!(strcmp(arguement0,"-m"))))
    {
        int limit = atoi(arguement1);
        
        FILE *file = fopen(arguement3, "r");

        if (file == NULL) {
            printf("Error: Unable to open file %s\n", arguement3);
            exit(EXIT_FAILURE);
        }

        char line[MAX_LINE_LENGTH];
        int count=0;

        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            if (strstr(line, arguement2) != NULL) {
                count++;
                printf("%s", line);
            }
            if (count==limit) break;
            
        }
        fclose(file);
    }
    
    
    else if (arguement2!=NULL)
    {
        FILE *file = fopen(arguement2, "r");

        if (file == NULL) {
            printf("Error: Unable to open file %s\n", arguement2);
            exit(EXIT_FAILURE);
        }

        char line[MAX_LINE_LENGTH];

        if (!strcmp(arguement0,"-v"))
        {
            int line_no=1;
            while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
                if (strstr(line, arguement1) == NULL) {
                    printf("%s", line);            
                }line_no++;
            }
            printf("\n");
            fclose(file);
        }
        
        else
        {
        int line_no=1;
        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            if (strstr(line, arguement1) != NULL) {
                if(!strcmp(arguement0,"-n")) printf("%d:%s", line_no,line);
                else if(!strcmp(arguement0,"-o")) printf("%s\n", arguement1);            
            }line_no++;
        }
        fclose(file);
        }   
    }

    else if (!strcmp(arguement0,"--help"))
    {
        FILE *file = fopen("mygrep.txt", "r");

        if (file == NULL) {
            printf("Error: Unable to open file mygep.txt\n");
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
        FILE *file = fopen(arguement1, "r");

        if (file == NULL) {
            printf("Error: Unable to open file %s\n", arguement1);
            exit(EXIT_FAILURE);
        }

        char line[MAX_LINE_LENGTH];

        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            if (strstr(line, arguement0) != NULL) {
                printf("%s", line);
            }
        }
        fclose(file);
    }

   
}