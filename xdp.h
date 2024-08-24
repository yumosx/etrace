#ifndef __EXDP__
#define __EXDP__

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <linux/rtnetlink.h>

//  token
typedef enum token_type {
    TOKEN_CONST,
    TOKEN_HEX,
    TOKEN_NUMBER,
    TOKEN_CASE,     //?
    TOKEN_ARROW,    //->
    TOKEN_MATCH,    //=
    TOKEN_U8,       //u8
    TOKEN_U16,      //u16
    TOKEN_DROP,     //drop
    TOKEN_PASS,     //pass
    TOKEN_AT,       //@
    TOKEN_EQ,       //=
    TOKEN_EOF,
} token_type;

typedef struct token_t {
    char* name;
    token_type type;
} token_t;

enum expr_type_e {
    EXPR_TYPE_CONST,
    EXPR_TYPE_READ_U8,
    EXPR_TYPE_READ_U16,
    EXPR_TYPE_TEST,
};

typedef enum {
    NODE_VAR,
    NODE_INT,
} type_t;

typedef struct node_t {
    type_t type;
} node_t;

typedef struct req_t{
    struct nlmsghdr nhdr;
    struct ifinfomsg ifinfo;
    char buf[64];
} req_t;

typedef struct vec_t {
    int len;
    int cap;
    void** data;   
} vec_t;

vec_t* vec_new();
void vec_push(vec_t* vec, void* elem);
#endif