#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return;
    
    struct dirent *entry;
    char full_path[1024];
    
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.') continue;
        
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        printf("%s\n", full_path);
        
        struct stat st;
        if (lstat(full_path, &st) == -1) continue;
        if (S_ISDIR(st.st_mode)) 
            list_files(full_path);
    }
    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}
