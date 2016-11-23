#include <stdlib.h>
#include "node.h"
#include "nodetype.h"
#include "vector.h"
#include "arraynode.h"
#include "numbernode.h"
#include "arrayupdatenode.h"
#include "parser.h"

Node *
ArrayUpdateNode_create(Node *arrayNode, Node *indexExpression, Node *rightSideExpression)
{
    ArrayUpdateNode *arrayUpdateNode = (ArrayUpdateNode *)malloc(sizeof(ArrayUpdateNode));
    arrayUpdateNode->arrayNode = arrayNode;
    arrayUpdateNode->indexExpression = indexExpression;
    arrayUpdateNode->rightSideExpression = rightSideExpression;

    Node *variant = Node_create(ARRAYUPDATE_NODE);
    variant->arrayUpdateNode = arrayUpdateNode;

    return variant;
}

Node *
ArrayUpdateNode_eval(Node *arrayUpdateNode)
{
    Node *arrayVariable = Eval(arrayUpdateNode->arrayUpdateNode->arrayNode);
    Node *indexExpression = Eval(arrayUpdateNode->arrayUpdateNode->indexExpression);
    int index = indexExpression->numberNode->value;
    Node *newValue = Eval(arrayUpdateNode->arrayUpdateNode->rightSideExpression);

    Vector_set(arrayVariable->arrayNode->elements, newValue, index);

    return arrayUpdateNode;
}
