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

Node *
IfNode_eval(Node *ifNode)
{
    Node *ret = NULL;

    if (ifNode->ifNode->condition != NULL &&
        ifNode->ifNode->thenBlock != NULL) {
        Node *condition = Eval(ifNode->ifNode->condition);
        int result = condition->numberNode->value; 
        if (result) {
            ret = Eval(ifNode->ifNode->thenBlock);
        }
    }

    if (ifNode->ifNode->condition != NULL &&
        ifNode->ifNode->elseBlock != NULL) {
        Node *condition = Eval(ifNode->ifNode->condition);
        int result = condition->numberNode->value; 
        if (!result) {
            ret = Eval(ifNode->ifNode->elseBlock);
        }
    }

    return ret;
}
