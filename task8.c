#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dir = opendir(".");
    if (!dir) return EXIT_FAILURE;
    
    struct dirent *entry;
    char response;
    
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || 
            strcmp(entry->d_name, "..") == 0) continue;
        
        printf("Delete %s? (y/n): ", entry->d_name);
        response = getchar();
        while (getchar() != '\n');
        
        if (response == 'y' || response == 'Y') {
            if (unlink(entry->d_name) == 0) {
                printf("Deleted: %s\n", entry->d_name);
            } else {
                perror("unlink");
            }
        }
    }
    closedir(dir);
    return 0;
}
