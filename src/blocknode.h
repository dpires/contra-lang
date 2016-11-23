#ifndef BLOCKNODE_H
#define BLOCKNODE_H

#include "node.h"
#include "vector.h"

typedef struct BlockNode {
    Vector *statements;
} BlockNode;

Node *
BlockNode_create(Vector *statements);

Node *
BlockNode_get(BlockNode *blockNode, int index);

Vector *
BlockNode_getStatements(BlockNode *blockNode);

Node *
BlockNode_eval(Node *blockNode);

#endif
