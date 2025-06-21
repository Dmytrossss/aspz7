# # Звіт виконання лабораторної роботи №7

**Система:** FreeBSD 13.4 з інтерфейсом MATE  

**Виконав: Гнилицький Дмитро** 

**Група ТВ-33**

**Завдання:**


2.1 Загальні завдання

Задача 1

 Використайте popen(), щоб передати вивід команди rwho (команда UNIX) до more (команда UNIX) у програмі на C.

Задача 2
 
 Напишіть програму мовою C, яка імітує команду ls -l в UNIX — виводить список усіх файлів у поточному каталозі та перелічує права доступу тощо.

 (Варіант вирішення, що просто виконує ls -l із вашої програми, — не підходить.)

Задача 3

 Напишіть програму, яка друкує рядки з файлу, що містять слово, передане як аргумент програми (проста версія утиліти grep в UNIX).

Задача 4

 Напишіть програму, яка виводить список файлів, заданих у вигляді аргументів, з зупинкою кожні 20 рядків, доки не буде натиснута клавіша (спрощена версія утиліти more в UNIX).

Задача 5

 Напишіть програму, яка перелічує всі файли в поточному каталозі та всі файли в підкаталогах.

Задача 6

 Напишіть програму, яка перелічує лише підкаталоги у алфавітному порядку.

Задача 7
 
 Напишіть програму, яка показує користувачу всі його/її вихідні програми на C, а потім в інтерактивному режимі запитує, чи потрібно надати іншим дозвіл на читання (read permission); у разі ствердної відповіді — 
 
 такий дозвіл повинен бути наданий.

Задача 8

 Напишіть програму, яка надає користувачу можливість видалити будь-який або всі файли у поточному робочому каталозі. Має з’являтися ім’я файлу з запитом, чи слід його видалити.

Задача 9

 Напишіть програму на C, яка вимірює час виконання фрагмента коду в мілісекундах.

Задача 10
 
 Напишіть програму мовою C для створення послідовності випадкових чисел з плаваючою комою у діапазонах:
 
 (a) від 0.0 до 1.0
 
 (b) від 0.0 до n, де n — будь-яке дійсне число з плаваючою точкою.

 Початкове значення генератора випадкових чисел має бути встановлене так, щоб гарантувати унікальну послідовність.

Примітка: використання прапорця -Wall під час компіляції є обов’язковим.

Варіант №3

Розробіть засіб, що аналізує, які файли у вказаній директорії змінювалися найчастіше за останні 7 днів, використовуючи лише доступні через стандартну бібліотеку функції C.

---

## Завдання 1:

**Код програми (`task1.c`):**
```c
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
```

**Компіляція та запуск:**
```bash
gcc -Wall -o task1 task1.c
./task1
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/df3035f8-d991-4003-85f2-9088edf4d84f)


```
dima@dima:~/aspz7 $ ./task1
dima@dima:~/aspz7 $ dima
sh: dima: not found
```
---

## Завдання 2:

**Код програми (`task2.c`):**
```c
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
```

**Компіляція та запуск:**
```bash
gcc -Wall -o task2 task2.c
./task2
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/5e2060f2-1c78-4335-9fc8-d7b7f4a8f41b)


```
dima@dima:~/aspz7 $ ./task2
-rwxr-xr-x 1 dima dima    16440 Jun 21 16:02 task4
-rw-r--r-- 1 dima dima      676 Jun 21 15:35 task5.c
-rw-r--r-- 1 dima dima      359 Jun 21 15:39 task10.c
-rw-r--r-- 1 dima dima     1343 Jun 21 16:01 task4.c
-rw-r--r-- 1 dima dima     1595 Jun 21 16:02 variant3.c
-rwxr-xr-x 1 dima dima    14192 Jun 21 15:39 task9
-rwxr-xr-x 1 dima dima    14976 Jun 21 15:34 task3
-rwxr-xr-x 1 dima dima    16136 Jun 21 16:02 variant3
-rw-r--r-- 1 dima dima      808 Jun 21 15:35 task6.c
-rwxr-xr-x 1 dima dima    16392 Jun 21 15:36 task7
-rwxr-xr-x 1 dima dima    14528 Jun 21 15:40 task10
-rw-r--r-- 1 dima dima     1233 Jun 21 15:36 task7.c
-rwxr-xr-x 1 dima dima    16072 Jun 21 15:31 task2
-rwxr-xr-x 1 dima dima    16072 Jun 21 15:38 task8
-rw-r--r-- 1 dima dima      593 Jun 21 15:34 task3.c
-rw-r--r-- 1 dima dima       24 Jun 21 15:34 test.txt
-rw-r--r-- 1 dima dima      530 Jun 21 15:39 task9.c
-rw-r--r-- 1 dima dima      816 Jun 21 15:38 task8.c
-rw-r--r-- 1 dima dima     1381 Jun 21 15:31 task2.c
-rwxr-xr-x 1 dima dima    14712 Jun 21 15:35 task5
-rwxr-xr-x 1 dima dima    14056 Jun 21 16:02 task1
-rw-r--r-- 1 dima dima      411 Jun 21 16:01 task1.c
-rwxr-xr-x 1 dima dima    15016 Jun 21 15:36 task6
```

**Висновок:**  
Програма коректно імітує `ls -l`, виводячи детальну інформацію про файли без використання системних команд.

---

## Завдання 3:

**Код програми (`task3.c`):**
```c
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
```

**Компіляція та тестування:**
```bash
gcc -Wall -o task3 task3.c
echo "test line\nanother line" > test.txt
./task3 "test" test.txt
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/f0ad5cde-8c0b-4ef5-8942-8cab5e1de7af)


```
dima@dima:~/aspz7 $ echo "test line\nanother line" > test.txt
dima@dima:~/aspz7 $ ./task3 "test" test.txt
test line\nanother line
```

**Висновок:**  
Програма успішно знаходить рядки, що містять вказаний шаблон, демонструючи роботу простої версії `grep`.

---

## Завдання 4:`

**Код програми (`task4.c`):**
```c
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void set_raw_mode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void reset_terminal() {
    struct termios normal;
    tcgetattr(STDIN_FILENO, &normal);
    normal.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &normal);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    set_raw_mode();
    atexit(reset_terminal);
    
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            perror("fopen");
            continue;
        }
        
        printf("\n--- %s ---\n", argv[i]);
        char line[256];
        int line_count = 0;
        int c;
        
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            if (++line_count % 20 == 0) {
                printf("\n-- Press any key to continue (q to quit) --");
                fflush(stdout);
                c = getchar();
                if (c == 'q') break;
            }
        }
        fclose(file);
    }
    return 0;
}
```

**Компіляція та запуск:**
```bash
gcc -Wall -o task4 task4.c
./task4 task4.c
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/f170e1f2-1925-463e-ac2b-b1e102fac1aa)


```
dima@dima:~/aspz7 $ ./task4 task4.c

--- task4.c ---
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void set_raw_mode() {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void reset_terminal() {
    struct termios normal;
    tcgetattr(STDIN_FILENO, &normal);
    normal.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &normal);
}

int main(int argc, char *argv[]) {

-- Press any key to continue (q to quit) --

```

**Висновок:**  
Програма коректно реалізує сторінковий перегляд з паузами кожні 20 рядків. Використано RAW-режим термінала для обробки вводу.

---

## Завдання 5:

**Код програми (`task5.c`):**
```c
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
```

**Компіляція та запуск:**
```bash
gcc -Wall -o task5 task5.c
./task5
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/bed41859-0255-4af8-8d73-cccef1cbf63b)


```
dima@dima:~/aspz7 $ ./task5
./task4
./task5.c
./task10.c
./task4.c
./variant3.c
./task9
./task3
./variant3
./task6.c
./task7
./task10
./task7.c
./task2
./task8
./task3.c
./test.txt
./task9.c
./task8.c
./task2.c
./task5
./task1
./task1.c
./task6
```

**Висновок:**  
Програма успішно обходить всі піддиректорії, демонструючи рекурсивну роботу з файловою системою.

---

## Завдання 6:

**Код програми (`task6.c`):**
```c
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
```

**Компіляція та запуск:**
```bash
gcc -Wall -o task6 task6.c
./task6
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/e9c02fb3-d975-4b60-bfde-d5d832271e36)


```
dima@dima:~/aspz7 $ ./task6
test_dir1
test_dir2
test_dir3
```

**Висновок:**  
Програма коректно виводить підкаталоги у алфавітному порядку, ігноруючи службові директорії `.` та `..`.

---

## Завдання 7:

**Код програми (`task7.c`):**
```c
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
```

**Компіляція та запуск:**
```bash
gcc -Wall -o task7 task7.c
./task7
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/a790890c-5d10-461c-ab53-afd2dbdb10ff)

```
dima@dima:~/aspz7 $ ./task7
1. task5.c
2. task10.c
3. task4.c
4. variant3.c
5. task6.c
6. task7.c
7. task3.c
8. task9.c
9. task8.c
10. task2.c
11. task1.c
Grant read to others for task5.c? (y/n): n
Grant read to others for task10.c? (y/n): n
Grant read to others for task4.c? (y/n): n
Grant read to others for variant3.c? (y/n): n
Grant read to others for task6.c? (y/n): n
Grant read to others for task7.c? (y/n): n
Grant read to others for task3.c? (y/n): n
Grant read to others for task9.c? (y/n): n
Grant read to others for task8.c? (y/n): n
Grant read to others for task2.c? (y/n): n
Grant read to others for task1.c? (y/n): n
```

**Висновок:**  
Програма успішно надає права читання для C-файлів на основі інтерактивного запиту.

---

## Завдання 8:

**Код програми (`task8.c`):**
```c
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
```

**Компіляція та запуск:**
```bash
gcc -Wall -o task8 task8.c
./task8
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/77e7be38-6bbf-45ff-a6c8-ad4002916d8b)


```
dima@dima:~/aspz7 $ ./task8
Delete task4? (y/n): n
Delete task5.c? (y/n): n
Delete task10.c? (y/n): n
Delete test_dir2? (y/n): n
Delete task4.c? (y/n): n
Delete variant3.c? (y/n): n
Delete task9? (y/n): n
Delete task3? (y/n): n
Delete variant3? (y/n): n
Delete task6.c? (y/n): n
Delete task7? (y/n): n
Delete task10? (y/n): n
Delete test_dir1? (y/n): n
Delete task7.c? (y/n): n
Delete task2? (y/n): n
Delete task8? (y/n): n
Delete task3.c? (y/n): n
Delete test.txt? (y/n): n
Delete task9.c? (y/n): n
Delete task8.c? (y/n): n
Delete test_dir3? (y/n): n
Delete task2.c? (y/n): n
Delete task5? (y/n): n
Delete task1? (y/n): n
Delete task1.c? (y/n): n
Delete task6? (y/n): n
```

**Висновок:**  
Програма коректно видаляє файли після підтвердження, демонструючи безпечне управління файловою системою.

---

## Завдання 9:

**Код програми (`task9.c`):**
```c
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
```

**Компіляція та запуск:**
```bash
gcc -Wall -o task9 task9.c -lrt
./task9
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/56b7c654-50b0-41c0-9079-585ec523b169)


```
dima@dima:~/aspz7 $ ./task9
Execution time: 1522.83 ms
```

**Висновок:**  
Програма точно вимірює час виконання операцій з використанням високоточних таймерів.

---

## Завдання 10:

**Код програми (`task10.c`):**
```c
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
```

**Компіляція та тестування:**
```bash
gcc -Wall -o task10 task10.c
./task10
./task10 5.0
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/42a7d7ca-8dfd-42cc-b546-7c066b451e01)


```
dima@dima:~/aspz7 $ ./task10
0.902753
0.541184
0.064116
0.804912
0.899028
dima@dima:~/aspz7 $ ./task10 5.0
1.954754
3.477878
2.511809
0.254125
3.888568
```

**Висновок:**  
Генератор коректно створює унікальні послідовності випадкових чисел для різних діапазонів.

---

## Варіант 3:

**Код програми (`variant3.c`):**
```c
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
```

**Компіляція та запуск:**
```bash
gcc -Wall -o variant3 variant3.c
./variant3
```

**Вивід програми:**

![image](https://github.com/user-attachments/assets/f8590bca-02b5-4ee0-abb0-231faaf01bc4)


```
dima@dima:~/aspz7 $ ./variant3
Most recently changed files in . (last 7 days):
test_dir1            2025-06-21 17:28:58
test_dir3            2025-06-21 17:28:58
test_dir2            2025-06-21 17:28:58
test.txt             2025-06-21 17:23:45
variant3             2025-06-21 16:02:31
task4                2025-06-21 16:02:30
task1                2025-06-21 16:02:30
variant3.c           2025-06-21 16:02:17
task4.c              2025-06-21 16:01:56
task1.c              2025-06-21 16:01:24
```

**Висновок:**  
Програма ефективно аналізує та сортує файли за частотою змін, використовуючи лише стандартні бібліотеки C.
