#ifndef PARSER_H
#define PARSER_H

static const char *KEYWORD_STRINGS[] = {
    FOREACH_KEYWORD(GENERATE_STRING)
};

// typedef struct Statement_Block{
//   int size;
//   struct Node* members[1];
// } Statement_Block;

typedef enum Class{
	CONSTANT, BINOP, UNOP, COMPOUND, ASSOP, VAR, NOOP
} Class;
typedef struct Node {
	Class class;
	Token token;
	union {
		int value;
    char* id;
		struct {
			struct Node* left;
			struct Node* right;
		} op;
		struct Node* expr;
    struct Node* children[1];
	};
} Node;


void consume(Type type);
Node* expr();
Node* factor();
Node* term();
Node* Num(Token token);
Node* BinOp(Token token, Node* left, Node* right);
Node* UnOp(Token op, Node* expr);
Node* NoOp();
Node* AssOp(Token token, Node* left, Node* right);
Node* Var(Token token);
Node* program();
Node* compound_statement();
Node* statement_list();
Node* statement();
Node* assignment_statement();
Node* variable();


#endif
