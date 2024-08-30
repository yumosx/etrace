#ifndef INSN_H
#define INSN_H

#include <linux/bpf.h>

#define _ALIGN sizeof(int64_t)
#define _ALIGNED(_size) (((_size) + _ALIGN - 1) & ~(_ALIGN - 1))

#define INSN(_code, _dst, _src, _off, _imm) \
    ((struct bpf_insn){                     \
        .code = _code,                      \
        .dst_reg = _dst,                    \
        .src_reg = _src,                    \
        .off = _off,                        \
        .imm = _imm})


#define LDX(_size, _dst, _src, _off) \
    INSN(BPF_LDX|BPF_SIZE(_size)|BPF_MEM, _dst, _src, _off, 0)

#define STX(_size, _dst, _src, _off) \
    INSN(BPF_STX|BPF_SIZE(_size)|BPF_MEM, _dst, _src, _off, 0)

#define JUMP_REG(_op, _dst, _src, _offs) \
    INSN(BPF_JUMP32|BPF_OP(OP)|BPF_X, _dst, _src, _offs, 0)

#endif