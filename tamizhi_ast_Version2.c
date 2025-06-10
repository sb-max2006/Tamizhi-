#include "tamizhi_ast.h"
#include <stdlib.h>
#include <string.h>

static char* strdup_safe(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char* d = malloc(len);
    memcpy(d, s, len);
    return d;
}

ASTNode *create_literal_node(LiteralType type, void *value, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL;
    node->line = line;
    node->literal.type = type;
    switch (type) {
        case LITERAL_INT:
            node->literal.int_val = *(int *)value;
            break;
        case LITERAL_FLOAT:
            node->literal.float_val = *(float *)value;
            break;
        case LITERAL_STRING:
            node->literal.string_val = strdup_safe((char*)value);
            break;
        case LITERAL_BOOL:
            node->literal.bool_val = *(int *)value;
            break;
    }
    return node;
}

ASTNode *create_variable_node(const char *name, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_VARIABLE;
    node->line = line;
    node->variable_name = strdup_safe(name);
    return node;
}

ASTNode *create_assignment_node(const char *name, ASTNode *value, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_ASSIGNMENT;
    node->line = line;
    node->assignment.left = strdup_safe(name);
    node->assignment.right = value;
    return node;
}

ASTNode *create_binary_expr_node(BinaryOperator op, ASTNode *left, ASTNode *right, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY_EXPR;
    node->line = line;
    node->binary_expr.op = op;
    node->binary_expr.left = left;
    node->binary_expr.right = right;
    return node;
}

ASTNode *create_unary_expr_node(UnaryOperator op, ASTNode *operand, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_UNARY_EXPR;
    node->line = line;
    node->unary_expr.op = op;
    node->unary_expr.operand = operand;
    return node;
}

ASTNode *create_if_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_IF_STATEMENT;
    node->line = line;
    node->if_stmt.condition = condition;
    node->if_stmt.then_branch = then_branch;
    node->if_stmt.else_branch = else_branch;
    return node;
}

ASTNode *create_while_node(ASTNode *condition, ASTNode *body, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_WHILE_LOOP;
    node->line = line;
    node->while_loop.condition = condition;
    node->while_loop.body = body;
    return node;
}

ASTNode *create_for_node(ASTNode *init, ASTNode *condition, ASTNode *update, ASTNode *body, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_FOR_LOOP;
    node->line = line;
    node->for_loop.init = init;
    node->for_loop.condition = condition;
    node->for_loop.update = update;
    node->for_loop.body = body;
    return node;
}

ASTNode *create_function_call_node(const char *name, ASTNode **args, int arg_count, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_FUNCTION_CALL;
    node->line = line;
    node->function_call.function_name = strdup_safe(name);
    node->function_call.arguments = args;
    node->function_call.arg_count = arg_count;
    return node;
}

ASTNode *create_function_def_node(const char *name, char **params, int param_count, ASTNode *body, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_FUNCTION_DEF;
    node->line = line;
    node->function_def.function_name = strdup_safe(name);
    node->function_def.parameters = params;
    node->function_def.param_count = param_count;
    node->function_def.body = body;
    return node;
}

ASTNode *create_return_node(ASTNode *value, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_RETURN_STATEMENT;
    node->line = line;
    node->return_stmt.value = value;
    return node;
}

ASTNode *create_block_node(ASTNode **statements, int count, int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_BLOCK;
    node->line = line;
    node->block.statements = statements;
    node->block.statement_count = count;
    return node;
}

ASTNode *create_noop_node(int line) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_NOOP;
    node->line = line;
    return node;
}

// Free recursively
void free_ast(ASTNode *node) {
    if (!node) return;
    switch (node->type) {
        case AST_LITERAL:
            if (node->literal.type == LITERAL_STRING)
                free(node->literal.string_val);
            break;
        case AST_VARIABLE:
            free(node->variable_name);
            break;
        case AST_ASSIGNMENT:
            free(node->assignment.left);
            free_ast(node->assignment.right);
            break;
        case AST_BINARY_EXPR:
            free_ast(node->binary_expr.left);
            free_ast(node->binary_expr.right);
            break;
        case AST_UNARY_EXPR:
            free_ast(node->unary_expr.operand);
            break;
        case AST_IF_STATEMENT:
            free_ast(node->if_stmt.condition);
            free_ast(node->if_stmt.then_branch);
            free_ast(node->if_stmt.else_branch);
            break;
        case AST_WHILE_LOOP:
            free_ast(node->while_loop.condition);
            free_ast(node->while_loop.body);
            break;
        case AST_FOR_LOOP:
            free_ast(node->for_loop.init);
            free_ast(node->for_loop.condition);
            free_ast(node->for_loop.update);
            free_ast(node->for_loop.body);
            break;
        case AST_FUNCTION_CALL:
            free(node->function_call.function_name);
            for (int i = 0; i < node->function_call.arg_count; ++i)
                free_ast(node->function_call.arguments[i]);
            free(node->function_call.arguments);
            break;
        case AST_FUNCTION_DEF:
            free(node->function_def.function_name);
            for (int i = 0; i < node->function_def.param_count; ++i)
                free(node->function_def.parameters[i]);
            free(node->function_def.parameters);
            free_ast(node->function_def.body);
            break;
        case AST_RETURN_STATEMENT:
            free_ast(node->return_stmt.value);
            break;
        case AST_BLOCK:
            for (int i = 0; i < node->block.statement_count; ++i)
                free_ast(node->block.statements[i]);
            free(node->block.statements);
            break;
        case AST_NOOP:
            break;
    }
    free(node);
}