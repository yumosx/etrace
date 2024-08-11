#ifndef __EXDP__
#define __EXDP__

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//  token
typedef enum token_type {
    TOKEN_CONST,
    TOKEN_HEX,
    TOKEN_NUMBER,
    TOKEN_CASE,     //?
    TOKEN_ARROW,    //->
    TOKEN_MATCH,    //=
    TOKEN_U8,    //u8
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

/// ast node
typedef struct match_s {
    size_t op;
    struct expr_s* expr;
} match_t;


typedef struct arm_s {
    struct match_s* macth;
    struct expr_s* expr;
    struct arm_s* next;
    struct vertex_s* then_v;
} arm_t;


enum expr_type_e {
    EXPR_TYPE_CONST,
    EXPR_TYPE_READ_U8,
    EXPR_TYPE_READ_U16,
    EXPR_TYPE_TEST,
};


//bpf insn
typedef struct block_s {
    size_t len;
    struct bpf_insn insns[];
} block_t;




typedef struct vec_t {
    int len;
    int cap;
    void** data;   
} vec_t;

vec_t* vec_new();
void vec_push(vec_t* vec, void* elem);
#endif