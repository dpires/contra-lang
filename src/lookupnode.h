#ifndef LOOKUPNODE_H
#define LOOKUPNODE_H

#include "node.h"

typedef struct LookupNode {
    Node *varNode;
    Node *keyNode;
} LookupNode;


Node *
LookupNode_create(Node *varNode, Node *keyNode);

void
LookupNode_destroy(LookupNode *lookupNode);

Node *
LookupNode_eval(Node *lookupNode);

#endif
