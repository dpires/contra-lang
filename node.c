#include <stdlib.h>

#include "node.h"

Node *
Node_create(int nodeType)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->nodeType = nodeType;
    return node;
}
