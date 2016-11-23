#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"
#include "parser.h"
#include "node.h"
#include "nodetype.h"
#include "assignmentnode.h"
#include "numbernode.h"
#include "printnode.h"
#include "functionnode.h"

Node *
AssignmentNode_create(char *varName, Node *value, Parser *parser)
{
    AssignmentNode *assignmentNode = (AssignmentNode *)malloc(sizeof(AssignmentNode));
    assignmentNode->parser = parser;
    assignmentNode->varName = varName;
    assignmentNode->value = value;

    Node *variant = Node_create(ASSIGNMENT_NODE);
    variant->assignmentNode = assignmentNode;

    return variant;
}

Node *
AssignmentNode_eval(Node *node)
{
    AssignmentNode *an = node->assignmentNode;
    if (an->value->nodeType == FUNCTION_NODE) {
        HashMap_put(an->parser->symbols, an->varName, an->value);
    } else {
        Node *eval = Eval(an->value);
        HashMap_put(an->parser->symbols, an->varName, eval);
    }
    return node;
}
