#include <stdlib.h>
#include "node.h"
#include "nodetype.h"
#include "parser.h"
#include "ifnode.h"
#include "numbernode.h"
#include <stdio.h>


Node *
IfNode_create(Node *condition, Node *thenBlock, Node *elseBlock)
{
    IfNode *ifNode = (IfNode *)malloc(sizeof(IfNode));
    ifNode->condition = condition;
    ifNode->thenBlock = thenBlock;
    ifNode->elseBlock = elseBlock;

    Node *variant = Node_create(IF_NODE);
    variant->ifNode = ifNode;

    return variant;
}

void
IfNode_destroy(IfNode *ifNode)
{
    Release(ifNode->condition);
    if (ifNode->thenBlock != NULL) {
        Release(ifNode->thenBlock);
    }

    if (ifNode->elseBlock != NULL) {
        Release(ifNode->elseBlock);
    }

    free(ifNode);
}

Node *
IfNode_eval(Node *ifNode)
{
    Node *ret = NULL;
    Node *condition;
    int result;

    if (ifNode->ifNode->condition != NULL &&
        ifNode->ifNode->thenBlock != NULL) {
        condition = Eval(ifNode->ifNode->condition);
        result = condition->numberNode->value; 
        if (result) {
            return Eval(ifNode->ifNode->thenBlock);
        }
    }

    if (ifNode->ifNode->condition != NULL &&
        ifNode->ifNode->elseBlock != NULL) {
        condition = Eval(ifNode->ifNode->condition);
        result = condition->numberNode->value; 
        if (!result) {
            return Eval(ifNode->ifNode->elseBlock);
        }
    }

    return ret;
}
