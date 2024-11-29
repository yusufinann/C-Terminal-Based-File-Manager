#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "file_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "file_manager.h"

void delete_folder(const char *folder_name) {
    DIR *dir = opendir(folder_name);
    if (!dir) {
        perror("Unable to open directory");
        return;
    }

    struct dirent *entry;
    char path[1024];

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", folder_name, entry->d_name);

        struct stat stat_buf;
        if (stat(path, &stat_buf) == 0) {
            if (S_ISDIR(stat_buf.st_mode)) {
                // Recursive call for directories
                delete_folder(path);
            } else {
                // Remove file
                if (unlink(path) != 0) {
                    perror("Failed to delete file");
                }
            }
        }
    }

    closedir(dir);

    // Remove the empty directory
    if (rmdir(folder_name) != 0) {
        perror("Failed to delete directory");
    } else {
        printf("Deleted folder: %s\n", folder_name);
    }
}

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Unable to open directory");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == 0) {
            printf("%s - %ld bytes\n", entry->d_name, file_stat.st_size);
        } else {
            perror("Error getting file info");
        }
    }
    closedir(dir);
}