#ifndef PRINTLINECOMMAND_H
#define PRINTLINECOMMAND_H

#include "node.h"
#include "parser.h"

typedef struct PrintLineCommand {
    Parser *parser;
} PrintLineCommand;


Node *
PrintLineCommand_create(Parser *parser);

Node *
PrintLineCommand_eval(Node *printLineCommand);

#endif
