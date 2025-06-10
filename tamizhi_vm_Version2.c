#include "tamizhi_vm.h"
#include <stdio.h>

void tamizhi_vm_init(TamizhiVM *vm) {
    vm->sp = 0;
}

void tamizhi_vm_free(TamizhiVM *vm) {
    for (int i = 0; i < vm->sp; ++i)
        free_value(vm->stack[i]);
}

static void print_value(TamizhiValue v) {
    switch (v.type) {
        case VAL_INT: printf("%d", v.as_int); break;
        case VAL_FLOAT: printf("%f", v.as_float); break;
        case VAL_STRING: printf("%s", v.as_string); break;
        case VAL_BOOL: printf("%s", v.as_bool ? "true" : "false"); break;
    }
}

void tamizhi_vm_run(TamizhiVM *vm, TamizhiChunk *chunk) {
    int ip = 0;
    while (ip < chunk->count) {
        uint8_t op = chunk->code[ip++];
        switch (op) {
            case OP_CONSTANT: {
                int idx = chunk->code[ip++];
                vm->stack[vm->sp++] = chunk->constants[idx];
                break;
            }
            case OP_ADD: {
                TamizhiValue b = vm->stack[--vm->sp];
                TamizhiValue a = vm->stack[--vm->sp];
                if (a.type == VAL_INT && b.type == VAL_INT)
                    vm->stack[vm->sp++] = make_int(a.as_int + b.as_int);
                break;
            }
            case OP_PRINT: {
                TamizhiValue v = vm->stack[--vm->sp];
                print_value(v);
                printf("\n");
                free_value(v);
                break;
            }
            case OP_RETURN:
                return;
            default:
                printf("Unknown opcode: %d\n", op);
                return;
        }
    }
}