#ifndef TAMIZHI_COMPILER_H
#define TAMIZHI_COMPILER_H

#include "tamizhi_ast.h"
#include "tamizhi_chunk.h"
#include "tamizhi_errors.h"

void init_compiler();
void free_compiler();
int compile_ast(const ASTNode* root, TamizhiChunk* out_chunk);
TamizhiError get_compilation_error();

#endif