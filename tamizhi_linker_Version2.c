#include "tamizhi_linker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TamizhiLinkerContext* create_linker_context() {
    TamizhiLinkerContext* ctx = malloc(sizeof(TamizhiLinkerContext));
    ctx->modules = NULL;
    ctx->module_count = 0;
    return ctx;
}

void destroy_linker_context(TamizhiLinkerContext* ctx) {
    if (!ctx) return;
    for (int i = 0; i < ctx->module_count; ++i) {
        free(ctx->modules[i].name);
        free(ctx->modules[i].filepath);
    }
    free(ctx->modules);
    free(ctx);
}

bool add_module(TamizhiLinkerContext* ctx, const char* name, const char* filepath, bool is_stdlib) {
    if (is_module_loaded(ctx, name)) return false;
    ctx->modules = realloc(ctx->modules, sizeof(TamizhiModule) * (ctx->module_count + 1));
    TamizhiModule* mod = &ctx->modules[ctx->module_count];
    mod->name = strdup(name);
    mod->filepath = strdup(filepath);
    mod->is_loaded = false;
    mod->is_stdlib = is_stdlib;
    ctx->module_count++;
    return true;
}

bool is_module_loaded(TamizhiLinkerContext* ctx, const char* name) {
    for (int i = 0; i < ctx->module_count; ++i) {
        if (strcmp(ctx->modules[i].name, name) == 0) {
            return ctx->modules[i].is_loaded;
        }
    }
    return false;
}

bool link_all_modules(TamizhiLinkerContext* ctx) {
    if (!ctx || ctx->module_count == 0) return false;
    for (int i = 0; i < ctx->module_count; ++i) {
        TamizhiModule* mod = &ctx->modules[i];
        printf("🔗 Linking module: %s (%s)\n", mod->name, mod->filepath);
        // TODO: Parse + Compile each module file here
        mod->is_loaded = true;
    }
    return true;
}

void print_linked_modules(const TamizhiLinkerContext* ctx) {
    if (!ctx) return;
    printf("\n📦 Linked Modules:\n");
    for (int i = 0; i < ctx->module_count; ++i) {
        TamizhiModule* mod = &ctx->modules[i];
        printf("  - %s [%s] %s\n", mod->name, mod->filepath, mod->is_stdlib ? "(stdlib)" : "");
    }
}