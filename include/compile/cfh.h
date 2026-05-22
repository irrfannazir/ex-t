#ifndef CFH_H
#define CFH_H

void insert_before_target(const char *filename, const char *new_content, const char *target_string);
void remove_string_from_file(const char *filename, const char *target, int isloop);


#endif