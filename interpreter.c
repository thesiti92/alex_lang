#include "interpreter.h"
extern char * buffer;
extern char current_char;
extern int length_of_input;
extern Token current_token;
extern const char * TYPE_STRING[];

int visitNum(Node *node){
  return node->value;
}
int visitUnOp(Node *node){
  switch(node->token.type){
    case ADD:
      return +visit(node->expr);
    case SUB:
      return -visit(node->expr);
  }
}

int visitBinOp(Node *node){
  switch(node->token.type){
    case ADD:
      return visit(node->op.left) + visit(node->op.right);
    case SUB:
      return visit(node->op.left) - visit(node->op.right);
    case MUL:
      return visit(node->op.left) * visit(node->op.right);
    case DIV:
      return visit(node->op.left) / visit(node->op.right);
  }
}
int visit(Node *node){
  switch(node->class){
    case BINOP:
      return visitBinOp(node);
    case CONSTANT:
      return visitNum(node);
    case UNOP:
      return visitUnOp(node);
  }
}
int main(int argc, char *argv[])
{
  FILE * f = fopen (argv[1], "rb");
  buffer = 0;
  long length;
  if (f)
  {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
      fread (buffer, 1, length, f);
    }
    fclose (f);
  }
  else{
    printf("No File Found!\n");
    return 0;
  }
  length_of_input = length/sizeof(buffer[0]) - 2;
  current_char =  buffer[0];
  current_token = next_token();
  Node *head = expr();
  // for(int i=BEGIN; i<ID+1; i++){
  //   printf("%s\n", TYPE_STRING[i]);
  // }
  // printf("%d\n", );
  printf("%d\n", visit(head));

	return 0;
}
