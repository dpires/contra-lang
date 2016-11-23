#include <stdio.h>
#include <stdlib.h>

#include "printnode.h"
#include "node.h"
#include "nodetype.h"

#include "numbernode.h"
#include "variablenode.h"
#include "stringnode.h"

Node *
PrintNode_create(Node *expression, int type)
{
    PrintNode *printNode = (PrintNode *)malloc(sizeof(PrintNode)); 
    printNode->expression = expression;
    printNode->type = type;

    Node *variant = Node_create(PRINT_NODE);
    variant->printNode = printNode;

    return variant;
}

Node *
PrintNode_eval(Node *node)
{
    char buf[4];
    buf[0] = '%';

    Node *res = Eval(node->printNode->expression);
    
    if (res->nodeType == NUMBER_NODE)
        buf[1] = 'd';
    else
        buf[1] = 's';

    if (node->printNode->type == NEWLINE) {
        buf[2]='\n';
        buf[3]='\0';
    } else {
        buf[2]='\0';
    }
    
    if (res->nodeType == NUMBER_NODE)
        printf(buf, res->numberNode->value);
    else
        printf(buf, res->stringNode->text);

    return res;
}
