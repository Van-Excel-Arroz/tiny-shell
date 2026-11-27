#include<stdio.h>
#include<string.h>

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
    }

    return 0;
}