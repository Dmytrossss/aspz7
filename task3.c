#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    FILE *file = fopen(argv[2], "r");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    while ((read = getline(&line, &len, file)) != -1) {
        if (strstr(line, argv[1])) 
            printf("%s", line);
    }
    
    free(line);
    fclose(file);
    return 0;
}
