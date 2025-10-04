#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "solver.h"
#include <stdio.h>

void append_char(char* str, char c)
{
    char temp[2] = {c, '\0'};
    strcat(str, temp);
}

Lexer_t* init_lexer(char* src)
{
    Lexer_t* lexer = malloc(sizeof(Lexer_t));
    if(!lexer)
        return NULL;
    
    lexer->src = src;
    lexer->len = strlen(src);
    lexer->pos = 0;

    return lexer;
}

bool advance_lexer(Lexer_t* lexer)
{
    if(lexer->pos + 1 >= lexer->len)
        return false;
    
    lexer->pos += 1;
    return true;
}

char peek(Lexer_t* lexer)
{
    if(lexer->pos + 1 >= lexer->len)
        return '\0';
    return lexer->src[lexer->pos +1];
}

void skip_whitespace(Lexer_t *lexer)
{
    char c = lexer->src[lexer->pos];

    while((c == ' ' || c == '\t'))
    {     
        advance_lexer(lexer);
        c = lexer->src[lexer->pos];
    }
}

int* parse_clause(Lexer_t* lexer)
{
    int* clause = calloc(MAX_CLAUSE_LENGTH, sizeof(int));

    size_t index = 0;
    while(lexer->src[lexer->pos] != '\n' && lexer->pos < lexer->len)
    {
        skip_whitespace(lexer);
        if(index >= MAX_CLAUSE_LENGTH)
            return NULL;

        char tmp[2] = {lexer->src[lexer->pos], '\0'};

        if(lexer->src[lexer->pos] == '-')
        {
            advance_lexer(lexer);
            if(!isdigit(lexer->src[lexer->pos]))
                return NULL;

            
            char num[64] = "-";

            while(isdigit(lexer->src[lexer->pos]) && lexer->pos < lexer->len)
            {
                append_char(num, lexer->src[lexer->pos]);
                lexer->pos++;
            }
            clause[index] = atoi(num);
            index++;
            lexer->pos++;
            continue;
        }        
        if(!isdigit(lexer->src[lexer->pos]))
                return NULL;

        char num[64] = "";
        while(isdigit(lexer->src[lexer->pos]) && lexer->pos < lexer->len)
        {
            append_char(num, lexer->src[lexer->pos]);
            lexer->pos++;
        }

        clause[index] = atoi(num);
        index++;
        lexer->pos++;
    }

    return clause;
}

int** parse_formula(Lexer_t* lexer)
{
    int** formula = calloc(MAX_FORMULA_LENGTH, sizeof(int*));

    size_t index = 0;
    while(lexer->pos < lexer->len)
    {
        formula[index] = parse_clause(lexer);
        index++;
        lexer->pos++;
    }

    return formula;
}