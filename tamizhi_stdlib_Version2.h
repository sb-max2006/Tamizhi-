#ifndef TAMIZHI_STDLIB_H
#define TAMIZHI_STDLIB_H

#include <stddef.h>

// -----------------------------
// ✅ Core Utilities
// -----------------------------
void* tamizhi_malloc(size_t size);
void tamizhi_free(void* ptr);
int tamizhi_atoi(const char* str);
char* tamizhi_itoa(int value, char* buffer, int base);

// -----------------------------
// ✅ Math Functions
// -----------------------------
double tamizhi_sin(double angle);
double tamizhi_cos(double angle);
double tamizhi_tan(double angle);
double tamizhi_pow(double base, double exp);
double tamizhi_sqrt(double value);
double tamizhi_log(double value);
double tamizhi_exp(double value);
double tamizhi_floor(double value);
double tamizhi_ceil(double value);

// -----------------------------
// ✅ String Utilities
// -----------------------------
size_t tamizhi_strlen(const char* str);
char* tamizhi_strcpy(char* dest, const char* src);
int tamizhi_strcmp(const char* s1, const char* s2);
char* tamizhi_strdup(const char* s);

// -----------------------------
// ✅ IO Utilities
// -----------------------------
void tamizhi_print(const char* str);
void tamizhi_println(const char* str);
char* tamizhi_readline(char* buffer, size_t size);

// -----------------------------
// ✅ Character Utilities
// -----------------------------
int tamizhi_is_digit(char c);
int tamizhi_is_alpha(char c);
int tamizhi_to_upper(char c);
int tamizhi_to_lower(char c);

#endif // TAMIZHI_STDLIB_H