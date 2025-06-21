#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void set_raw_mode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void reset_terminal() {
    struct termios normal;
    tcgetattr(STDIN_FILENO, &normal);
    normal.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &normal);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    set_raw_mode();
    atexit(reset_terminal);
    
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            perror("fopen");
            continue;
        }
        
        printf("\n--- %s ---\n", argv[i]);
        char line[256];
        int line_count = 0;
        int c;
        
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            if (++line_count % 20 == 0) {
                printf("\n-- Press any key to continue (q to quit) --");
                fflush(stdout);
                c = getchar();
                if (c == 'q') break;
            }
        }
        fclose(file);
    }
    return 0;
}
