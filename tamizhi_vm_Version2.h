#ifndef TAMIZHI_VM_H
#define TAMIZHI_VM_H

#include "tamizhi_chunk.h"
#include "tamizhi_value.h"

typedef struct {
    TamizhiValue stack[256];
    int sp;
} TamizhiVM;

void tamizhi_vm_init(TamizhiVM *vm);
void tamizhi_vm_free(TamizhiVM *vm);
void tamizhi_vm_run(TamizhiVM *vm, TamizhiChunk *chunk);

#endif