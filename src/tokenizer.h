#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"

enum TokenizeState {
    DEFAULT_STATE,
    OPERATOR_STATE,
    NUMBER_STATE,
    KEYWORD_STATE,
    STRING_STATE
};

typedef struct Tokenizer {
    char *source;
    Vector *tokens;
} Tokenizer;

Tokenizer *
Tokenizer_create(char *source);

void
Tokenizer_destroy(Tokenizer *tokenizer);

int
IsOp(char chr);

int
FindOpType(char firstOperator, char nextChar);

int
IsPunc(char chr);

int
FindPuncType(char firstOperator);

int
IsParen(char chr);

int
FindParenType(char chr);

int
FindStatementType(char *text);

void
Tokenizer_addToken(Tokenizer *tokenizer, Token *token);

Vector *
Tokenizer_tokenize(Tokenizer *tokenizer, char *source);

#endif
