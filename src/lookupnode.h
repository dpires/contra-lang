#ifndef LOOKUPNODE_H
#define LOOKUPNODE_H

#include "node.h"

typedef struct LookupNode {
    Node *varNode;
    Node *keyNode;
} LookupNode;


Node *
LookupNode_create(Node *varNode, Node *keyNode);

Node *
LookupNode_eval(Node *lookupNode);

#endif
