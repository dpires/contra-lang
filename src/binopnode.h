#ifndef BINOPNODE_H
#define BINOPNODE_H

#include "node.h"

typedef struct BinOpNode {
    int op;
    Node *left;
    Node *right;
    Node *eval;
} BinOpNode;

Node *
BinOpNode_create(int op, Node *left, Node *right);

void
BinOpNode_destroy(BinOpNode *binOpNode);

Node *
BinOpNode_eval(Node *binOpNode);

#endif
