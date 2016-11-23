#ifndef WHILENODE_H
#define WHILENODE_H

#include "node.h"

typedef struct WhileNode {
    Node *condition;
    Node *body;
} WhileNode;

Node *
WhileNode_create(Node *condition, Node *body);

Node *
WhileNode_eval(Node *whileNode);

#endif
