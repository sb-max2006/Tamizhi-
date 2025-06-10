#include "tamizhi_errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TamizhiError make_error(TamizhiErrorType type, const char* message, const char* filename, int line, int column) {
    TamizhiError err;
    err.type = type;
    err.message = strdup(message);
    err.filename = strdup(filename);
    err.line = line;
    err.column = column;
    return err;
}
void print_error(const TamizhiError* err) {
    if (!err || err->type == T_ERROR_NONE) return;
    fprintf(stderr, "Tamizhi Error [%s]: %s (File: %s, Line: %d, Col: %d)\n",
        get_error_type_name(err->type),
        err->message,
        err->filename ? err->filename : "<unknown>",
        err->line,
        err->column
    );
}
const char* get_error_type_name(TamizhiErrorType type) {
    switch (type) {
        case T_ERROR_NONE: return "None";
        case T_ERROR_SYNTAX: return "Syntax Error";
        case T_ERROR_TYPE: return "Type Error";
        case T_ERROR_RUNTIME: return "Runtime Error";
        case T_ERROR_MEMORY: return "Memory Error";
        case T_ERROR_LINK: return "Link Error";
        case T_ERROR_NAME: return "Name Error";
        case T_ERROR_IO: return "IO Error";
        case T_ERROR_CUSTOM: return "Custom Error";
        default: return "Unknown Error";
    }
}
TamizhiError clear_error() {
    TamizhiError err = { .type = T_ERROR_NONE, .message = NULL, .filename = NULL, .line = -1, .column = -1 };
    return err;
}
int is_error(TamizhiError err) {
    return err.type != T_ERROR_NONE;
}