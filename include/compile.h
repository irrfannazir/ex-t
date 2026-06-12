#ifndef COMPILE_H
#define COMPILE_H

static inline int last_command(char *command){
    int result = system(command);

    if (result == 0) {
        printf("Compilation successful. Executable is created");
    } else {
        printf("Compilation failed.\n");
    }
    return result;
}

int compilef(const char *src_filename, const char *final_filename, const char *dest_filename);
int flushf();

#endif