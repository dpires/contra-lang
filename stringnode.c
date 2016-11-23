#include <stdlib.h>
#include <stdio.h>

#include "node.h"
#include "nodetype.h"
#include "stringnode.h"

Node *
StringNode_create(char *text)
{
    StringNode *stringNode = (StringNode *)malloc(sizeof(StringNode));
    stringNode->text = text;

    Node *variant = Node_create(STRING_NODE);
    variant->stringNode = stringNode;

    return variant;
}

Node *
StringNode_eval(Node *node)
{
    return node;
}
