#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "common/hash.h"



static Entry* load_table(const char *filename, size_t *entry_count) {
    FILE *fp = fopen(filename, "rb");
    size_t count = INITIAL_TABLE_SIZE;
    Entry *table = NULL;

    if (fp) {
        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (file_size > 0) {
            count = file_size / sizeof(Entry);
            if (count == 0) count = 1;  
        }
        table = calloc(count, sizeof(Entry));
        if (table) {
            size_t read_cnt = fread(table, sizeof(Entry), count, fp);
            (void)read_cnt; 
        }
        fclose(fp);
    } else {
        table = calloc(count, sizeof(Entry)); 
    }

    *entry_count = (table ? count : 0);
    return table;
}


static int save_table(const char *filename, const Entry *table, size_t entry_count) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return -1;
    size_t written = fwrite(table, sizeof(Entry), entry_count, fp);
    fclose(fp);
    return (written == entry_count) ? 0 : -1;
}


static int find_in_table(const Entry *table, size_t table_size, const char *name) {
    uint64_t h = hash_str(name);
    size_t start = h % table_size;

    for (size_t i = 0; i < table_size; ++i) {
        size_t idx = (start + i) % table_size;
        const Entry *e = &table[idx];

        if (e->name[0] == '\0')
            break;                 
        if (e->name[0] == DELETED_MARKER[0])
            continue;              
        if (strncmp(e->name, name, NAME_SIZE) == 0)
            return (int)idx;
    }
    return -1;
}


static int insert_into_table(Entry *table, size_t table_size, const char *name) {
    uint64_t h = hash_str(name);
    size_t start = h % table_size;
    int first_tombstone_idx = -1;

    for (size_t i = 0; i < table_size; ++i) {
        size_t idx = (start + i) % table_size;
        Entry *e = &table[idx];

        if (e->name[0] == '\0') {
            
            size_t target_idx = (first_tombstone_idx != -1) ? (size_t)first_tombstone_idx : idx;
            memset(table[target_idx].name, 0, NAME_SIZE);
            strncpy(table[target_idx].name, name, NAME_SIZE - 1);
            return 0; 
        }
        if (e->name[0] == DELETED_MARKER[0]) {
            if (first_tombstone_idx == -1) {
                first_tombstone_idx = (int)idx;
            }
            continue;
        }
        if (strncmp(e->name, name, NAME_SIZE) == 0) {
            return 1; 
        }
    }

    if (first_tombstone_idx != -1) {
        size_t target_idx = (size_t)first_tombstone_idx;
        memset(table[target_idx].name, 0, NAME_SIZE);
        strncpy(table[target_idx].name, name, NAME_SIZE - 1);
        return 0;
    }

    return -1;
}


static Entry* resize_table(const Entry *old_table, size_t old_size, size_t *new_size) {
    size_t new_sz = old_size * 2;
    Entry *new_table = calloc(new_sz, sizeof(Entry));
    if (!new_table) return NULL;

    for (size_t i = 0; i < old_size; ++i) {
        if (old_table[i].name[0] != '\0' && old_table[i].name[0] != DELETED_MARKER[0]) {
            uint64_t h = hash_str(old_table[i].name);
            size_t start = h % new_sz;
            size_t j;
            for (j = 0; j < new_sz; ++j) {
                size_t idx = (start + j) % new_sz;
                if (new_table[idx].name[0] == '\0' || new_table[idx].name[0] == DELETED_MARKER[0]) {
                    strncpy(new_table[idx].name, old_table[i].name, NAME_SIZE - 1);
                    new_table[idx].name[NAME_SIZE - 1] = '\0';
                    break;
                }
            }
        }
    }

    *new_size = new_sz;
    return new_table;
}

/* vscan – returns index of name, or -1 if not found */
int vscan(const char *filename, const char *name) {
    size_t entry_count;
    Entry *table = load_table(filename, &entry_count);
    if (!table) return -1;

    int idx = find_in_table(table, entry_count, name);
    free(table);
    return idx;
}

/* vadd – adds name if not present, returns 0 on success,
   1 if already exists, -1 on error.
   If the table is full, it is automatically resized. */
int vadd(const char *filename, const char *name) {
    size_t entry_count;
    Entry *table = load_table(filename, &entry_count);
    if (!table) return -1;

    int status = insert_into_table(table, entry_count, name);

    if (status == 0) {
        if (save_table(filename, table, entry_count) != 0)
            status = -1;
        free(table);
        return status;
    }

    if (status == 1) {
        free(table);
        return 1;
    }

    size_t new_size;
    Entry *new_table = resize_table(table, entry_count, &new_size);
    free(table);

    if (!new_table) return -1;

    status = insert_into_table(new_table, new_size, name);
    if (status == 0) {
        if (save_table(filename, new_table, new_size) != 0)
            status = -1;
    } else {
        status = -1;
    }

    free(new_table);
    return status;
}