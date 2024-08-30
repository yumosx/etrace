#include "xdp.h"

noreturn void error(char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

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

void vec_free(vec_t* v) {
    assert(v!=NULL);    
    free(v->data);
    free(v);
}

char* strerr(int err, char* dst, int len) {
	int ret = strerror_r(err, dst, len);
	if (ret)
		snprintf(dst, len, "ERROR: strerror_r(%d)=%d", err, ret);
	return dst;
}