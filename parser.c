#include "interpreter.h"
Token current_token;
extern const char * TYPE_STRINGS[];

Node* Num(Token token){
  Node* toReturn = (Node*)malloc(sizeof(Node));
  toReturn->class = CONSTANT;
  toReturn->token = token;
  toReturn->value = token.value;
  return toReturn;
}

Node* BinOp(Token token, Node* left, Node* right){
  Node* toReturn = (Node*)malloc(sizeof(Node));
  toReturn->class = BINOP;
  toReturn->token = token;
  toReturn->op.left = left;
  toReturn->op.right = right;
  return toReturn;
}
Node* UnOp(Token op, Node* expr){
  Node* toReturn = (Node*)malloc(sizeof(Node));
  toReturn->class = UNOP;
  toReturn->token = op;
  toReturn->expr = expr;
  return toReturn;
}
    


void consume(Type type){
  if(current_token.type == type){
		printf("Consuming %s\n", TYPE_STRINGS[current_token.type]);
    current_token = next_token();
  }
  else{
    printf("Error consuming %s expected %s instead\n",TYPE_STRINGS[type], TYPE_STRINGS[current_token.type]);
    exit(EXIT_SUCCESS);
  }
}


Node* factor(){
  Token current = current_token;
  if (current_token.type==INT){
  	consume(INT);
  	return Num(current);
  }
  else if(current_token.type==LPAREN){
    consume(LPAREN);
    Node *node = expr();
    consume(RPAREN);
    return node;
  }
  else if(current_token.type==ADD){
    consume(ADD);
    return UnOp(current, factor());
  }
  else if(current_token.type==SUB){
    consume(SUB);
    return UnOp(current, factor());
  }

}

Node* term(){
	Node *node = factor();
	while(current_token.type==MUL || current_token.type==DIV){
		Token op = current_token;
		if(op.type==MUL) {
			consume(MUL);
		}
		else if (op.type==DIV) {
			consume(DIV);
		}
    node = BinOp(op, node, factor());
	}
	return node;
}
Node* expr(){
	Node *node = term();
	while(current_token.type==MUL || current_token.type==DIV||current_token.type==ADD || current_token.type==SUB){
		Token op = current_token;
		if (op.type==ADD) {
			consume(ADD);
		}
		else if (op.type==SUB) {
			consume(SUB);
		}
    node = BinOp(op, node, term());
	}
	return node;
}
