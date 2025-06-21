#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

#define SECONDS_IN_7_DAYS (7 * 24 * 3600)

typedef struct {
    char name[256];
    time_t mtime;
} FileInfo;

int compare(const void *a, const void *b) {
    return ((FileInfo*)b)->mtime - ((FileInfo*)a)->mtime;
}

int main(int argc, char *argv[]) {
    const char *path = argc > 1 ? argv[1] : ".";
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return EXIT_FAILURE;
    }
    
    FileInfo files[256];
    int count = 0;
    time_t now = time(NULL);
    struct dirent *entry;
    
    while ((entry = readdir(dir)) && count < 256) {
        if (entry->d_name[0] == '.') continue;
        
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        struct stat st;
        if (lstat(full_path, &st) == -1) continue;
        
        if (now - st.st_mtime <= SECONDS_IN_7_DAYS) {
            strncpy(files[count].name, entry->d_name, 255);
            files[count].name[255] = '\0';
            files[count].mtime = st.st_mtime;
            count++;
        }
    }
    closedir(dir);
    
    qsort(files, count, sizeof(FileInfo), compare);
    
    printf("Most recently changed files in %s (last 7 days):\n", path);
    for (int i = 0; i < (count > 10 ? 10 : count); i++) {
        char time_buf[80];
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&files[i].mtime));
        printf("%-20s %s\n", files[i].name, time_buf);
    }
    return 0;
}
