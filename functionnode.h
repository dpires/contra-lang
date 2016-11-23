#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H

#include "vector.h"
#include "node.h"

typedef struct FunctionNode {
    char *name;
    Node *body;
    Vector *parameters;
} FunctionNode;

Node *
FunctionNode_create(char *name, Node *body, Vector *parameters);

Node *
FunctionNode_eval(Node *functionNode);

Vector *
FunctionNode_getParameters(FunctionNode *functionNode);

Node *
FunctionNode_getBody(FunctionNode *functionNode);

char *
FunctionNode_getName(FunctionNode *functionNode);

#endif
