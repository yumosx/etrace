#include "xdp.h"

node_t* node_new(type_t type) {
    node_t* n = malloc(sizeof(*n));
    n->type = type;

    return n;
}

node_t* node_const_new(int integer) {
    node_t* n = node_new(TYPE_INT);
    
    n->integer = integer;
    return n;
}

node_t* node_read_u8_new(int integer) {
    node_t* n = node_new(TYPE_U8);

    n->integer = integer;
    return n;
}

node_t* node_read_u16_new(int integer) {
    node_t* n = node_new(TYPE_U16);

    n->integer = integer;
    return n;
}

node_t* node_match_new(size_t op, node_t* expr) {
    node_t* n = node_new(TYPE_MATCH);
    
    n->match.op = op;
    n->match.value = expr;
    return n;
}

node_t* node_expr_new(size_t* op, node_t* left, node_t* right) {
    node_t* n = node_new(TYPE_EXPR);

    n->expr.op = op;
    n->expr.left = left;
    n->expr.right = right;
    return n;
}

node_t* node_cond_new(node_t* match, node_t* stmts) {
    node_t* n = node_new(TYPE_COND);
    
    n->cond.prev = match;
    n->cond.stmts = stmts;
    return n;
}