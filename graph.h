#ifndef __GRAPH__
#define __GRAPH__

#define array_size(x) sizeof((x)) / sizeof((x)[0])

struct vw_s {
    bool set;
    size_t addr;
    struct block_s* block;
};


#endif