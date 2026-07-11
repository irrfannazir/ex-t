#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP_FILE "temp_file.tmp"

void insert_before_target(const char *filename, const char *new_content, const char *target_string) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error while reading the file %s for inserting the target\n", filename);
        return;
    }

    
    size_t buffer_size = 4096;
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }
    buffer[0] = '\0';

    char line[1024];
    size_t total_len = 0;
    while (fgets(line, sizeof(line), file)) {
        size_t line_len = strlen(line);
        while (total_len + line_len + 1 > buffer_size) {
            buffer_size *= 2;
            char *resized = realloc(buffer, buffer_size);
            if (!resized) {
                perror("Reallocation failed");
                free(buffer);
                fclose(file);
                return;
            }
            buffer = resized;
        }
        memcpy(buffer + total_len, line, line_len);
        total_len += line_len;
        buffer[total_len] = '\0';
    }

    fclose(file);

    char *pos = strstr(buffer, target_string);
    if (!pos) {
        printf("Target string not found in file.\n");
        free(buffer);
        return;
    }

    
    file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error while writing the file %s for inserting the target\n", filename);
        free(buffer);
        return;
    }

    
    size_t prefix_len = pos - buffer;
    char saved = buffer[prefix_len];
    buffer[prefix_len] = '\0';
    fputs(buffer, file);
    buffer[prefix_len] = saved;

    
    fputs(new_content, file);

    
    fputs(pos, file);

    fclose(file);
    free(buffer);
}
