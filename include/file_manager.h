#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <sys/types.h> // mode_t için gerekli

void list_directory(const char *path);
void copy_file(const char *source, const char *destination);
void delete_folder(const char *folder_name);
void change_permissions(const char *path, mode_t mode);
void log_operation(const char *operation, const char *details, int success);

#endif // FILE_MANAGER_H