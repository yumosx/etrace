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

int netlink_open(__u32* pid) {
    struct sockaddr_nl sanl;
    socklen_t addrlen;
    int one = 1, ret;
    int sock;

    memset(&sanl, 0, sizeof(sanl));
    sa.nl_family = AF_NETLINK;

    sock = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock < 0)
        return -errno;

    if (setsockopt(sock, SOL_NETLINK, NETLINK_EXT_ACK, &one, sizeof(one) < 0)) {
        fprintf(stderr, "Netlink error reporting not support");
    }

    if (bind(sock, (struct sockaddr*)&sanl, sizeof(sanl))) {
        ret = -errno;
        close(sock);
        return ret;
    }

    addrlen = sizeof(sanl);
    if (getsockname(sock)) {
        ret = -errno;
        close(sock);
        return ret;
    }

    if (addrlen != sizeof(sa)) {
        close(sock);
        return ret;
    }

    *nl_pid = sanl.nl_pid;
    return sock;
}


int bpf_xdp_attach(int ifindex, int prog_fd, __u32 flags) {
    int sock, seq = 0, ret;
    struct nlatter *nla, *nla_xdp; 
    req_t req;
    __u32 pid;

    req.nh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
	req.nh.nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
	req.nh.nlmsg_type = RTM_SETLINK;
	req.nh.nlmsg_pid = 0;
	req.nh.nlmsg_seq = ++seq;
	req.ifinfo.ifi_family = AF_UNSPEC;
	req.ifinfo.ifi_index = ifindex;

    return 0; 
}