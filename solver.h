#ifndef SOLVER_H
#define SOLVER_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_CLAUSE_LENGTH 16
#define MAX_FORMULA_LENGTH 16
#define MAX_VARIABLES 32
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

typedef struct 
{
    uint32_t assignment;
    size_t num_vars;
} AssignmentMap_t;

AssignmentMap_t* init_map();

Lexer_t* init_lexer(char* src);
int* parse_clause(Lexer_t* lexer);
void append_var(AssignmentMap_t* map);
bool evaluate_clause(int clause[MAX_CLAUSE_LENGTH], AssignmentMap_t* map);

#endif