#ifndef STRING_NODE_H
#define STRING_NODE_H

#include "node.h"

typedef struct StringNode {
    char *text;
} StringNode;

Node *
StringNode_create(char *text);

Node *
StringNode_eval(Node *node);

#endif
