#include "tamizhi_compiler.h"
#include "tamizhi_errors.h"
#include "tamizhi_vm.h"
#include "tamizhi_ast.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // let a = 5;
    int val = 5;
    ASTNode *literal = create_literal_node(LITERAL_INT, &val, 1);
    ASTNode *decl = create_assignment_node("a", literal, 1);

    TamizhiChunk out_chunk;
    if (compile_ast(decl, &out_chunk)) {
        printf("Compilation successful!\n");
        // TODO: Run chunk with VM
    } else {
        TamizhiError err = get_compilation_error();
        print_error(&err);
    }
    free_compiler();
    free_chunk(&out_chunk);
    free_ast(decl);
    return 0;
}