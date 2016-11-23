#ifndef BINOPNODE_H
#define BINOPNODE_H

#include "node.h"

typedef struct BinOpNode {
    int op;
    Node *left;
    Node *right;
} BinOpNode;

Node *
BinOpNode_create(int op, Node *left, Node *right);

Node *
BinOpNode_eval(Node *binOpNode);

#endif
