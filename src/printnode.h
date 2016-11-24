#ifndef PRINTNODE_H
#define PRINTNODE_H

#include "node.h"

enum PrintType {
    SAMELINE,
    NEWLINE
};

typedef struct PrintNode {
    Node *expression;
    int type;
} PrintNode;

Node *
PrintNode_create(Node *expression, int type);

void
PrintNode_destroy(PrintNode *printNode);

Node *
PrintNode_eval(Node *node);

#endif
