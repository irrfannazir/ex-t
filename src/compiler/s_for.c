#define FOR_LOOP
#include "compile/sh.h"


void for_condition(int *arr, int count){
    static char temp[C_PROGRAM_MAX] = "";
    const char *datatype = find_datatype(arr[ORDER_DATATYPE]);
    const char *id = get_token(arr[ORDER_ID]);
    const char *from = serialize(arr[ORDER_FROM_START], arr[ORDER_FROM_END]);
    const char *to = serialize(arr[ORDER_TO_START], arr[ORDER_TO_END]);
    sprintf(temp, "for(%s %s = %s; %s <= %s; %s++){%s}",
        datatype,
        id,
        from,
        id,
        to,
        id,
        PGM_CURSOR
    );
    insert_before_target(PGM_EXATED_FILE_NAME, temp, PGM_CURSOR);
}