#ifndef ASSIGNMENT_NODE_H
#define ASSIGNMENT_NODE_H

#include "parser.h"
#include "node.h"


typedef struct AssignmentNode {
    Parser *parser;
    char *varName;
    Node *value;
} AssignmentNode;

Node *
AssignmentNode_create(char *varName, Node *value, Parser *parser);

Node *
AssignmentNode_eval(Node *node);

#endif
