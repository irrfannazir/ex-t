#define INITIAL_TABLE_SIZE 32
#define NAME_SIZE          64
#define DELETED_MARKER "\x01"

typedef struct {
    char name[NAME_SIZE];
} Entry;

static unsigned long long hash_str(const char *s) {
    unsigned long long h = 14695981039346656037ULL;
    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 1099511628211ULL;
    }
    return h;
}