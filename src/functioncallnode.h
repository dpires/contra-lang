#ifndef FUNCTIONCALLNODE_H
#define FUNCTIONCALLNODE_H

#include "node.h"
#include "parser.h"
#include "vector.h"
#include "boundparameter.h"
#include "parameter.h"

typedef struct FunctionCallNode {
    Node *name;
    Vector *actualParameters;
    Parser *parser;
} FunctionCallNode;

Node *
FunctionCallNode_create(Node *name, Vector *actualParameters, Parser *parser);

Node *
FunctionCallNode_eval(Node *functionCallNode);

#endif
