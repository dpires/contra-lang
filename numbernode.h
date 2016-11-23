#ifndef NUMBERNODE_H
#define NUMBERNODE_H

#include "node.h"

typedef struct NumberNode {
    int value;
} NumberNode;


Node *
NumberNode_create(int value);

Node *
NumberNode_eval(Node *numberNode);

#endif
