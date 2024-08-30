#include "xdp.h"
#include "insn.h"

void emit(prog_t* prog, struct bpf_insn insn) {
    *(prog->ip)++ = insn;
}

size_t bpf_size_to_size(int bs) {
    switch (bs) {
    case BPF_B:
        return 1;
    case BPF_H:
        return 2;
    case BPF_W:
        return 4;
    case BPF_DW:
        return 8;
    default:
        return 0;
    }
}

int emit_read(prog_t* prog, int bs, node_t* node) {
    size_t size;

    size = bpf_size_to_size(bs);
    emit(prog, LDX(bs, BPF_REG_0, BPF_REG_8, node->integer));
    return 0;
}

int prog_compile(prog_t* prog, node_t* node) {
    switch (node->type) {
    case TYPE_INT:
        emit(prog, MOV64_IMM(BPF_REG_0, node->integer));
        break;
    case TYPE_U8:
        emit_read(prog, BPF_W, node);
        break;
    case TYPE_U16:
        break;
    case TYPE_CASE:
        break;
    default:
        break;
    }
}

int prog_init(prog_t* prog) {
    emit(prog, LDX(BPF_W, BPF_REG_8, BPF_REG_1, 0));
    emit(prog, LDX(BPF_W, BPF_REG_9, BPF_REG_1, 4));
    emit(prog, MOV64_IMM(BPF_REG_0, XDP_DROP));
}

int prog_exit(prog_t* prog) {
    emit(prog, MOV64_IMM(BPF_REG_0, 0));
    emit(prog, EXIT);
    return 0;
}