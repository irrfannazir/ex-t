#ifndef COMPILE_H
#define COMPILE_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <process.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

static inline int last_command(char *const argv[]){
    if (argv == NULL || argv[0] == NULL) {
        fprintf(stderr, "No command provided.\n");
        return 1;
    }

#ifdef _WIN32
    int result = _spawnvp(_P_WAIT, argv[0], (const char *const *)argv);
    if (result == -1) {
        perror("Failed to start compiler");
        return 1;
    }
#else
    pid_t pid = fork();
    if (pid == -1) {
        perror("Failed to start compiler");
        return 1;
    }
    if (pid == 0) {
        execvp(argv[0], argv);
        perror("Failed to execute compiler");
        _exit(127);
    }

    int status = 0;
    if (waitpid(pid, &status, 0) == -1) {
        perror("Failed to wait for compiler");
        return 1;
    }
    int result = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
#endif

    if (result == 0) {
        printf("Compilation successful. Executable is created\n");
    } else {
        printf("Compilation failed.\n");
    }
    return result;
}

int compilef(const char *src_filename, const char *final_filename, const char *dest_filename);
int flushf();

#endif
