#include "xdp.h"

static vec_t* toks;
static int pos;

static void expect(int ty) {
    token_t* t = toks[pos]; 
    if (t->type != ty)
        error("expect error");    
    pos++;
}

static bool consume(int ty) {
    token_t* t = tok->data[pos];
    if (t->type != ty)
        return false;
    pos++;
    return true;
}