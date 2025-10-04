#ifndef SOLVER_H
#define SOLVER_H

#include <stdlib.h>

#define MAX_CLAUSE_LENGTH 16
#define MAX_FORMULA_LENGTH 16

typedef struct
{
    int formula[MAX_CLAUSE_LENGTH][MAX_FORMULA_LENGTH];
} Formula_t;

typedef struct
{

    char* src;
    size_t len;
    size_t pos;
} Lexer_t;

Lexer_t* init_lexer(char* src);
int* parse_clause(Lexer_t* lexer);
int** parse_formula(Lexer_t* lexer);
#endif