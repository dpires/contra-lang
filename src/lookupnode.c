#include <stdlib.h>
#include "node.h"
#include "nodetype.h"
#include "parser.h"
#include "numbernode.h"
#include "variablenode.h"
#include "lookupnode.h"
#include "arraynode.h"

Node *
LookupNode_create(Node *varNode, Node *keyNode)
{
    LookupNode *lookupNode = (LookupNode *)malloc(sizeof(LookupNode));
    lookupNode->varNode = varNode;
    lookupNode->keyNode = keyNode;

    Node *variant = Node_create(LOOKUP_NODE);
    variant->lookupNode = lookupNode;

    return variant;
}

Node *
LookupNode_eval(Node *lookupNode)
{
    Node *ret = lookupNode;
    Node *indexNode = Eval(lookupNode->lookupNode->keyNode);
    int index = indexNode->numberNode->value;
    Node *var = Eval(lookupNode->lookupNode->varNode);
    ret = Vector_get(var->arrayNode->elements, index);

    return ret;
}
