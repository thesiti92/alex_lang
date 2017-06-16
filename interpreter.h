#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

int visitNum(Node *node);
int visitBinOp(Node *node);
int visit(Node *node);

#endif
