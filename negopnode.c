#include <stdlib.h>

#include "nodetype.h"
#include "node.h"
#include "negopnode.h"
#include "numbernode.h"

Node *
NegOpNode_create(Node *node)
{
//    NegOpNode *negOpNode = (NegOpNode *)malloc(sizeof(NegOpNode));
    NumberNode *numberNode = (NumberNode *)malloc(sizeof(NumberNode));
    //yypnegOpNode->value = node->numberNode->value;
    numberNode->value = -node->numberNode->value;

    Node *variant = Node_create(NUMBER_NODE);
    variant->numberNode = numberNode;

    return variant;
}

Node *
NegOpNode_eval(Node *node)
{
    return node;
}
