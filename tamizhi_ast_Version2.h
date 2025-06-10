#ifndef TAMIZHI_AST_H
#define TAMIZHI_AST_H

typedef enum {
    AST_LITERAL,
    AST_VARIABLE,
    AST_ASSIGNMENT,
    AST_BINARY_EXPR,
    AST_UNARY_EXPR,
    AST_IF_STATEMENT,
    AST_WHILE_LOOP,
    AST_FOR_LOOP,
    AST_BLOCK,
    AST_FUNCTION_DEF,
    AST_FUNCTION_CALL,
    AST_RETURN_STATEMENT,
    AST_NOOP
} ASTNodeType;

typedef enum {
    LITERAL_INT,
    LITERAL_FLOAT,
    LITERAL_STRING,
    LITERAL_BOOL
} LiteralType;

typedef enum {
    UNARY_NEGATE,
    UNARY_NOT
} UnaryOperator;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_LTE,
    OP_GT,
    OP_GTE,
    OP_AND,
    OP_OR
} BinaryOperator;

typedef struct {
    LiteralType type;
    union {
        int int_val;
        float float_val;
        char *string_val;
        int bool_val;
    };
} LiteralValue;

struct ASTNode;

typedef struct ASTNode {
    ASTNodeType type;
    int line;
    union {
        LiteralValue literal;

        char *variable_name;

        struct {
            char *left;
            struct ASTNode *right;
        } assignment;

        struct {
            BinaryOperator op;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary_expr;

        struct {
            UnaryOperator op;
            struct ASTNode *operand;
        } unary_expr;

        struct {
            struct ASTNode *condition;
            struct ASTNode *then_branch;
            struct ASTNode *else_branch;
        } if_stmt;

        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_loop;

        struct {
            struct ASTNode *init;
            struct ASTNode *condition;
            struct ASTNode *update;
            struct ASTNode *body;
        } for_loop;

        struct {
            char *function_name;
            struct ASTNode **arguments;
            int arg_count;
        } function_call;

        struct {
            char *function_name;
            char **parameters;
            int param_count;
            struct ASTNode *body;
        } function_def;

        struct {
            struct ASTNode *value;
        } return_stmt;

        struct {
            struct ASTNode **statements;
            int statement_count;
        } block;
    };
} ASTNode;

// Node creation functions
ASTNode *create_literal_node(LiteralType type, void *value, int line);
ASTNode *create_variable_node(const char *name, int line);
ASTNode *create_assignment_node(const char *name, ASTNode *value, int line);
ASTNode *create_binary_expr_node(BinaryOperator op, ASTNode *left, ASTNode *right, int line);
ASTNode *create_unary_expr_node(UnaryOperator op, ASTNode *operand, int line);
ASTNode *create_if_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch, int line);
ASTNode *create_while_node(ASTNode *condition, ASTNode *body, int line);
ASTNode *create_for_node(ASTNode *init, ASTNode *condition, ASTNode *update, ASTNode *body, int line);
ASTNode *create_function_call_node(const char *name, ASTNode **args, int arg_count, int line);
ASTNode *create_function_def_node(const char *name, char **params, int param_count, ASTNode *body, int line);
ASTNode *create_return_node(ASTNode *value, int line);
ASTNode *create_block_node(ASTNode **statements, int count, int line);
ASTNode *create_noop_node(int line);

// Destroy/free AST tree
void free_ast(ASTNode *node);

#endif