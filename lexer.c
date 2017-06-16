#include "interpreter.h"
int current_pos = 0;
char current_char;
long length_of_input;
char * buffer;


Token next_token(){
  if(isdigit(current_char)){
    Token current;
    current.type = INT;
    current.value = integer();
    return current;
  }
  else if(current_char == '+'){
		advance();
    Token current;
    current.type = ADD;
    return current;
  }
  else if(current_char == '-'){
		advance();
    Token current;
    current.type = SUB;
    return current;
  }
	else if(current_char == '*'){
		advance();
		Token current;
    current.type = MUL;
		return current;
	}
	else if(current_char == '/'){
		advance();
		Token current;
    current.type = DIV;
		return current;
	}
  else if(current_char == '('){
    advance();
    Token current;
    current.type = LPAREN;
    return current;
  }
  else if(current_char == ')'){


    advance();
    Token current;
    current.type = RPAREN;
    return current;
  }

  Token current;
  current.type = EOS;
  return current;

}
int integer(){
	char result[10] = "";
	while(isdigit(current_char) && current_pos<length_of_input){
		strncat(result, &current_char,1);
		advance();
	}
	return atoi(result);
}
void advance(){
  current_pos++;
  if(current_pos>length_of_input){
    printf("End of Sequence\n");
    return;
  }

  current_char = buffer[current_pos];
}
char peek(){
  int peek_pos = current_pos + 1;
  if(peek_pos>length_of_input){
    return 0;
  }
  return buffer[peek_pos];
}
int index_of(char* string, char* array[], int size){
  for(int i=0; i<size; i++){
    if(strcmp(array[i], string) == 0){
      return i;
    }
  }
  return -1;
}
void _id(){
  char result[10] = "";
  while(isalnum(current_char)!=0 && current_pos<length_of_input){
    strncat(result, &current_char, 1);
    advance();
  }
  Token toreturn;
  toreturn.type = index_of(result, KEYWORD_STRINGS, sizeof(KEYWORD_STRINGS)/sizeof(KEYWORD_STRINGS[0]));
  return toreturn;
}
