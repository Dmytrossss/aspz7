#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Тестовий код
    usleep(1500000);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    long long elapsed_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + 
                          (end.tv_nsec - start.tv_nsec);
    double elapsed_ms = elapsed_ns / 1000000.0;
    
    printf("Execution time: %.2f ms\n", elapsed_ms);
    return 0;
}
