#include "tamizhi_chunk.h"
#include <stdlib.h>
#include <string.h>

void init_chunk(TamizhiChunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    chunk->constants_count = 0;
    chunk->constants_capacity = 0;
    chunk->constants = NULL;
}

void free_chunk(TamizhiChunk* chunk) {
    free(chunk->code);
    free(chunk->lines);
    for (int i = 0; i < chunk->constants_count; i++)
        free_value(chunk->constants[i]);
    free(chunk->constants);
    init_chunk(chunk);
}

void write_instruction(TamizhiChunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int old = chunk->capacity;
        chunk->capacity = old < 8 ? 8 : old * 2;
        chunk->code = realloc(chunk->code, chunk->capacity);
        chunk->lines = realloc(chunk->lines, chunk->capacity * sizeof(int));
    }
    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

int add_constant(TamizhiChunk* chunk, TamizhiValue value) {
    if (chunk->constants_capacity < chunk->constants_count + 1) {
        int old = chunk->constants_capacity;
        chunk->constants_capacity = old < 8 ? 8 : old * 2;
        chunk->constants = realloc(chunk->constants, chunk->constants_capacity * sizeof(TamizhiValue));
    }
    chunk->constants[chunk->constants_count] = value;
    return chunk->constants_count++;
}

void write_constant(TamizhiChunk* chunk, TamizhiValue value, int line) {
    int index = add_constant(chunk, value);
    write_instruction(chunk, OP_CONSTANT, line);
    write_instruction(chunk, (uint8_t)index, line);
}
void write_define_global(TamizhiChunk* chunk, int name_index, int line) {
    write_instruction(chunk, OP_DEFINE_GLOBAL, line);
    write_instruction(chunk, (uint8_t)name_index, line);
}
void write_get_global(TamizhiChunk* chunk, int name_index, int line) {
    write_instruction(chunk, OP_GET_GLOBAL, line);
    write_instruction(chunk, (uint8_t)name_index, line);
}
void write_set_global(TamizhiChunk* chunk, int name_index, int line) {
    write_instruction(chunk, OP_SET_GLOBAL, line);
    write_instruction(chunk, (uint8_t)name_index, line);
}