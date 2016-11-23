#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"
#include "parser.h"
#include "node.h"
#include "nodetype.h"
#include "variablenode.h"


Node *
VariableNode_create(char *varName, Parser *parser)
{
    VariableNode *vn = (VariableNode *)malloc(sizeof(VariableNode));
    vn->varName = varName;
    vn->parser = parser;

    Node *variant = Node_create(VARIABLE_NODE);
    variant->variableNode = vn;

    return variant;
}

Node *
VariableNode_eval(Node *node)
{
    VariableNode *vn = node->variableNode;
    return HashMap_get(vn->parser->symbols, vn->varName);
}
