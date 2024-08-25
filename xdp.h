#ifndef XDP_H
#define XDP_H

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <linux/rtnetlink.h>

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