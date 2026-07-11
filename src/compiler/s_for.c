#define FOR_LOOP
#include <stdlib.h>
#include "compile/sh.h"


void for_condition(const char *fn, int *arr, int count){
    if (count != 7) return;
    char temp[C_PROGRAM_MAX] = "";
    const char *datatype = find_datatype(arr[ORDER_DATATYPE]);
    char *id = get_token(arr[ORDER_ID]);
    char *from = serialize(arr[ORDER_FROM_START], arr[ORDER_FROM_END]);
    char *to = serialize(arr[ORDER_TO_START], arr[ORDER_TO_END]);
    if (!datatype || !id || !from || !to) {
        free(id);
        free(from);
        free(to);
        return;
    }
    if (snprintf(temp, sizeof(temp), "for(%s %s = %s; %s <= %s; %s++){%s}",
        datatype,
        id,
        from,
        id,
        to,
        id,
        PGM_CURSOR
    ) >= (int)sizeof(temp)) {
        free(id);
        free(from);
        free(to);
        return;
    }
    char psuedo[PSUEDO_CODE_MAX];
    char descr[PSUEDO_CODE_MAX];
    get_description(datatype, descr);
    if (snprintf(psuedo, sizeof(psuedo), 
        "Start a for loop block by iterating a variable named"
        "%s with datatype which %s. Iterate from the value (%s) to the value (%s).",
        id,
        descr,
        from,
        to
    ) >= (int)sizeof(psuedo)) {
        free(id);
        free(from);
        free(to);
        return;
    }
    insert_before_target(fn, temp, PGM_CURSOR);
    fputs_with_newl(PARSED_INFORMATION, psuedo);
    free(id);
    free(from);
    free(to);
}
