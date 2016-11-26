#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "nodetype.h"
#include "printcommand.h"
#include "numbernode.h"
#include "stringnode.h"
#include "hashmap.h"

Node *
PrintCommand_create(Parser *parser)
{
    PrintCommand *printCommand = (PrintCommand *)malloc(sizeof(PrintCommand));
    printCommand->parser = parser;

    Node *variant = Node_create(PRINT_COMMAND);
    variant->printCommand = printCommand;

    return variant;
}

Node *
PrintCommand_eval(Node *printCommand)
{
    char buf[3];
    buf[0] = '%';

    PrintCommand *command = printCommand->printCommand;

    Node *variable = HashMap_get(command->parser->symbols, "writee");

    switch (variable->nodeType) {
        case NUMBER_NODE:
            buf[1] = 'd';
            buf[2] = '\0';
            printf(buf, variable->numberNode->value);
            break;

        case STRING_NODE:
            buf[1] = 's';
            buf[2] = '\0';
            printf(buf, variable->stringNode->text);
            break;
    }

    return printCommand;
}
