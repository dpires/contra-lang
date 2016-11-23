#ifndef BOUNDPARAMETER_H
#define BOUNDPARAMETER_H

#include "node.h"

typedef struct BoundParameter {
    char *name;
    Node *value;
} BoundParameter;

BoundParameter *
BoundParameter_create(char *name, Node *value);

char *
BoundParameter_getName(BoundParameter *boundParameter);

Node *
BoundParameter_getValue(BoundParameter *boundParameter);

#endif
