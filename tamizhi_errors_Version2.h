#ifndef TAMIZHI_ERRORS_H
#define TAMIZHI_ERRORS_H

typedef enum {
    T_ERROR_NONE = 0,
    T_ERROR_SYNTAX,
    T_ERROR_TYPE,
    T_ERROR_RUNTIME,
    T_ERROR_MEMORY,
    T_ERROR_LINK,
    T_ERROR_NAME,
    T_ERROR_IO,
    T_ERROR_CUSTOM
} TamizhiErrorType;

typedef struct {
    TamizhiErrorType type;
    const char* message;
    const char* filename;
    int line;
    int column;
} TamizhiError;

TamizhiError make_error(TamizhiErrorType type, const char* message, const char* filename, int line, int column);
void print_error(const TamizhiError* err);
const char* get_error_type_name(TamizhiErrorType type);
TamizhiError clear_error();
int is_error(TamizhiError err);

#endif