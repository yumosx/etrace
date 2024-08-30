#include "xdp.h"
#include <errno.h>

#define LOG_BUF_SIZE 0x1000
char bpf_log_buf[LOG_BUF_SIZE];

static __u64 ptr_to_u64(const void* ptr) {
    return (__u64) (unsigned long) ptr;
}

static int _bpf(enum bpf_cmd cmd, union bpf_attr* attr) {
    int r = (int)syscall(__NR_bpf, cmd, attr, sizeof(*attr));
    if (r < 0)
        return -errno;
    
    return r;
}

int bpf_prog_load(enum bpf_prog_type type, const struct bpf_insn* insn, int insn_cnt) {
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

    return _bpf(BPF_PROG_LOAD, &attr);
}

int bpf_xdp_link_create(int prog_fd, int ifindex, int* link_fd, enum bpf_attach_type hook, int* link_fd) {
    union bpf_attr attr = {};
    int r;

    attr.link_create.prog_fd = prog_fd;
    attr.link_create.target_fd = ifindex;
    attr.link_create.attach_type = hook;

    r = _bpf(BPF_LINK_CREATE, &attr);
    if (r < 0)
        return r;
    *link_fd = r;
    
    return 0;
}

int bpf_xdp_link_update(int link_fd, int prog_fd) {
    union bpf_attr attr = {};

    attr.link_update.link_fd = link_fd;
    attr.link_update.new_prog_fd = prog_fd;

    return _bpf(BPF_LINK_UPDATE, &attr);
}