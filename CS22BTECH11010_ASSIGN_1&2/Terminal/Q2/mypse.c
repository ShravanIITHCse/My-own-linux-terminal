#include"header.h"

#define PROC_PATH "/proc/"
#define CMDLINE_FILE "cmdline"
#define STAT_FILE "stat"

void get_process_info(char *pid, char *tty, char *time, char *cmd) {
    char path[256];

    // Construct the path to the tty file
    sprintf(path, PROC_PATH "%s/fd/0", pid);
    readlink(path, tty, 256);

    // Construct the path to the stat file
    sprintf(path, PROC_PATH "%s/" STAT_FILE, pid);

    // Read the process state and start time from the file
    FILE *stat_file = fopen(path, "r");
    if (stat_file != NULL) {
        int utime, stime, cutime, cstime, start_time;
        char state;
        fscanf(stat_file, "%*d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %u %u %u %u %*d %*d %*d %d", &state, &utime, &stime, &cutime, &cstime, &start_time);
        fclose(stat_file);

        // Calculate the process elapsed time in seconds
        int elapsed_time = start_time / sysconf(_SC_CLK_TCK);

        // Convert the elapsed time to a human-readable format
        int hours = elapsed_time / 3600;
        int minutes = (elapsed_time % 3600) / 60;
        int seconds = elapsed_time % 60;
        sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
    } else {
        sprintf(time, "-");
    }

    // Construct the path to the cmdline file
    sprintf(path, PROC_PATH "%s/" CMDLINE_FILE, pid);

    // Read the command line from the file
    FILE *cmdline_file = fopen(path, "r");
    if (cmdline_file != NULL) {
        fgets(cmd, 256, cmdline_file);
        fclose(cmdline_file);

        // Remove any null characters from the command line
        for (int i = 0; i < strlen(cmd); i++) {
            if (cmd[i] == '\0') {
                cmd[i] = ' ';
            }
        }
    } else {
        sprintf(cmd, "-");
    }
}

void mypse() {
    DIR *dir;
    struct dirent *ent;

    printf("%-10s %-10s %-10s %s\n", "PID", "TTY", "TIME", "CMD");

    dir = opendir(PROC_PATH);
    if (dir == NULL) {
        perror("Error opening /proc/");
        exit(EXIT_FAILURE);
    }

    while ((ent = readdir(dir)) != NULL) {
        // Check if the entry is a process directory
        if (ent->d_type == DT_DIR && isdigit(ent->d_name[0])) {
            char tty[256], time[10], cmd[256];
            get_process_info(ent->d_name, tty, time, cmd);
            if(tty[0]=='\0') 
            tty[0]='?';
            printf("%-10s %-10s %-10s %s\n", ent->d_name, tty, time, cmd);
        }
    }

    closedir(dir);
}