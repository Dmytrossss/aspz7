#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    uid_t uid = getuid();
    DIR *dir = opendir(".");
    if (!dir) return EXIT_FAILURE;
    
    struct dirent *entry;
    char *c_files[256];
    int count = 0;
    
    while ((entry = readdir(dir)) && count < 256) {
        char *dot = strrchr(entry->d_name, '.');
        if (dot && strcmp(dot, ".c") == 0) {
            struct stat st;
            if (stat(entry->d_name, &st) == -1) continue;
            if (st.st_uid == uid) {
                c_files[count++] = strdup(entry->d_name);
            }
        }
    }
    closedir(dir);
    
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i+1, c_files[i]);
    }
    
    for (int i = 0; i < count; i++) {
        printf("Grant read to others for %s? (y/n): ", c_files[i]);
        char response = getchar();
        while (getchar() != '\n');
        
        if (response == 'y' || response == 'Y') {
            struct stat st;
            stat(c_files[i], &st);
            chmod(c_files[i], st.st_mode | S_IROTH);
            printf("Permissions updated.\n");
        }
        free(c_files[i]);
    }
    return 0;
}
