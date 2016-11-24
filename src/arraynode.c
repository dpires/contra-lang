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

void
ArrayNode_destroy(ArrayNode *arrayNode)
{
    VIterator *it = Vector_getIterator(arrayNode->elements);
    Node *node;
    while ((node = VIterator_getNext(it)) != NULL) {
        Release(node);
    }
    VIterator_destroy(it);
    Vector_destroy(arrayNode->elements);
    free(arrayNode);
}

Node *
ArrayNode_eval(Node *arrayNode)
{
    return arrayNode;
}
