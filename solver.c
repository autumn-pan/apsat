#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "solver.h"
#include <stdio.h>

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

char eat(Lexer_t* lexer)
{
    if(lexer->pos + 1 >= lexer->len)
        return '\0';
    advance_lexer(lexer);
    return lexer->src[lexer->pos-1];
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
    while(lexer->src[lexer->pos] != '\0')
    {
        skip_whitespace(lexer);
        if(index >= MAX_CLAUSE_LENGTH)
            return NULL;

        if(lexer->src[lexer->pos] == '-')
        {
            eat(lexer);
            if(!isdigit(lexer->src[lexer->pos]))
                return NULL;

            char temp[3] = {'-', eat(lexer), '\0'};
            clause[index] = atoi(temp);
            index++;
            continue;
        }        

        if(!isdigit(lexer->src[lexer->pos]))
                return NULL;

        char temp[2] = {eat(lexer), '\0'};
        clause[index] = atoi(temp);
        index++;
    }

    return clause;
}