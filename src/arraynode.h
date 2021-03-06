#ifndef ARRAYNODE_H
#define ARRAYNODE_H

#include "node.h"
#include "vector.h"

typedef struct ArrayNode {
    Vector *elements;
} ArrayNode;

Node *
ArrayNode_create(Vector *elements);

void
ArrayNode_destroy(ArrayNode *arrayNode);

Node *
ArrayNode_eval(Node *arrayNode);

#endif
