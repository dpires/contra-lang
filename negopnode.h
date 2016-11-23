#ifndef NEGOPNODE_H
#define NEGOPNODE_H

#include "node.h"

typedef struct NegOpNode {
    int value;
} NegOpNode;


Node *
NegOpNode_create(Node *node);

Node *
NegOpNode_eval(Node *node);

#endif
