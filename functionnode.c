#include <stdlib.h>
#include "node.h"
#include "nodetype.h"
#include "vector.h"
#include "parser.h"
#include "functionnode.h"


Node *
FunctionNode_create(char *name, Node *body, Vector *parameters)
{
    FunctionNode *functionNode = (FunctionNode *)malloc(sizeof(FunctionNode));
    functionNode->name = name;
    functionNode->body = body;
    functionNode->parameters = parameters;

    Node *variant = Node_create(FUNCTION_NODE);
    variant->functionNode = functionNode;

    return variant;
}

Node *
FunctionNode_eval(Node *functionNode)
{
    return Eval(functionNode->functionNode->body);
}

Vector *
FunctionNode_getParameters(FunctionNode *functionNode)
{
    return functionNode->parameters;
}

Node *
FunctionNode_getBody(FunctionNode *functionNode)
{
    return functionNode->body;
}

char *
FunctionNode_getName(FunctionNode *functionNode)
{
    return functionNode->name;
}
