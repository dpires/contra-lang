#ifndef NODE_H
#define NODE_H

typedef struct Node {
    int nodeType;
    union {
        struct NumberNode *numberNode;
        struct BinOpNode *binOpNode;    
        struct NegOpNode *negOpNode;
        struct NotOpNode *notOpNode;
        struct PrintNode *printNode;
        struct StringNode *stringNode;
        struct VariableNode *variableNode;
        struct AssignmentNode *assignmentNode;
        struct BlockNode *blockNode;
        struct WhileNode *whileNode;
        struct IfNode *ifNode;
        struct ArrayNode *arrayNode;
        struct LookupNode *lookupNode;
        struct ArrayUpdateNode *arrayUpdateNode;
        struct FunctionNode *functionNode;
        struct FunctionCallNode *functionCallNode;
        struct PrintCommand *printCommand;
        struct PrintLineCommand *printLineCommand;
    };
} Node;

Node *
Node_create(int nodeType);

#endif
