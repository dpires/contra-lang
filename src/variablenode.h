#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "parser.h"
#include "node.h"
#include "nodetype.h"

typedef struct VariableNode {
    Parser *parser;
    char *varName;
} VariableNode;

Node *
VariableNode_create(char *varName, Parser *parser);

void
VariableNode_destroy(VariableNode *variableNode);

Node *
VariableNode_eval(Node *node);

#endif
