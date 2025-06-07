#include "tamizhi_compiler.h"
#include "tamizhi_errors.h"
#include "tamizhi_vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------
// ✅ உள்ளமைவு அமைப்புகள்
// ---------------------------

typedef struct {
    TamizhiChunk* chunk;
    TamizhiError last_error;
} CompilerState;

static CompilerState state;

// ---------------------------
// ✅ Compiler Initialization
// ---------------------------

void init_compiler() {
    state.chunk = create_chunk();
    state.last_error = clear_error();
}

void free_compiler() {
    free_chunk(state.chunk);
}

// ---------------------------
// ✅ Error Handling
// ---------------------------

bool has_compilation_error() {
    return is_error(state.last_error);
}

TamizhiError get_compilation_error() {
    return state.last_error;
}

void set_compilation_error(const char* message, const char* file, int line, int col) {
    state.last_error = make_error(T_ERROR_SYNTAX, message, file, line, col);
}

// ---------------------------
// ✅ AST Compilation Entry
// ---------------------------

bool compile_ast(const ASTNode* root, TamizhiChunk* out_chunk) {
    init_compiler();

    if (!compile_node(root)) {
        return false;
    }

    *out_chunk = *state.chunk;
    return true;
}

// ---------------------------
// ✅ Individual AST Nodes
// ---------------------------

bool compile_node(const ASTNode* node) {
    switch (node->type) {
        case AST_LITERAL_INT:
            write_constant(state.chunk, make_int(node->int_value), node->line);
            return true;

        case AST_LITERAL_STRING:
            write_constant(state.chunk, make_string(node->string_value), node->line);
            return true;

        case AST_VAR_DECL:
            // Example: let a = 5
            if (!compile_node(node->value)) return false;
            write_define_global(state.chunk, node->name, node->line);
            return true;

        case AST_VAR_ASSIGN:
            if (!compile_node(node->value)) return false;
            write_set_global(state.chunk, node->name, node->line);
            return true;

        case AST_VAR_ACCESS:
            write_get_global(state.chunk, node->name, node->line);
            return true;

        case AST_BINARY_OP:
            if (!compile_node(node->left)) return false;
            if (!compile_node(node->right)) return false;
            return compile_binary_op(node);

        case AST_PRINT:
            if (!compile_node(node->value)) return false;
            write_instruction(state.chunk, OP_PRINT, node->line);
            return true;

        default:
            set_compilation_error("அறியப்படாத நொடிக்கணுக்காட்சி (AST node)", "<internal>", node->line, 0);
            return false;
    }
}

// ---------------------------
// ✅ Binary Operator Compilation
// ---------------------------

bool compile_binary_op(const ASTNode* node) {
    switch (node->op) {
        case OP_ADD: write_instruction(state.chunk, OP_ADD, node->line); return true;
        case OP_SUB: write_instruction(state.chunk, OP_SUB, node->line); return true;
        case OP_MUL: write_instruction(state.chunk, OP_MUL, node->line); return true;
        case OP_DIV: write_instruction(state.chunk, OP_DIV, node->line); return true;
        default:
            set_compilation_error("தவறான பைனரி செயலி", "<internal>", node->line, 0);
            return false;
    }
}
