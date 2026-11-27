#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void) {
    char line[1024];
    char *args[64];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(line, sizeof line, stdin) == NULL) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';
        int argc = 0;
        int i = 0;

        while (line[i] != '\0' && argc < 63) {
            while (line[i] == ' ' || line[i] == '\t') {
                line[i] = '\0';
                i++;
            }

            if (line[i] == '\0') {
                break;
            }

            args[argc] = &line[i];
            argc++;

            while (line[i] != ' ' && line[i] != '\t' &&line[i] != '\0') {
                i++;
            }
        }
        args[argc] = NULL;
        
        for (int j = 0; j < argc; j++) {
            printf("args[%d] = [%s]\n", j, args[j]);
        }

        if (argc == 0) {
            continue;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            // Child
            execvp(args[0], args);
            perror(args[0]);
            exit(1);
        }
        
        // Parent
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}