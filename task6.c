#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) return EXIT_FAILURE;
    
    char *dirs[256];
    int count = 0;
    struct dirent *entry;
    
    while ((entry = readdir(dir)) && count < 256) {
        if (entry->d_type == DT_DIR && 
            strcmp(entry->d_name, ".") != 0 && 
            strcmp(entry->d_name, "..") != 0) {
            dirs[count++] = strdup(entry->d_name);
        }
    }
    closedir(dir);
    
    qsort(dirs, count, sizeof(char *), compare);
    
    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }
    return 0;
}
