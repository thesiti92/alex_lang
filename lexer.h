#ifndef LEXER_H
#define LEXER_H

#define FOREACH_TYPE(TYPE)\
	TYPE(ADD)	\
	TYPE(SUB)	\
	TYPE(MUL)	\
	TYPE(DIV)	\
	TYPE(INT)	\
	TYPE(LPAREN)	\
	TYPE(RPAREN)	\
	TYPE(EOS)	\
	TYPE(DOT)	\
	TYPE(SEMI)	\
	TYPE(ASSIGN)	\
	TYPE(ID) \

	#define FOREACH_KEYWORD(KEYWORD) \
	        KEYWORD(BEGIN)   \
	        KEYWORD(END)  \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

#define FOREACH_JOIN_ENUM
#define FOREACH_JOIN_STRING

typedef enum Type {
    FOREACH_KEYWORD(GENERATE_ENUM) FOREACH_TYPE(GENERATE_ENUM)
} Type;

static const char *TYPE_STRINGS[] = {
    FOREACH_KEYWORD(GENERATE_STRING) FOREACH_TYPE(GENERATE_STRING)
};

typedef struct Token {
	int value;
  Type type;
} Token;

Token next_token();
int integer();
void advance();
char peek();
int index_of(char* string, char* array[], int size);
void _id();


#endif
