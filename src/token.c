#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "tokentype.h"

Token *
Token_create(char *text, int type)
{
    Token *token = (Token *)malloc(sizeof(Token));
    token->text = text;
    token->type = type;
    return token;
}

void
Token_destroy(Token *token)
{
    free(token->text);
    free(token);
}

void
Token_println(Token *token)
{
    printf("%s(%s)\n", TokenTypeString(token->type), token->text);
}

