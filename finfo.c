// Chance Mason, System Calls, CPE 2600 morning

// finfo.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("File Type: Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("File Type: Directory\n");
    } else if (S_ISCHR(mode)) {
        printf("File Type: Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("File Type: Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("File Type: FIFO (named pipe)\n");
    } else if (S_ISLNK(mode)) {
        printf("File Type: Symbolic link\n");
    } else if (S_ISSOCK(mode)) {
        printf("File Type: Socket\n");
    } else {
        printf("File Type: Unknown\n");
    }
}

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    const char *file_name = argv[1];
    struct stat file_stat;

    if (stat(file_name, &file_stat) == -1) {
        perror("stat");
        return 1;
    }

    // Print file type
    print_file_type(file_stat.st_mode);

    // Print permissions
    print_permissions(file_stat.st_mode);

    // Print owner
    printf("Owner (UID): %d\n", file_stat.st_uid);

    // Print size
    printf("Size: %ld bytes\n", file_stat.st_size);

    // Print last modification time
    char time_str[100];
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Last Modification: %s\n", time_str);

    return 0;
}