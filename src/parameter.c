#include <stdlib.h>
#include "node.h"
#include "parameter.h"


Parameter *
Parameter_createNode(Node *value)
{
    Parameter *parameter = (Parameter *)malloc(sizeof(Parameter));
    parameter->name = NULL;
    parameter->value = value;

    return parameter;
}

Parameter *
Parameter_createName(char *name)
{
    Parameter *parameter = (Parameter *)malloc(sizeof(Parameter));
    parameter->value = NULL;
    parameter->name = name;

    return parameter;
}

Node *
Parameter_getValue(Parameter *parameter)
{
    return parameter->value;
}

char *
Parameter_getName(Parameter *parameter)
{
    return parameter->name;
}
