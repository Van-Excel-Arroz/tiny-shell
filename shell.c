#include<stdio.h>
#include<string.h>

int main(void) {
    char line[1024];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(line, sizeof line, stdin) == NULL) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';
        printf("you typed: [%s]\n", line);
    }

    return 0;
}