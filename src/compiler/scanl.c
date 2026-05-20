#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 40

int *line_to_int_array(const char *line, int *count) {
    int *arr = NULL;
    int capacity = CAPACITY;
    int value;
    *count = 0;

    arr = malloc(capacity * sizeof(int));
    if (!arr) return NULL;

    const char *p = line;

    while (*p) {
        // Skip whitespace
        while (*p == ' ' || *p == '\t') p++;

        if (*p == '\0' || *p == '\n') break;

        // Read an integer
        if (sscanf(p, "%d", &value) == 1) {
            if (*count >= capacity) {
                capacity *= 2;
                arr = realloc(arr, capacity * sizeof(int));
                if (!arr) return NULL;
            }
            arr[*count] = value;
            (*count)++;

            // Move p past this number
            while (*p && *p != ' ' && *p != '\t' && *p != '\n') p++;
        } else {
            // Invalid token, skip it
            while (*p && *p != ' ' && *p != '\t' && *p != '\n') p++;
        }
    }

    return arr;
}
