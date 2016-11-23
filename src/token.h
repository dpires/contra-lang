#ifndef TOKEN_H
#define TOKEN_H

typedef struct Token {
    int type;
    char *text;
} Token;

Token *
Token_create(char *text, int type);

void
Token_destroy(Token *token);

void
Token_println(Token *token);

#endif
