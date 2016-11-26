#include <string.h>

#include "node.h"
#include "nodetype.h"

char *
NodeTypeString(Node *node)
{
    char *strings[] = {
        "NUMBER_NODE",
        "BINOP_NODE",
        "NEGOP_NODE",
        "PRINT_NODE",
        "STRING_NODE",
        "VARIABLE_NODE",
        "ASSIGNMENT_NODE"
        "BLOCK_NODE",
        "WHILE_NODE",
        "IF_NODE",
        "ARRAY_NODE",
        "LOOKUP_NODE",
        "ARRAYUPDATE_NODE",
        "FUNCTION_NODE",
        "FUNCTIONCALL_NODE",
        "PRINTLINE_COMMAND",
        "PRINT_COMMAND"
    };

    return strings[node->nodeType];
}
