#ifndef D_FH_H
#define D_FH_H

void init_stat();
int fputs_with_newl(const char *filename, const char *str);
char* fgets_by_nth_line(const char *filename, int n);

#endif 