#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
#include "numbernode.h"
#include "binopnode.h"
#include "tokentype.h"
#include "tokenizer.h"
#include "vector.h"
#include "token.h"
#include "parser.h"
#include "blocknode.h"
#include "functionnode.h"
#include "parameter.h"
#include "printcommand.h"
#include "printlinecommand.h"
#include "assignmentnode.h"
#include "waitcommand.h"

Node *
CreatePrintLineCommand(Parser *parser)
{
    char *functionName = "println";

    Vector *parameters = Vector_create(1);
    Vector_add(parameters, Parameter_createName("writee"));

    Vector *statements = Vector_create(1);
    Vector_add(statements, PrintLineCommand_create(parser));

    Node *functionBody = BlockNode_create(statements);

    Node *functionNode = FunctionNode_create(functionName, functionBody, parameters);

    Node *functionVariable = AssignmentNode_create(functionName, functionNode, parser);

    return functionVariable;
}

Node *
CreatePrintCommand(Parser *parser)
{
    char *functionName = "print";

    Vector *parameters = Vector_create(1);
    Vector_add(parameters, Parameter_createName("writee"));

    Vector *statements = Vector_create(1);
    Vector_add(statements, PrintCommand_create(parser));

    Node *functionBody = BlockNode_create(statements);

    Node *functionNode = FunctionNode_create(functionName, functionBody, parameters);

    Node *functionVariable = AssignmentNode_create(functionName, functionNode, parser);

    return functionVariable;
}

Node *
CreateWaitCommand(Parser *parser)
{
    char *functionName = "wait";

    Vector *parameters = Vector_create(1);
    Vector_add(parameters, Parameter_createName("interval"));

    Vector *statements = Vector_create(1);
    Vector_add(statements, WaitCommand_create(parser));

    Node *functionBody = BlockNode_create(statements);

    Node *functionNode = FunctionNode_create(functionName, functionBody, parameters);

    Node *functionVariable = AssignmentNode_create(functionName, functionNode, parser);

    return functionVariable;
}

char *
ReadFile(char *path)
{
    long length;
    char *buffer;
    FILE *file = fopen(path, "r");
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = (char *)malloc(sizeof(char) * (length + 2));
    if (buffer) {
        fread(buffer, 1, length, file);
    }
    fclose(file);
    buffer[length] = ' ';
    buffer[length + 1] = '\0';
    return buffer;
}

void 
Interpret(Parser *parser)
{
    MatchAndEat(parser, SCRIPT_TOKEN);
    Eval(CreatePrintCommand(parser));
    Eval(CreatePrintLineCommand(parser));
    Eval(CreateWaitCommand(parser));
    Node *statements = Block(parser);
    Eval(statements);
    Release(statements);
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("./contra <script.con>\n");
        exit(1);
    }

    char *source = ReadFile(argv[1]);

    Tokenizer *tokenizer = Tokenizer_create(source);

    Vector *tokens = Tokenizer_tokenize(tokenizer, source);

    Parser *parser = Parser_create(tokens);
    Interpret(parser);

    Tokenizer_destroy(tokenizer);
    Parser_destroy(parser);
    free(source);

    return 0;    
}
