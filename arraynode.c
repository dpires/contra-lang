#include <stdlib.h>
#include "node.h"
#include "nodetype.h"
#include "parser.h"
#include "arraynode.h"

Node *
ArrayNode_create(Vector *elements)
{
    ArrayNode *arrayNode = (ArrayNode *)malloc(sizeof(ArrayNode));
    arrayNode->elements = elements;

    Node *variant = Node_create(ARRAY_NODE);
    variant->arrayNode = arrayNode;

    return variant;
}

Node *
ArrayNode_eval(Node *arrayNode)
{
    Vector *items = Vector_create(arrayNode->arrayNode->elements->size);
    VIterator *it = Vector_getIterator(arrayNode->arrayNode->elements);
    Node *node;
    while ((node = VIterator_getNext(it)) != NULL) {
        Vector_add(items, Eval(node));
    }
    VIterator_destroy(it);
    return ArrayNode_create(items);
}
