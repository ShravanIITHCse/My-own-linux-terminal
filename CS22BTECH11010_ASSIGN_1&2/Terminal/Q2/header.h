#ifndef MAIN_H
#define MAIN_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<limits.h>
#include<errno.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<fcntl.h>
#include<ctype.h>

void myls(char* );
void mycp(char* ,char* ,char*);
void copy_file(char* , char* );
void copy_directory(char* , char* );
void mymv(char* , char* , char*);
void move_file(char *, char *);
void move_directory(char *, char *);
void myps(char *);
void get_process_info(char *, char *, char *, char *);
void mypse();
void mygrep(char*,char*,char*,char*);
//void myls1();
//void myls2();
//void myls3();
//void myls4();

#endif