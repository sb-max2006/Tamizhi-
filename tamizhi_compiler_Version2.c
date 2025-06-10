#include "tamizhi_compiler.h"
#include "tamizhi_value.h"
#include <string.h>
#include <stdlib.h>

static TamizhiError last_error;

static void set_error(const char* msg, int line) {
    last_error = make_error(T_ERROR_SYNTAX, msg, "<internal>", line, 0);
}

TamizhiError get_compilation_error() {
    return last_error;
}

void init_compiler() {
    last_error = clear_error();
}

void free_compiler() {}

static int dummy_global_index(const char* name) {
    // TODO: real symbol table
    return (int)name[0];
}

static int compile_node(const ASTNode *node, TamizhiChunk *chunk);

int compile_ast(const ASTNode *root, TamizhiChunk *out_chunk) {
    init_chunk(out_chunk);
    if (!compile_node(root, out_chunk)) return 0;
    write_instruction(out_chunk, OP_RETURN, root->line);
    return 1;
}

static int compile_node(const ASTNode *node, TamizhiChunk *chunk) {
    switch (node->type) {
        case AST_LITERAL:
            switch (node->literal.type) {
                case LITERAL_INT:
                    write_constant(chunk, make_int(node->literal.int_val), node->line);
                    break;
                case LITERAL_FLOAT:
                    write_constant(chunk, make_float(node->literal.float_val), node->line);
                    break;
                case LITERAL_STRING:
                    write_constant(chunk, make_string(node->literal.string_val), node->line);
                    break;
                case LITERAL_BOOL:
                    write_constant(chunk, make_bool(node->literal.bool_val), node->line);
                    break;
            }
            return 1;
        case AST_VARIABLE:
            write_get_global(chunk, dummy_global_index(node->variable_name), node->line);
            return 1;
        case AST_ASSIGNMENT:
            if (!compile_node(node->assignment.right, chunk)) return 0;
            write_define_global(chunk, dummy_global_index(node->assignment.left), node->line);
            return 1;
        case AST_BINARY_EXPR:
            if (!compile_node(node->binary_expr.left, chunk)) return 0;
            if (!compile_node(node->binary_expr.right, chunk)) return 0;
            switch (node->binary_expr.op) {
                case OP_ADD: write_instruction(chunk, OP_ADD, node->line); break;
                case OP_SUB: write_instruction(chunk, OP_SUB, node->line); break;
                case OP_MUL: write_instruction(chunk, OP_MUL, node->line); break;
                case OP_DIV: write_instruction(chunk, OP_DIV, node->line); break;
                default: set_error("Unsupported binary operator", node->line); return 0;
            }
            return 1;
        default:
            set_error("Unsupported AST node", node->line);
            return 0;
    }
}