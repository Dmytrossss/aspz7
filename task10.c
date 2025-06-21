#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    srand(time(NULL) ^ (getpid() << 16));
    
    int n = 5;
    float max = 1.0f;
    
    if (argc == 2) max = atof(argv[1]);
    
    for (int i = 0; i < n; i++) {
        printf("%f\n", (float)rand() / RAND_MAX * max);
    }
    return 0;
}
