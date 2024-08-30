#ifndef BPF_LIB_H
#define BPF_LIB_H

#include <net/if.h>
#include <stdint.h>
#include "xdp.h"

#define CTX_OFF(filed) offsetof(struct bpf_context, fileld)

struct bpf_context {
    void* arg;
    uint64_t pkt_size;
 
    union {
        struct ethhdr _ethhdr;
        char l2_raw;
    };

    struct {
        uint32_t l3_offset;
        uint16_t l3_proto;
        union {
            struct iphdr _iphdr;
            char l3_raw;
        };
    };

    struct {
        uint32_t l4_offset;
        uint8_t l4_proto;

        union {
            struct icmphdr _icmphdr;
            struct udphdr _udphdr;
            struct tcphdr _tcphdr;
            char l4_raw;
        };
    };
}_aligned(8);


#endif