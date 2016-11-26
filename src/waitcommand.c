#include <stdlib.h>
#include <unistd.h>

#include "node.h"
#include "nodetype.h"
#include "parser.h"
#include "hashmap.h"
#include "waitcommand.h"
#include "numbernode.h"


Node *
WaitCommand_create(Parser *parser)
{
    WaitCommand *waitCommand = (WaitCommand *)malloc(sizeof(WaitCommand));
    waitCommand->parser = parser;

    Node *variant = Node_create(WAIT_COMMAND);
    variant->waitCommand = waitCommand;

    return variant;
}

Node *
WaitCommand_eval(Node *waitCommand)
{
    WaitCommand *command = waitCommand->waitCommand;
    Node *variable = HashMap_get(command->parser->symbols, "interval");
    sleep(variable->numberNode->value);
    return waitCommand;
}
