#include <stdlib.h>
#include <stdio.h>

#include "node.h"
#include "nodetype.h"
#include "parser.h"
#include "parameter.h"
#include "boundparameter.h"
#include "functioncallnode.h"
#include "functionnode.h"

Node *
FunctionCallNode_create(Node *name, Vector *actualParameters, Parser *parser)
{
    FunctionCallNode *functionCallNode = (FunctionCallNode *)malloc(sizeof(FunctionCallNode));
    functionCallNode->name = name;
    functionCallNode->actualParameters = actualParameters;
    functionCallNode->parser = parser;

    Node *variant = Node_create(FUNCTIONCALL_NODE);
    variant->functionCallNode = functionCallNode;

    return variant;
}

Node *
FunctionCallNode_eval(Node *functionCallNode)
{
    Node *fnode = Eval(functionCallNode->functionCallNode->name);

    FunctionNode *functionNode = fnode->functionNode;
    
    FunctionCallNode *callNode = functionCallNode->functionCallNode;

    Vector *boundParameters = Vector_create(5);

    if (FunctionNode_getParameters(functionNode) != NULL) {

        if (callNode->actualParameters != NULL) {

            Vector *functionParameters = FunctionNode_getParameters(functionNode);

            if (callNode->actualParameters->size < functionParameters->size) {
                printf("Called with too few parameters\n");
                exit(1);

            } else if (callNode->actualParameters->size > functionParameters->size) {
                printf("Called with too many parameters\n");
                exit(1);

            } else {

                int index;
                for (index=0; index < callNode->actualParameters->size; index++) {

                    Parameter *parameterName = Vector_get(functionParameters, index);
                    char *name = Parameter_getName(parameterName);

                    Parameter *parameterNode = Vector_get(callNode->actualParameters, index);
                    Node *value = Parameter_getValue(parameterNode);

                    if (value->nodeType == FUNCTION_NODE) {
                        value = Eval(value);
                    }

                    Vector_add(boundParameters, BoundParameter_create(name, value));
                }
            }

        } else {
            printf("Parameters are required!\n");
            exit(1);
        }
        
    }

    return ExecuteFunction(callNode->parser, functionNode, boundParameters);
}
