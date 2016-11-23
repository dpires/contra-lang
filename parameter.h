#ifndef PARAMETER_H
#define PARAMETER_H

typedef struct Parameter {
    Node *value;
    char *name;
} Parameter;

Parameter *
Parameter_createNode(Node *value);

Parameter *
Parameter_createName(char *name);

Node *
Parameter_getValue();

char *
Parameter_getName();

#endif
