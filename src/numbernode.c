#include <stdlib.h>

#include "nodetype.h"
#include "node.h"
#include "numbernode.h"

Node *
NumberNode_create(int value)
{
    NumberNode *numberNode = (NumberNode *)malloc(sizeof(NumberNode));
    numberNode->value = value;

    Node *variant = Node_create(NUMBER_NODE);
    variant->numberNode = numberNode;

    return variant;
}

void
NumberNode_destroy(NumberNode *numberNode)
{
    free(numberNode);
}

Node *
NumberNode_eval(Node *numberNode)
{
    return numberNode;
}
