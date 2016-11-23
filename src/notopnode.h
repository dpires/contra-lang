#ifndef NOTOPNODE_H
#define NOTOPNODE_H

#include "node.h"

typedef struct NotOpNode {
    int value;
} NotOpNode;


Node *
NotOpNode_create(Node *node);

Node *
NotOpNode_eval(Node *node);

#endif
