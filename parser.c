#include "interpreter.h"
Token current_token;
extern const char * TYPE_STRINGS[];
Node* toReturn;
Node* statements;

Node* Num(Token token){
  free(toReturn);
  toReturn = malloc(sizeof(Node));
  toReturn->class = CONSTANT;
  toReturn->token = token;
  toReturn->value = token.value;
  return toReturn;
}

Node* BinOp(Token token, Node* left, Node* right){
  free(toReturn);
  toReturn = malloc(sizeof(Node));
  toReturn->class = BINOP;
  toReturn->token = token;
  toReturn->op.left = left;
  toReturn->op.right = right;
  return toReturn;
}

Node* UnOp(Token op, Node* expr){
  free(toReturn);
  toReturn = malloc(sizeof(Node));
  toReturn->class = UNOP;
  toReturn->token = op;
  toReturn->expr = expr;
  return toReturn;
}

Node* NoOp(){
  free(toReturn);
  toReturn = malloc(sizeof(Node));
  toReturn->class = NOOP;
  return toReturn;
}

Node* AssOp(Token token, Node* left, Node* right){
  free(toReturn);
  toReturn = malloc(sizeof(Node));
  toReturn->class = ASSOP;
  toReturn->token = token;
  toReturn->op.left = left;
  toReturn->op.right = right;
  return toReturn;
}

Node* Var(Token token){
  free(toReturn);
  toReturn = malloc(sizeof(Node));
  toReturn->class = VAR;
  toReturn->token = token;
  toReturn->id = token.id;
  return toReturn;
}

Node* Compound(Node* children, int size){
  free(toReturn);
  toReturn =  malloc(sizeof(Node));
  memcpy(toReturn->children, children, sizeof(Node)*size);
  toReturn->class = COMPOUND;
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
  else{
    return variable();
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

Node* program(){
  Node *node = compound_statement();
  consume(DOT);
  return node;
}

Node* compound_statement(){
  consume(BEGIN);
  Node* nodes = statement_list();
  Node* node = Compound(nodes, sizeof(nodes->children)/sizeof(nodes->children[0]));
  consume(END);
  return node;
}

Node* statement_list(){
  free(statements);
  statements = malloc(sizeof(Node));
  int size = 1;
  statements->children[0] = statement();
  while(current_token.type == SEMI){
    consume(SEMI);
    memcpy(statements->children, realloc(statements->children, size * sizeof(Node*)), size * sizeof(Node*));
    statements->children[size] = statement();
    size++;
  }
  if(current_token.type == ID){
    printf("Syntax Error in parsing statement_list\n");
  }
  printf("returning statement block\n");
  return statements;
}

Node* statement(){
  if(current_token.type == BEGIN){
    return compound_statement();
  }
  else if(current_token.type == ID){
    return assignment_statement();
  }
  else{
    return NoOp();
  }
}

Node* assignment_statement(){
  Node* left = variable();
  Token assign = current_token;
  consume(ASSIGN);
  Node* right = expr();
  return AssOp(assign, left, right);
}

Node* variable(){
  Node *node = Var(current_token);
  consume(ID);
  return node;
}
