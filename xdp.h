#ifndef XDP_H
#define XDP_H

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <assert.h>
#include <stdnoreturn.h>
#include <linux/rtnetlink.h>
#include <linux/bpf.h>


#define _size(arr) sizeof(arr) / sizeof(arr[0])

//  token
typedef enum token_type {
    TOKEN_CONST = 1,
    TOKEN_HEX,
    TOKEN_IDENT,
    TOKEN_NUMBER,
    TOKEN_CASE,     //case
    TOKEN_END,      //end
    TOKEN_ARROW,    //->
    TOKEN_EQ,       //=
    TOKEN_U8,       //u8
    TOKEN_U16,      //u16
    TOKEN_DROP,     //drop
    TOKEN_PASS,     //pass
    TOKEN_SEMICOLON, //;
    TOKEN_MC,       //#
    TOKEN_LPARN,
    TOKEN_RPARN,
    TOKEN_EOF,
} token_type;

typedef struct token_t {
    char* str;
    token_type type;
} token_t;


typedef struct kw {
    char* name;
    token_type type;
} kw_t;

enum expr_type_e {
    EXPR_TYPE_CONST,
    EXPR_TYPE_READ_U8,
    EXPR_TYPE_READ_U16,
    EXPR_TYPE_TEST,
};

/// node 
typedef enum type_t{
    TYPE_VAR,
    TYPE_INT,
} type_t;

typedef struct iff_t {

} iff_t;

typedef struct node_t {
    type_t type;
    char* name;
    union {
        int integer;
        iff_t iff;
    };
} node_t;

/// net
enum xdp_attach_mode {
    XDP_MODE_SKB = XDP_FLAGS_SKB_MODE,
    XDP_MODE_DRV = XDP_FLAGS_DRV_MODE,
    XDP_MODE_HW = XDP_FLAGS_HW_MODE,
};

enum hook {
    BF_HOOK_NFT_INGRESS,
    BF_HOOK_TC_INGRESS,
    BF_HOOK_IPT_PRE_ROUTINE,
};

typedef struct prog_t {
    char* name;
    uint32_t ifindex;
    enum hook h;
    int prog_fd;
    struct bpf_insn* img;
} prog_t;

/// ut
typedef struct vec_t {
    int len;
    int cap;
    void** data;   
} vec_t;

noreturn void error(char* fmt, ...);
vec_t* vec_new();
void vec_push(vec_t* vec, void* elem);
void vec_free(vec_t* vec);

#endif