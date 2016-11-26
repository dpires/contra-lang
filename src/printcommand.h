#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H

#include "node.h"
#include "parser.h"

typedef struct PrintCommand {
    Parser *parser;
} PrintCommand;


Node *
PrintCommand_create(Parser *parser);

Node *
PrintCommand_eval(Node *printCommand);

#endif
