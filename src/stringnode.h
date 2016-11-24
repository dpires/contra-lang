#ifndef STRING_NODE_H
#define STRING_NODE_H

#include "node.h"

typedef struct StringNode {
    char *text;
} StringNode;

Node *
StringNode_create(char *text);

void
StringNode_destroy(StringNode *stringNode);

Node *
StringNode_eval(Node *node);

#endif
