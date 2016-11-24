#include <stdlib.h>
#include "parser.h"
#include "node.h"
#include "nodetype.h"
#include "whilenode.h"
#include "numbernode.h"


Node *
WhileNode_create(Node *condition, Node *body)
{
    WhileNode *whileNode = (WhileNode *)malloc(sizeof(WhileNode));
    whileNode->condition = condition;
    whileNode->body = body;

    Node *variant = Node_create(WHILE_NODE);
    variant->whileNode = whileNode;

    return variant;
}

void
WhileNode_destroy(WhileNode *whileNode)
{
    Release(whileNode->condition);
    Release(whileNode->body);
    free(whileNode);
}


Node *
WhileNode_eval(Node *whileNode)
{
    Node *ret = NULL;

    Node *res = Eval(whileNode->whileNode->condition);
    int result = res->numberNode->value;
    while (result) {
        res = Eval(whileNode->whileNode->condition);
        result = res->numberNode->value;
        ret =  Eval(whileNode->whileNode->body);
        
    }

    return ret;
}
