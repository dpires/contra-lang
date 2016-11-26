#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"
#include "parser.h"
#include "token.h"
#include "nodetype.h"
#include "node.h"

#include "numbernode.h"
#include "printnode.h"
#include "negopnode.h"
#include "notopnode.h"
#include "tokentype.h"
#include "binopnode.h"
#include "stringnode.h"
#include "variablenode.h"
#include "assignmentnode.h"
#include "blocknode.h"
#include "whilenode.h"
#include "ifnode.h"
#include "arraynode.h"
#include "lookupnode.h"
#include "arrayupdatenode.h"
#include "functionnode.h"
#include "parameter.h"
#include "boundparameter.h"
#include "functioncallnode.h"
#include "printlinecommand.h"
#include "printcommand.h"
#include "waitcommand.h"


Parser *
Parser_create(Vector *tokens)
{
    Parser *parser = (Parser *)malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->symbols = HashMap_create();
    parser->currentTokenPosition = 0;
    return parser;
}

void
Parser_destroy(Parser *parser)
{
    HashMap_destroy(parser->symbols);
    free(parser);
}
    
Node *
Multiply(Parser *parser)
{
    MatchAndEat(parser, MULTIPLY_TOKEN);
    return Factor(parser); 
}

Node *
Divide(Parser *parser)
{
    MatchAndEat(parser, DIVIDE_TOKEN);
    return Factor(parser);
}

Node *
Modulo(Parser *parser)
{
    MatchAndEat(parser, MODULO_TOKEN);
    return Factor(parser);
}

Node *
Add(Parser *parser)
{
    MatchAndEat(parser, ADD_TOKEN);
    return Term(parser);
}

Node *
Subtract(Parser *parser)
{
    MatchAndEat(parser, SUBTRACT_TOKEN);
    return Term(parser);
}

Node *
Factor(Parser *parser)
{
    Node *result = NULL;

    Token *currentToken = CurrentToken(parser);

    if (currentToken->type == LEFT_PAREN_TOKEN) {

        MatchAndEat(parser, LEFT_PAREN_TOKEN);
        result = Expression(parser);
        MatchAndEat(parser, RIGHT_PAREN_TOKEN);

    } else if (IsNumber(currentToken->type)) {
        Token *token = MatchAndEat(parser, NUMBER_TOKEN);
        char *ptr;
        int ret;
        ret = strtol(token->text, &ptr, 10);
        result = NumberNode_create(ret);
    } else if (IsString(parser)) {
        Token *token = MatchAndEat(parser, STRING_TOKEN);
        result = StringNode_create(token->text);
    } else if (IsKeyWord(parser)) {
        result = Variable(parser);
    }

    return result;
}

Node *
SignedFactor(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);

    if (currentToken->type == SUBTRACT_TOKEN) {
        MatchAndEat(parser, SUBTRACT_TOKEN);
        Node *node = NegOpNode_create(Factor(parser));
        return node;
    }

    return Factor(parser);
}

Node *
Term(Parser *parser)
{
    Node *node = SignedFactor(parser);

    Token *currentToken = CurrentToken(parser);

    while (IsMulOp(currentToken->type)) {

        switch (currentToken->type) {
            case MULTIPLY_TOKEN:
                node = BinOpNode_create(MULTIPLY_TOKEN, node, Multiply(parser));
                break;
            
            case DIVIDE_TOKEN:
                node = BinOpNode_create(DIVIDE_TOKEN, node, Divide(parser));
                break;

            case MODULO_TOKEN:
                node = BinOpNode_create(MODULO_TOKEN, node, Modulo(parser));
                break;
        }

        currentToken = CurrentToken(parser);
    }

    return node;
}

Node *
ArithmeticExpression(Parser *parser)
{
    Node *node = Term(parser);

    Token *currentToken = CurrentToken(parser);

    while (IsAddOp(currentToken->type)) {

        switch (currentToken->type) {
            case ADD_TOKEN:
                node = BinOpNode_create(ADD_TOKEN, node, Add(parser));
                break;

            case SUBTRACT_TOKEN:
                node = BinOpNode_create(SUBTRACT_TOKEN, node, Subtract(parser));
                break;
        }

        currentToken = CurrentToken(parser);
    }

    return node;
}

Node *
Less(Parser *parser, Node *node)
{
    MatchAndEat(parser, LESS_TOKEN);
    return BinOpNode_create(LESS_TOKEN, node, ArithmeticExpression(parser));
}

Node *
Greater(Parser *parser, Node *node)
{
    MatchAndEat(parser, GREATER_TOKEN);
    return BinOpNode_create(GREATER_TOKEN, node, ArithmeticExpression(parser));
}

Node *
Equal(Parser *parser, Node *node)
{
    MatchAndEat(parser, EQUAL_TOKEN);
    return BinOpNode_create(EQUAL_TOKEN, node, ArithmeticExpression(parser));
}

Node *
NotEqual(Parser *parser, Node *node)
{
    MatchAndEat(parser, NOT_EQUAL_TOKEN);
    return BinOpNode_create(NOT_EQUAL_TOKEN, node, ArithmeticExpression(parser));
}

Node *
LessEqual(Parser *parser, Node *node)
{
    MatchAndEat(parser, LESS_EQUAL_TOKEN);
    return BinOpNode_create(LESS_EQUAL_TOKEN, node, ArithmeticExpression(parser));
}

Node *
GreaterEqual(Parser *parser, Node *node)
{
    MatchAndEat(parser, GREATER_EQUAL_TOKEN);
    return BinOpNode_create(GREATER_EQUAL_TOKEN, node, ArithmeticExpression(parser));
}

Node *
Relation(Parser *parser)
{
    Node *node = ArithmeticExpression(parser);
    
    Token *currentToken = CurrentToken(parser);

    if (IsRelOp(currentToken->type)) {

        switch (currentToken->type) {
            case LESS_TOKEN:
                node = Less(parser, node);
                break;

            case GREATER_TOKEN:
                node = Greater(parser, node);
                break;

            case EQUAL_TOKEN:
                node = Equal(parser, node);
                break;

            case NOT_EQUAL_TOKEN:
                node = NotEqual(parser, node);
                break;

            case LESS_EQUAL_TOKEN:
                node = LessEqual(parser, node);
                break;

            case GREATER_EQUAL_TOKEN:
                node = GreaterEqual(parser, node);
                break;
        }
    }

    return node;
}

Node *
BooleanFactor(Parser *parser)
{
    return Relation(parser);
}

Node *
NotFactor(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);

    if (currentToken->type == NOT_TOKEN) {
        MatchAndEat(parser, NOT_TOKEN);
        Node *node = BooleanFactor(parser);
        return NotOpNode_create(node);
    }

    return BooleanFactor(parser);
}

Node *
BooleanTerm(Parser *parser)
{
    Node *node = NotFactor(parser);

    Token *currentToken = CurrentToken(parser);

    while (currentToken->type == AND_TOKEN) {
        MatchAndEat(parser, AND_TOKEN);
        node = BinOpNode_create(AND_TOKEN, node, NotFactor(parser));
        currentToken = CurrentToken(parser);
    }
    
    return node; 
}

Node *
BooleanExpression(Parser *parser)
{
    Node *node = BooleanTerm(parser);

    Token *currentToken = CurrentToken(parser);
    
    while (IsLogicalOp(currentToken->type)) {

        switch (currentToken->type) {
            case OR_TOKEN:
                MatchAndEat(parser, OR_TOKEN);
                node = BinOpNode_create(OR_TOKEN, node, BooleanTerm(parser));
                break;
        }

        currentToken = CurrentToken(parser);
    }

    return node;
}

Node *
Expression(Parser *parser)
{
    return BooleanExpression(parser);
}

int
IsMulOp(int type)
{
    return type == MULTIPLY_TOKEN || type == DIVIDE_TOKEN || type == MODULO_TOKEN;
}

int
IsAddOp(int type)
{
    return type == ADD_TOKEN || type == SUBTRACT_TOKEN;
}

int
IsMultiDigitOp(int type)
{
    return type == LESS_EQUAL_TOKEN || type == GREATER_EQUAL_TOKEN;
}

int
IsRelOp(int type)
{
    int lgOps = type == LESS_TOKEN || type == GREATER_TOKEN;
    int eqOps = type == EQUAL_TOKEN || type == NOT_EQUAL_TOKEN;
    return eqOps || lgOps || IsMultiDigitOp(type);
}

int
IsLogicalOp(int type)
{
    return type == OR_TOKEN || type == AND_TOKEN;
}

int
IsString(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);
    return currentToken->type == STRING_TOKEN;
}

int
IsNumber(int type)
{
    return type == NUMBER_TOKEN;
}

int
IsKeyWord(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);
    return currentToken->type == KEYWORD_TOKEN;
}

int
IsWhile(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);
    return currentToken->type == WHILE_TOKEN;
}

int
IsIfElse(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);
    return currentToken->type == IF_TOKEN || currentToken->type == ELSE_TOKEN;
}


int
IsAssignment(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);
    Token *nextToken = NextToken(parser);

    return currentToken->type == KEYWORD_TOKEN &&
        nextToken->type == ASSIGNMENT_TOKEN;
}   

int
IsArrayAccess(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);
    Token *nextToken = NextToken(parser);

    return currentToken->type == KEYWORD_TOKEN &&
        nextToken->type == LEFT_BRACKET_TOKEN;
}

int
IsFunctionDef(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);
    Token *nextToken = NextToken(parser);

    return currentToken->type == DEF_TOKEN && nextToken->type == KEYWORD_TOKEN;
}

int
IsFunctionCall(Parser *parser)
{
    Token *currentToken = CurrentToken(parser);
    Token *nextToken = NextToken(parser);

    return currentToken->type == KEYWORD_TOKEN && nextToken->type == LEFT_PAREN_TOKEN;

}

Token *
GetToken(Parser *parser, int offset)
{
    if (parser->currentTokenPosition + offset >= parser->tokens->size) {
        return Token_create("", EOF_TOKEN);
    }
    return Vector_get(parser->tokens, parser->currentTokenPosition + offset);
}

Token *
CurrentToken(Parser *parser)
{
    return GetToken(parser, 0);
}

Token *
NextToken(Parser *parser)
{
    return GetToken(parser, 1);
}

void
EatToken(Parser *parser, int offset)
{
    parser->currentTokenPosition = parser->currentTokenPosition + offset;
}

Token *
MatchAndEat(Parser *parser, int type)
{
    Token *currentToken = CurrentToken(parser);

    if (currentToken->type != type) {
        printf("Saw %s but %s expected\n", TokenTypeString(currentToken->type), TokenTypeString(type));
        exit(1);
    }

    EatToken(parser, 1);

    return currentToken;
}

Node *
ArrayDefinition(Parser *parser, char *name)
{
    Vector *elements = Vector_create(10);
    MatchAndEat(parser, LEFT_BRACKET_TOKEN);

    Token *currentToken = CurrentToken(parser);

    if (currentToken->type != RIGHT_BRACKET_TOKEN) {

        Vector_add(elements, Expression(parser));

        currentToken = CurrentToken(parser);

        while (currentToken->type != RIGHT_BRACKET_TOKEN) {
            MatchAndEat(parser, COMMA_TOKEN);
            Vector_add(elements, Expression(parser)); 
            currentToken = CurrentToken(parser);
        }
    
    }

    MatchAndEat(parser, RIGHT_BRACKET_TOKEN);

    return AssignmentNode_create(name, ArrayNode_create(elements), parser);
}

Node *
Assignment(Parser *parser)
{
    Node *node = NULL;

    Token *token = MatchAndEat(parser, KEYWORD_TOKEN);
    char *varName = token->text;
    MatchAndEat(parser, ASSIGNMENT_TOKEN);

    Token *currentToken = CurrentToken(parser);
    if (currentToken->type == LEFT_BRACKET_TOKEN) {
        node = ArrayDefinition(parser, varName);
    } else {
        Node *expression = Expression(parser);
        node = AssignmentNode_create(varName, expression, parser);
    }
    return node;
}

Node *
While(Parser *parser)
{
    Node *condition, *body;
    MatchAndEat(parser, WHILE_TOKEN);
    condition = Expression(parser);
    body = Block(parser);
    return WhileNode_create(condition, body);
}

Node *
If(Parser *parser)
{
    Node *condition = NULL;
    Node *thenBlock = NULL;
    Node *elseBlock = NULL;
    
    MatchAndEat(parser, IF_TOKEN);
    condition = Expression(parser);
    thenBlock = Block(parser);
    
    Token *currentToken = CurrentToken(parser);

    if (currentToken->type == ELSE_TOKEN) {
        MatchAndEat(parser, ELSE_TOKEN);
    
        currentToken = CurrentToken(parser);

        if (currentToken->type == IF_TOKEN) {
            elseBlock = If(parser); 
        } else {
            elseBlock = Block(parser);
        }
    }
    
    return IfNode_create(condition, thenBlock, elseBlock);
}

Node *
ArrayUpdate(Parser *parser)
{
    Token *arrayToken = MatchAndEat(parser, KEYWORD_TOKEN);
    char *arrayName = arrayToken->text;
    Node *arrayNode = VariableNode_create(arrayName, parser);

    MatchAndEat(parser, LEFT_BRACKET_TOKEN);
    Node *indexExp = Expression(parser);
    MatchAndEat(parser, RIGHT_BRACKET_TOKEN);

    MatchAndEat(parser, ASSIGNMENT_TOKEN);
    Node *right = Expression(parser);

    return ArrayUpdateNode_create(arrayNode, indexExp, right);
}

Vector *
FunctionDefParameters(Parser *parser)
{
    Vector *parameters = NULL;

    Token *currentToken = CurrentToken(parser);

    if (currentToken->type == KEYWORD_TOKEN) {
        parameters = Vector_create(5);
    
        Token *keywordToken = MatchAndEat(parser, KEYWORD_TOKEN);

        Vector_add(parameters, Parameter_createName(keywordToken->text));

        currentToken = CurrentToken(parser);

        while (currentToken->type == COMMA_TOKEN) {
            MatchAndEat(parser, COMMA_TOKEN);

            Token *keywordToken = MatchAndEat(parser, KEYWORD_TOKEN);
    
            Vector_add(parameters, Parameter_createName(keywordToken->text));

            currentToken = CurrentToken(parser);
        }
    }

    return parameters;
}

Node *
FunctionDefinition(Parser *parser)
{
    MatchAndEat(parser, DEF_TOKEN);
    Token *nameToken = MatchAndEat(parser, KEYWORD_TOKEN);
    char *functionName = nameToken->text;

    MatchAndEat(parser, LEFT_PAREN_TOKEN);
    Vector *parameters = FunctionDefParameters(parser);
    MatchAndEat(parser, RIGHT_PAREN_TOKEN);

    Node *functionBodyNode = Block(parser);

    Node *functionNode = FunctionNode_create(functionName, functionBodyNode, parameters);

    Node *functionVariableNode = AssignmentNode_create(functionName, functionNode, parser);

    return functionVariableNode;
}

Vector *
FunctionCallParameters(Parser *parser)
{
    Vector *actualParameters = NULL;

    Node *expression = Expression(parser);

    if (expression != NULL) {

        actualParameters = Vector_create(5);

        Vector_add(actualParameters, Parameter_createNode(expression));

        Token *currentToken = CurrentToken(parser);

        while (currentToken->type == COMMA_TOKEN) {

            MatchAndEat(parser, COMMA_TOKEN);
            
            Vector_add(actualParameters, Parameter_createNode(Expression(parser)));

            currentToken = CurrentToken(parser);
        }
    }

    return actualParameters;
}

Node *
FunctionCall(Parser *parser)
{
    Token *functionNameToken = MatchAndEat(parser, KEYWORD_TOKEN);
    char *functionName = functionNameToken->text;

    Node *calleeFunctionName = VariableNode_create(functionName, parser);

    MatchAndEat(parser, LEFT_PAREN_TOKEN);
    Vector *actualParameters = FunctionCallParameters(parser);
    MatchAndEat(parser, RIGHT_PAREN_TOKEN);

    Node *functionCallNode = FunctionCallNode_create(calleeFunctionName, actualParameters, parser);

    return functionCallNode;
}

Node *
Statement(Parser *parser)
{
    Node *node = NULL;
    
    Token *currentToken = CurrentToken(parser);

    if (IsAssignment(parser)) {
        node = Assignment(parser);
    } else if (IsArrayAccess(parser)) {
        node = ArrayUpdate(parser);
    } else if (IsWhile(parser)) {
        node = While(parser);
    } else if (IsIfElse(parser)) {
        node = If(parser);
    } else if (IsFunctionDef(parser)) {
        node = FunctionDefinition(parser);
    } else if (IsFunctionCall(parser)) {
        node = FunctionCall(parser);
    } else {
        printf("Unexpected token: ");
        Token_println(currentToken);
        exit(1);
    }

    return node;
}

Node *
Variable(Parser *parser)
{
    Node *node = NULL;

    Token *nextToken = NextToken(parser);

    if (nextToken->type == LEFT_PAREN_TOKEN) {

        node = FunctionCall(parser);

    } else {
        Token *token = MatchAndEat(parser, KEYWORD_TOKEN);

        Node *varNode = VariableNode_create(token->text, parser);

        Token *currentToken = CurrentToken(parser);

        if (currentToken->type == LEFT_BRACKET_TOKEN) {

            MatchAndEat(parser, LEFT_BRACKET_TOKEN);

            Node *key = Expression(parser);

            MatchAndEat(parser, RIGHT_BRACKET_TOKEN);

            return LookupNode_create(varNode, key);

        } else {
            return varNode;
        }
    }

    return node;
}

Node *
Eval(Node *node)
{
    switch(node->nodeType) {
        case PRINT_NODE:
            return PrintNode_eval(node);
            break;
        case ASSIGNMENT_NODE:
            return AssignmentNode_eval(node);
            break;
        case BINOP_NODE:
            return BinOpNode_eval(node);
            break;
        case NUMBER_NODE:
            return NumberNode_eval(node);
            break;
        case VARIABLE_NODE:
            return VariableNode_eval(node);
            break;
        case STRING_NODE:
            return StringNode_eval(node);
        case NEGOP_NODE:
            return NegOpNode_eval(node);
            break;
        case BLOCK_NODE:
            return BlockNode_eval(node);
            break;
        case WHILE_NODE:
            return WhileNode_eval(node);
            break;
        case IF_NODE:
            return IfNode_eval(node);
            break;
        case ARRAY_NODE:
            return ArrayNode_eval(node);
            break;
        case LOOKUP_NODE:
            return LookupNode_eval(node);
            break;
        case ARRAYUPDATE_NODE:
            return ArrayUpdateNode_eval(node);
            break;
        case FUNCTION_NODE:
            return FunctionNode_eval(node);
            break;
        case FUNCTIONCALL_NODE:
            return FunctionCallNode_eval(node);
            break;
        case PRINT_COMMAND:
            return PrintCommand_eval(node);
            break;
        case PRINTLINE_COMMAND:
            return PrintLineCommand_eval(node);
            break;
        case WAIT_COMMAND:
            return WaitCommand_eval(node);
            break;
    }
    return node;
}

Node *
ExecuteFunction(Parser *parser, FunctionNode *functionNode, Vector *boundParameters)
{
    // create a copy of the symbol table
    HashMap *copies = HashMap_create();
    HashMapIterator *hmip = HashMap_getIterator(parser->symbols);
    HashMapNode *n;
    while ((n = HashMapIterator_getNext(hmip)) != NULL) {
        HashMap_put(copies, n->key, n->value);
    }
    HashMapIterator_destroy(hmip);

    VIterator *it = Vector_getIterator(boundParameters);
    BoundParameter *bp;
    while ((bp = VIterator_getNext(it)) != NULL) {
        Node *valueNode = Eval(BoundParameter_getValue(bp));
        HashMap_put(parser->symbols, BoundParameter_getName(bp), valueNode);
        
    }
    VIterator_destroy(it);

    Node *node = Node_create(FUNCTION_NODE);
    node->functionNode = functionNode;

    // eval function with local symbol table
    Node *evalFunction = Eval(node);

    // reset the symbol table
    parser->symbols = copies;

    return evalFunction;
}

Node *
Block(Parser *parser)
{
    Vector *nodes = Vector_create(25);

    Token *currentToken = CurrentToken(parser);

    while (currentToken->type != END_TOKEN) {
        Vector_add(nodes, Statement(parser));
        currentToken = CurrentToken(parser);
    }

    MatchAndEat(parser, END_TOKEN);
    return BlockNode_create(nodes);
}

void
Release(Node *node)
{
    switch (node->nodeType) {
        case BLOCK_NODE:
            BlockNode_destroy(node->blockNode);
            break;

        case NUMBER_NODE:
            NumberNode_destroy(node->numberNode);
            break;

        case PRINT_NODE:
            PrintNode_destroy(node->printNode);
            break;

        case STRING_NODE:
            StringNode_destroy(node->stringNode);
            break;

        case BINOP_NODE:
            BinOpNode_destroy(node->binOpNode);
            break;

        case IF_NODE:
            IfNode_destroy(node->ifNode);
            break;

        case WHILE_NODE:
            WhileNode_destroy(node->whileNode);
            break;

        case ASSIGNMENT_NODE:
            AssignmentNode_destroy(node->assignmentNode);
            break;

        case VARIABLE_NODE:
            VariableNode_destroy(node->variableNode);
            break;

        case ARRAY_NODE:
            ArrayNode_destroy(node->arrayNode);
            break;

        case ARRAYUPDATE_NODE:
            ArrayUpdateNode_destroy(node->arrayUpdateNode);
            break;
    
        case LOOKUP_NODE:
            LookupNode_destroy(node->lookupNode);
            break;
    }

    free(node);
}
