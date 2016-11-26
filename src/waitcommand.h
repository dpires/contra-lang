#ifndef WAITCOMMAND_H
#define WAITCOMMAND_H

#include "node.h"
#include "parser.h"

typedef struct WaitCommand {
    Parser *parser;
} WaitCommand;

Node *
WaitCommand_create(Parser *parser);

Node *
WaitCommand_eval(Node *waitCommand);

#endif
