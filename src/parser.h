#ifndef PARSER_H
#define PARSER_H

#include "vector.h"
#include "hashmap.h"

#include "node.h"
#include "token.h"
#include "functionnode.h"

typedef struct Parser {
    Vector *tokens;
    HashMap *symbols;
    int currentTokenPosition;
} Parser;

Parser *
Parser_create(Vector *tokens);

void
Parser_destroy(Parser *parser);

Node *
Multiply(Parser *parser);

Node *
Divide(Parser *parser);

Node *
Add(Parser *parser);

Node *
Subtract(Parser *parser);

Node *
Factor(Parser *parser);

Node *
SignedFactor(Parser *parser);

Node *
Term(Parser *parser);

Node *
ArithmeticExpression(Parser *parser);

Node *
Less(Parser *parser, Node *node);

Node *
Greater(Parser *parser, Node *node);

Node *
Equal(Parser *parser, Node *node);

Node *
NotEqual(Parser *parser, Node *node);

Node *
LessEqual(Parser *parser, Node *node);

Node *
GreaterEqual(Parser *parser, Node *node);

Node *
Relation(Parser *parser);

Node *
BooleanFactor(Parser *parser);

Node *
NotFactor(Parser *parser);

Node *
BooleanTerm(Parser *parser);

Node *
BooleanExpression(Parser *parser);

Node *
Expression(Parser *parser);

int
IsMulOp(int type);

int
IsAddOp(int type);

int
IsMultiDigitOp(int type);

int
IsRelOp(int type);

int
IsLogicalOp(int type);

int
IsNumber(int type);

int
IsString(Parser *parser);

int
IsKeyWord(Parser *parser);

int
IsWhile(Parser *parser);

int
IsIfElse(Parser *parser);

int
IsAssignment(Parser *parser);

int
IsArrayAccess(Parser *parser);

int
IsFunctionDef(Parser *parser);

int
IsFunctionCall(Parser *parser);

Token *
GetToken(Parser *parser, int offset);

Token *
CurrentToken(Parser *parser);

Token *
NextToken(Parser *parser);

void
EatToken(Parser *parser, int offset);

Token *
MatchAndEat(Parser *parser, int type);

Node *
ArrayDefinition(Parser *parser, char *name);

Node *
Assignment(Parser *parser);

Node *
While(Parser *parser);

Node *
If(Parser *parser);

Vector *
FunctionDefParameters(Parser *parser);

Node *
FunctionDefinition(Parser *parser);

Vector *
FunctionCallParameters(Parser *parser);

Node *
FunctionCall(Parser *parser);

Node *
Statement(Parser *parser);

Node *
Variable(Parser *parser);

Node *
Eval(Node *node);

Node *
ExecuteFunction(Parser *parser, FunctionNode *functionNode, Vector *boundParameters);

Node *
Block(Parser *parser);

#endif
