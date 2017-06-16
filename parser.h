#ifndef PARSER_H
#define PARSER_H

static const char *KEYWORD_STRINGS[] = {
    FOREACH_KEYWORD(GENERATE_STRING)
};

typedef enum Class{
	CONSTANT, BINOP, UNOP
} Class;
typedef struct Node {
	Class class;
	Token token;
	union {
		int value;
		struct {
			struct Node* left;
			struct Node* right;
		} op;
		struct Node* expr;
	};
} Node;


void consume(Type type);
Node* expr();
Node* factor();
Node* term();
Node* Num(Token token);
Node* BinOp(Token token, Node* left, Node* right);
Node* UnOp(Token op, Node* expr);

#endif
