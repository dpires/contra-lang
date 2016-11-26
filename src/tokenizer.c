#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "vector.h"
#include "tokentype.h"
#include "tokenizer.h"
#include "token.h"
#include "numbernode.h"
#include "binopnode.h"
#include "negopnode.h"

Tokenizer *
Tokenizer_create(char *source)
{
    Tokenizer *tokenizer = (Tokenizer *)malloc(sizeof(Tokenizer));
    tokenizer->source = source;
    tokenizer->tokens = Vector_create(25);
    return tokenizer;
}

void
Tokenizer_destroy(Tokenizer *tokenizer)
{
    VIterator *it = Vector_getIterator(tokenizer->tokens);
    Token *token;
    while ((token = VIterator_getNext(it)) != NULL) {
        Token_destroy(token);
    }
    VIterator_destroy(it);
    Vector_destroy(tokenizer->tokens);
    free(tokenizer);
}
    
int
IsOp(char chr)
{
    int addOp = chr == '+' || chr == '-';
    int mulOp = chr == '*' || chr == '/' || chr == '%';

    int compOp = chr == '<' || chr == '>' || chr == '=';
    int lgicOp = chr == '!' || chr == '|' || chr == '&';

    return addOp || mulOp || compOp || lgicOp;
}

int
FindOpType(char firstOperator, char nextChar)
{
    int type = UNKNOWN_TOKEN;
    switch (firstOperator) {
        case '+':
            type = ADD_TOKEN;
            break;
        case '-':
            type = SUBTRACT_TOKEN;
            break;
        case '*':
            type = MULTIPLY_TOKEN;
            break;
        case '/':
            type = DIVIDE_TOKEN;
            break;
        case '%':
            type = MODULO_TOKEN;
            break;
        case '<':
            type = LESS_TOKEN;
            if (nextChar == '=') {
                type = LESS_EQUAL_TOKEN;
            }
            break;
        case '>':
            type = GREATER_TOKEN;
            if (nextChar == '=') {
                type = GREATER_EQUAL_TOKEN;
            }
            break;
        case '=':
            type = ASSIGNMENT_TOKEN;
            if (nextChar == '=') { 
                type = EQUAL_TOKEN;
            }
            break;
        case '!':
            type = NOT_TOKEN;
            if (nextChar == '=') {
                type = NOT_EQUAL_TOKEN;
            }
            break;
        case '|':
            type = OR_TOKEN;
            break;
        case '&':
            type = AND_TOKEN;
            break;
    }
    return type;
}

int
IsPunc(char chr)
{
    int puncOp = chr == ',';
    return puncOp;
}

int
FindPuncType(char firstOperator)
{
    int type = UNKNOWN_TOKEN;
    switch (firstOperator) {
        case ',':
            type = COMMA_TOKEN;
            break;
    }
    return type;
}

int
IsParen(char chr)
{
    int prnOp = chr == '(' || chr == ')';
    int brktOp = chr == '[' || chr == ']';
    int puncOp = chr == ',';

    return prnOp || brktOp || puncOp;
}

int
FindParenType(char chr)
{
    int type = UNKNOWN_TOKEN;
    switch (chr) {
        case '(':
            type = LEFT_PAREN_TOKEN;
            break;
        case ')':
            type = RIGHT_PAREN_TOKEN;
            break;
        case '[':
            type = LEFT_BRACKET_TOKEN;
            break;
        case ']':
            type = RIGHT_BRACKET_TOKEN;
            break;
        case ',':
            type = COMMA_TOKEN;
            break;
    }
    return type;
}

int
FindStatementType(char *text)
{
    int type = UNKNOWN_TOKEN;

    if (strcmp(text, "script") == 0) {
        type = SCRIPT_TOKEN;
    } else if (strcmp(text, "end") == 0) {
        type = END_TOKEN;
    } else if (strcmp(text, "while") == 0) {
        type = WHILE_TOKEN;
    } else if (strcmp(text, "if") == 0) {
        type = IF_TOKEN;
    } else if (strcmp(text, "else") == 0) {
        type = ELSE_TOKEN;
    } else if (strcmp(text, "def") == 0) {
        type = DEF_TOKEN;
    } else {
        type = KEYWORD_TOKEN;
    }
    return type;
}


void
Tokenizer_addToken(Tokenizer *tokenizer, Token *token)
{
    Vector_add(tokenizer->tokens, token);
}
    
Vector *
Tokenizer_tokenize(Tokenizer *tokenizer, char *source)
{
    int textIndex = 0;
    char *text = (char *)malloc(sizeof(char) * 256);

    Token *token;

    char firstOperator = '\0';

    int state = DEFAULT_STATE;

    long len = strlen(source);

    int index;
    for (index = 0; index < len; index++) {

        char chr = source[index];

        switch (state) {
            case DEFAULT_STATE:
                if (IsOp(chr)) {
                    firstOperator = chr;
                    text[0] = firstOperator;
                    text[1] = '\0';
                    int type = FindOpType(firstOperator, '\0');
                    token = Token_create(strdup(text), type);
                    state = OPERATOR_STATE;
                } else if (isdigit(chr)) {
                    
                    text[0] = chr;
                    textIndex++;
                    state = NUMBER_STATE; 
                } else if (IsParen(chr)) {
                    int parenType = FindParenType(chr);
                    text[0] = chr;
                    text[1] = '\0';
                    Token *t = Token_create(strdup(text), parenType);
                    Tokenizer_addToken(tokenizer, t);
                    textIndex = 0;
                } else if (isalpha(chr)) {
                    text[0] = chr;
                    textIndex++;
                    state = KEYWORD_STATE;
                } else if (chr == '"') {
                    state = STRING_STATE;
                } else if (IsPunc(chr)) {
                    int type = FindPuncType(chr);
                    text[0] = chr;
                    text[1] = '\0';
                    Token *t = Token_create(strdup(text), type);
                    Tokenizer_addToken(tokenizer, t);
                    textIndex = 0;
                }
                break;
            case STRING_STATE:
                if (chr == '"') {
                    text[textIndex] = '\0';
                    Token *t = Token_create(strdup(text), STRING_TOKEN);
                    Tokenizer_addToken(tokenizer, t);
                    textIndex = 0;
                    state = DEFAULT_STATE;
                } else {
                    text[textIndex] = chr;
                    textIndex++;
                }
                break;
            case KEYWORD_STATE:
                if (isalpha(chr) || isdigit(chr)) {
                    text[textIndex] = chr;
                    textIndex++;
                } else {
                    text[textIndex] = '\0';
                    int type = FindStatementType(text);
                    Token *t = Token_create(strdup(text), type);
                    Tokenizer_addToken(tokenizer, t);
                    textIndex = 0;
                    state = DEFAULT_STATE;
                    index--;
                }
                break;
            case OPERATOR_STATE:
                if (IsOp(chr)) {
                    int opType = FindOpType(firstOperator, chr);
                    text[0] = firstOperator;
                    text[1] = chr;
                    text[2] = '\0';
                    Token_destroy(token);
                    token = Token_create(strdup(text), opType);
                } else {
                    Tokenizer_addToken(tokenizer, token);
                    textIndex = 0;
                    state = DEFAULT_STATE;
                    index--;
                }
                break;
            case NUMBER_STATE:
                if (isdigit(chr)) {
                    text[textIndex] = chr;
                    textIndex++;
                } else {
                    text[textIndex] = '\0';
                    char *ptr;
                    long number = strtol(text, &ptr, 10);
                    int len = number;
                    char numberText[len+1];
                    snprintf(numberText, len+1, "%ld", number);
                    numberText[len] = '\0';
                    Token *t = Token_create(strdup(numberText), NUMBER_TOKEN);
                    Tokenizer_addToken(tokenizer, t);
                    textIndex = 0;
                    state = DEFAULT_STATE;
                    index--;
                }
                break;
        }
    }
    
    free(text);

    return tokenizer->tokens;
}
