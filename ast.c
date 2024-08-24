#include "xdp.h"

node_t* node_new(type_t type) {
    node_t* node = malloc(sizeof(node));
    
    node->type = type;
    return node;
}

node_t* node_expr() {
    node_t* node = node_new(NODE_EXPR);
    return node;
}