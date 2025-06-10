#ifndef TAMIZHI_CHUNK_H
#define TAMIZHI_CHUNK_H

#include "tamizhi_value.h"
#include <stdint.h>

typedef enum {
    OP_CONSTANT,
    OP_DEFINE_GLOBAL,
    OP_GET_GLOBAL,
    OP_SET_GLOBAL,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_PRINT,
    OP_RETURN
} OpCode;

typedef struct {
    uint8_t* code;
    int* lines;
    int count;
    int capacity;

    TamizhiValue* constants;
    int constants_count;
    int constants_capacity;
} TamizhiChunk;

void init_chunk(TamizhiChunk* chunk);
void free_chunk(TamizhiChunk* chunk);
int add_constant(TamizhiChunk* chunk, TamizhiValue constant);
void write_instruction(TamizhiChunk* chunk, uint8_t byte, int line);
void write_constant(TamizhiChunk* chunk, TamizhiValue value, int line);
void write_define_global(TamizhiChunk* chunk, int name_index, int line);
void write_get_global(TamizhiChunk* chunk, int name_index, int line);
void write_set_global(TamizhiChunk* chunk, int name_index, int line);

#endif