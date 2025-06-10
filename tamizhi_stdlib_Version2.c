#include "tamizhi_stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// -----------------------------
// ✅ Core Utilities
// -----------------------------
void* tamizhi_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "[tamizhi_stdlib] Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void tamizhi_free(void* ptr) {
    free(ptr);
}

int tamizhi_atoi(const char* str) {
    return atoi(str);
}

char* tamizhi_itoa(int value, char* buffer, int base) {
    if (!buffer) return NULL;
    // assume buffer >= 32 bytes
    switch (base) {
        case 10: snprintf(buffer, 32, "%d", value); break;
        case 16: snprintf(buffer, 32, "%x", value); break;
        case 8:  snprintf(buffer, 32, "%o", value); break;
        default: snprintf(buffer, 32, "%d", value); break;
    }
    return buffer;
}

// -----------------------------
// ✅ Math Functions
// -----------------------------
double tamizhi_sin(double angle) { return sin(angle); }
double tamizhi_cos(double angle) { return cos(angle); }
double tamizhi_tan(double angle) { return tan(angle); }
double tamizhi_pow(double base, double exp) { return pow(base, exp); }
double tamizhi_sqrt(double value) { return sqrt(value); }

double tamizhi_log(double value) { return log(value); }
double tamizhi_exp(double value) { return exp(value); }
double tamizhi_floor(double value) { return floor(value); }
double tamizhi_ceil(double value)  { return ceil(value); }

// -----------------------------
// ✅ String Utilities
// -----------------------------
size_t tamizhi_strlen(const char* str) {
    return strlen(str);
}

char* tamizhi_strcpy(char* dest, const char* src) {
    return strcpy(dest, src);
}

int tamizhi_strcmp(const char* s1, const char* s2) {
    return strcmp(s1, s2);
}

char* tamizhi_strdup(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char* dup = tamizhi_malloc(len);
    memcpy(dup, s, len);
    return dup;
}

// -----------------------------
// ✅ IO Utilities
// -----------------------------
void tamizhi_print(const char* str) {
    fputs(str, stdout);
}

void tamizhi_println(const char* str) {
    fputs(str, stdout);
    fputc('\n', stdout);
}

char* tamizhi_readline(char* buffer, size_t size) {
    if (!fgets(buffer, (int)size, stdin)) return NULL;
    // strip newline
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
    return buffer;
}

// -----------------------------
// ✅ Character Utilities
// -----------------------------
int tamizhi_is_digit(char c) {
    return isdigit((unsigned char)c);
}

int tamizhi_is_alpha(char c) {
    return isalpha((unsigned char)c);
}

int tamizhi_to_upper(char c) {
    return toupper((unsigned char)c);
}

int tamizhi_to_lower(char c) {
    return tolower((unsigned char)c);
}