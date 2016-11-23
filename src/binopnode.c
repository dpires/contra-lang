#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "numbernode.h"
#include "nodetype.h"
#include "node.h"
#include "tokentype.h"
#include "binopnode.h"
#include "stringnode.h"
#include "parser.h"

Node *
BinOpNode_create(int op, Node *left, Node *right)
{
    BinOpNode *binOpNode = (BinOpNode *)malloc(sizeof(BinOpNode));
    binOpNode->op =op;
    binOpNode->left = left;
    binOpNode->right = right;

    Node *variant = Node_create(BINOP_NODE);
    variant->binOpNode = binOpNode;

    return variant;
}


Node *
BinOpNode_eval(Node *binOpNode)
{
    Node *l = Eval(binOpNode->binOpNode->left);
    Node *r = Eval(binOpNode->binOpNode->right);
    int left = l->numberNode->value;
    int right = r->numberNode->value;
    switch (binOpNode->binOpNode->op) {
        case ADD_TOKEN:
            return NumberNode_create(left + right);
            break;
        case SUBTRACT_TOKEN:
            return NumberNode_create(left - right);
            break;
        case MULTIPLY_TOKEN:
            return NumberNode_create(left * right);
            break;
        case DIVIDE_TOKEN:
            if (right == 0) {
                printf("divide by 0\n");
                exit(1);
            }
            return NumberNode_create(left / right);
            break;
        case MODULO_TOKEN:
            return NumberNode_create(left % right);
            break;
        case LESS_TOKEN:
            return NumberNode_create(left < right);
            break;
        case GREATER_TOKEN:
            return NumberNode_create(left > right);
            break;
        case EQUAL_TOKEN:
            if (l->nodeType == STRING_NODE && r->nodeType == STRING_NODE) {
                int res =strcmp(l->stringNode->text, r->stringNode->text);
                return NumberNode_create(res == 0);
            } else  {
                return NumberNode_create(left == right);
            }
            break;
        case NOT_EQUAL_TOKEN:
            return NumberNode_create(left != right);
            break;
        case LESS_EQUAL_TOKEN:
            return NumberNode_create(left <= right);
            break;
        case GREATER_EQUAL_TOKEN:
            return NumberNode_create(left >= right);
            break;
        case OR_TOKEN:
            return NumberNode_create(left || right);
            break;
        case AND_TOKEN:
            return NumberNode_create(left && right);
            break;
    }
    return binOpNode;
}
