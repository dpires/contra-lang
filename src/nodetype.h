#ifndef NODETYPE_H
#define NODETYPE_H

#include "node.h"

enum NodeType {
    NUMBER_NODE,
    BINOP_NODE,
    NEGOP_NODE,
    NOTOP_NODE,
    PRINT_NODE,
    STRING_NODE,
    VARIABLE_NODE,
    ASSIGNMENT_NODE,
    BLOCK_NODE,
    WHILE_NODE,
    IF_NODE,
    ARRAY_NODE,
    LOOKUP_NODE,
    ARRAYUPDATE_NODE,
    FUNCTION_NODE,
    FUNCTIONCALL_NODE,
    PRINTLINE_COMMAND,
    PRINT_COMMAND
};

char *
NodeTypeString(Node *node);

#endif
