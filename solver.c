#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "solver.h"
#include <stdio.h>
#include <stdint.h>

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

        char tmp[2] = {lexer->src[lexer->pos], '\0'};

        if(lexer->src[lexer->pos] == '-')
        {
            eat(lexer);
            if(!isdigit(lexer->src[lexer->pos]))
                return NULL;

            char temp[3] = {'-', lexer->src[lexer->pos], '\0'};
            clause[index] = atoi(temp);
            index++;
            lexer->pos++;
            continue;
        }        
        if(!isdigit(lexer->src[lexer->pos]))
                return NULL;

        char temp[2] = {eat(lexer), '\0'};
        clause[index] = atoi(temp);
        index++;
        lexer->pos++;
    }

    return clause;
}

AssignmentMap_t* init_map()
{
    AssignmentMap_t* map = malloc(sizeof(AssignmentMap_t));
    map->assignment = 0;
    map->num_vars = 0;

    return map;
}

void append_var(AssignmentMap_t* map)
{
    map->num_vars++;
}

int get_bit(uint32_t integer, size_t bit)
{
    return ((integer & (1 << bit)) >> bit);
}

bool evaluate_clause(int clause[MAX_CLAUSE_LENGTH], AssignmentMap_t* map)
{
    for(int i = 0; i < map->num_vars; i++)
    {
        for(int j = 0; j < MAX_CLAUSE_LENGTH; j++)
        {
            if(clause[j] < 0 && clause[j] == i && !get_bit(map->assignment, clause[j]))
                return true;
            else if(clause[j] == i && get_bit(map->assignment, clause[j]))
                return true;
        }
    }
    return false;
}