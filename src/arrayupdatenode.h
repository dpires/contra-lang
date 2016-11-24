#ifndef ARRAYUPDATENODE_H
#define ARRAYUPDATENODE_H

#include "node.h"


typedef struct ArrayUpdateNode {
    Node *arrayNode;
    Node *indexExpression;
    Node *rightSideExpression;
} ArrayUpdateNode;

Node *
ArrayUpdateNode_create(Node *arrayNode, Node *indexExpression, Node *rightSideExpression);

void
ArrayUpdateNode_destroy(ArrayUpdateNode *arrayUpdateNode);

Node *
ArrayUpdateNode_eval(Node *arrayUpdateNode);

#endif
