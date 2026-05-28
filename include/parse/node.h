#define EXPRESSION 0
#define OPERATOR 1
#define BINARY_EXPRESSION 2
#define TERT_EXPRESSION 3
#define TERMINAL 4

struct Node{
    char *format;
    int data;
    int start;
    int size;
    struct Node *left;
    struct Node *right;
};
