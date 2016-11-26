#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "nodetype.h"
#include "printlinecommand.h"
#include "numbernode.h"
#include "stringnode.h"
#include "hashmap.h"

Node *
PrintLineCommand_create(Parser *parser)
{
    PrintLineCommand *printLineCommand = (PrintLineCommand *)malloc(sizeof(PrintLineCommand));
    printLineCommand->parser = parser;

    Node *variant = Node_create(PRINTLINE_COMMAND);
    variant->printLineCommand = printLineCommand;

    return variant;
}

Node *
PrintLineCommand_eval(Node *printLineCommand)
{
    char buf[4];
    buf[0] = '%';

    PrintLineCommand *command = printLineCommand->printLineCommand;

    Node *variable = HashMap_get(command->parser->symbols, "writee");

    switch (variable->nodeType) {
        case NUMBER_NODE:
            buf[1] = 'd';
            buf[2] = '\n';
            buf[3] = '\0';
            printf(buf, variable->numberNode->value);
            break;

        case STRING_NODE:
            buf[1] = 's';
            buf[2] = '\n';
            buf[3] = '\0';
            printf(buf, variable->stringNode->text);
            break;
    }

    return printLineCommand;
}
