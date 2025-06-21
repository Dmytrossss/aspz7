#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *pipe = popen("who | more", "r");
    if (!pipe) {
        perror("popen");
        return EXIT_FAILURE;
    }
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), pipe) {
        printf("%s", buffer);
    }
    
    pclose(pipe);
    return 0;
}
