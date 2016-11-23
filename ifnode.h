#ifndef IFNODE_H
#define IFNODE_H

#include "node.h"

typedef struct IfNode {
    Node *condition;
    Node *thenBlock;
    Node *elseBlock;
} IfNode;

Node *
IfNode_create(Node *condition, Node *thenBlock, Node *elseBlock);

Node *
IfNode_eval(Node *ifNode);

#endif
