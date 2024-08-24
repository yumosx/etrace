#include "xdp.h"

#define LOG_BUF_SIZE 0x1000
char bpf_log_buf[LOG_BUF_SIZE];

static __u64 ptr_to_u64(const void* ptr) {
    return (__u64) (unsigned long) ptr;
}

int bpf_prog_load(enum bpf_prog_type type, const struct bpf_insn* insn, int insn_cnt)
{
    union bpf_attr attr = {
        .prog_type = type,
        .insns = ptr_to_u64(insns),
        .insn_cnt = insn_cnt,
        .license = ptr_to_u64("GPL"),
        .log_buf = ptr_to_u64(bpf_log_buf),
        .log_size = LOG_BUF_SIZE,
        .log_level = 1,
        .kern_version = LINUX_VERSION_CODE, 
    };

    return syscall(__NR_bpf, BPF_PROG_LOAD, &attr, sizeof(attr)); 
}

int bpf_xdp_attach(int ifindex, int prog_fd) {
    return 0;    
}