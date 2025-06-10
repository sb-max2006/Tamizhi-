#include "tamizhi_value.h"
#include <stdlib.h>
#include <string.h>

TamizhiValue make_int(int v) {
    TamizhiValue val = { .type = VAL_INT, .as_int = v };
    return val;
}
TamizhiValue make_float(float v) {
    TamizhiValue val = { .type = VAL_FLOAT, .as_float = v };
    return val;
}
TamizhiValue make_string(const char *s) {
    TamizhiValue val = { .type = VAL_STRING };
    if (s) {
        val.as_string = malloc(strlen(s)+1);
        strcpy(val.as_string, s);
    } else {
        val.as_string = NULL;
    }
    return val;
}
TamizhiValue make_bool(bool b) {
    TamizhiValue val = { .type = VAL_BOOL, .as_bool = b };
    return val;
}
void free_value(TamizhiValue v) {
    if (v.type == VAL_STRING && v.as_string)
        free(v.as_string);
}