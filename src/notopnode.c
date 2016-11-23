#include <stdlib.h>

#include "nodetype.h"
#include "node.h"
#include "notopnode.h"
#include "numbernode.h"

Node *
NotOpNode_create(Node *node)
{
    NumberNode *numberNode = (NumberNode *)malloc(sizeof(NumberNode));
    numberNode->value = !node->numberNode->value;

    Node *variant = Node_create(NUMBER_NODE);
    variant->numberNode = numberNode;

    return variant;
}

Node *
NotOpNode_eval(Node *node)
{
    return node;
}
