#ifndef TAMIZHI_VALUE_H
#define TAMIZHI_VALUE_H

#include <stdbool.h>

typedef enum {
    VAL_INT,
    VAL_FLOAT,
    VAL_STRING,
    VAL_BOOL
} TamizhiValueType;

typedef struct {
    TamizhiValueType type;
    union {
        int as_int;
        float as_float;
        char *as_string;
        bool as_bool;
    };
} TamizhiValue;

TamizhiValue make_int(int v);
TamizhiValue make_float(float v);
TamizhiValue make_string(const char *s);
TamizhiValue make_bool(bool b);
void free_value(TamizhiValue v);

#endif