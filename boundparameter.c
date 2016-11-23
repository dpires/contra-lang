#include <stdlib.h>
#include "node.h"
#include "boundparameter.h"


BoundParameter *
BoundParameter_create(char *name, Node *value)
{
    BoundParameter *boundParameter = (BoundParameter *)malloc(sizeof(BoundParameter));
    boundParameter->name = name;
    boundParameter->value = value;

    return boundParameter;
}

char *
BoundParameter_getName(BoundParameter *boundParameter)
{
    return boundParameter->name;
}

Node *
BoundParameter_getValue(BoundParameter *boundParameter)
{
    return boundParameter->value;
}
