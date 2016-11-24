#include <stdlib.h>
#include "node.h"
#include "nodetype.h"
#include "parser.h"
#include "blocknode.h"
#include "vector.h"
#include <stdio.h>


Node *
BlockNode_create(Vector *statements)
{
    BlockNode *blockNode = (BlockNode *)malloc(sizeof(BlockNode));
    blockNode->statements = statements;

    Node *variant = Node_create(BLOCK_NODE);
    variant->blockNode = blockNode;

    return variant;
}

void
BlockNode_destroy(BlockNode *blockNode)
{
    VIterator *it = Vector_getIterator(blockNode->statements);
    Node *node;
    while ((node = VIterator_getNext(it)) != NULL) {
        Release(node);
    }
    VIterator_destroy(it);
    Vector_destroy(blockNode->statements);
    free(blockNode);
}

Node *
BlockNode_get(BlockNode *blockNode, int index)
{
    return Vector_get(blockNode->statements, index);
}

Vector *
BlockNode_getStatements(BlockNode *blockNode)
{
    return blockNode->statements;
}

Node *
BlockNode_eval(Node *blockNode)
{
    Node *ret;
    VIterator *it = Vector_getIterator(blockNode->blockNode->statements);
    Node *node;
    while ((node = VIterator_getNext(it)) != NULL) {
        ret = Eval(node);
    }
    VIterator_destroy(it);
    return ret;
}
