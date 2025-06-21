#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_perms(mode_t mode) {
    char perms[11] = "----------";
    if (S_ISDIR(mode)) perms[0] = 'd';
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';
    printf("%s", perms);
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) return EXIT_FAILURE;
    
    struct dirent *entry;
    struct stat st;
    char time_buf[20];
    
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.') continue;
        
        if (stat(entry->d_name, &st) == -1) continue;
        
        print_perms(st.st_mode);
        printf(" %ld %s %s %8ld ", 
               (long)st.st_nlink,
               getpwuid(st.st_uid)->pw_name,
               getgrgid(st.st_gid)->gr_name,
               (long)st.st_size);
        
        strftime(time_buf, 20, "%b %d %H:%M", localtime(&st.st_mtime));
        printf("%s %s\n", time_buf, entry->d_name);
    }
    
    closedir(dir);
    return 0;
}
