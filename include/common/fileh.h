#ifndef FILE_H
#define FILE_H

//cget.c
char* get_nth_line(const char* filename, int n, const char *keyword);

//file.c
void create_file(const char *filename, const char *content);
void print_file_content(const char* filename);
char *read_nth_content_from_file(const char *filename, int n);


#endif