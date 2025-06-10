#ifndef TAMIZHI_LINKER_H
#define TAMIZHI_LINKER_H

#include <stdbool.h>

typedef struct {
    char* name;
    char* filepath;
    bool is_loaded;
    bool is_stdlib;
} TamizhiModule;

typedef struct {
    TamizhiModule* modules;
    int module_count;
} TamizhiLinkerContext;

TamizhiLinkerContext* create_linker_context();
void destroy_linker_context(TamizhiLinkerContext* ctx);

bool add_module(TamizhiLinkerContext* ctx, const char* name, const char* filepath, bool is_stdlib);
bool is_module_loaded(TamizhiLinkerContext* ctx, const char* name);

bool link_all_modules(TamizhiLinkerContext* ctx);
void print_linked_modules(const TamizhiLinkerContext* ctx);

#endif // TAMIZHI_LINKER_H