#include "xdp.h"

vec_t* vec_new() {
    vec_t* vec = malloc(sizeof(*vec));
    vec->len = 0;
    vec->cap = 16;
    vec->data = malloc(sizeof(void*) * 16);
    return vec;
}

void vec_push(vec_t *v, void *elem) {
    if (v->len == v->cap) {
        v->cap *= 2;
        v->data = realloc(v->data, sizeof(void *) * v->cap);
    }
    v->data[v->len++] = elem;
}