#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "solver.h"
#include <stdio.h>
#include <limits.h>
#include <time.h>

void append_char(char* str, char c)
{
    char temp[2] = {c, '\0'};
    strcat(str, temp);
}
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
    while(lexer->pos < lexer->len && lexer->src[lexer->pos] != '\n')
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

            while(lexer->pos < lexer->len && isdigit(lexer->src[lexer->pos]))
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

bool get_bit(uint32_t integer, size_t bit)
{
    return ((integer & (1 << bit)) >> bit);
}

bool evaluate_clause(int clause[MAX_CLAUSE_LENGTH], AssignmentMap_t* map)
{
    for(int i = 0; i < MAX_CLAUSE_LENGTH; i++)
    {
        int literal = clause[i];
        // Literals cannot be 0, because then they can't be negated and are therefore not booleans
        if(literal == 0)
            break;

        int index = abs(literal) - 1;
        bool value = get_bit(map->assignment, index);

        if(literal > 0 && value)
            return true;
        else if(literal < 0 && !value)
            return true;
    }
    
    return false;
}

bool evaluate_formula(int** formula, AssignmentMap_t* map, size_t num_clauses)
{
    for(int i = 0; i < num_clauses; i++)
    {
        if(!evaluate_clause(formula[i], map))
            return false;
    }

    return true;
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

uint64_t solve_formula(int** formula, AssignmentMap_t* map, size_t num_clauses)
{
    uint64_t max_size = (1ULL << map->num_vars);

    map->assignment = 0;

    while(map->assignment < max_size)
    {
        if(evaluate_formula(formula, map, num_clauses))
        {
            return map->assignment;
        }

        map->assignment++;
    }

    return ULONG_MAX;
}

int solve(char* formula)
{
    char* src = "1 2 \n -1 3 \n -2 4 \n -3 -4";

    uint8_t max = 0;
    AssignmentMap_t* map = init_map();

    int num_clauses = 1;

    for(int i = 0; i < strlen(src); i++)
    {
        if(isdigit(src[i]))
        {
            if(src[i] - 48 > max)
            {
                max = src[i] - 48;
            }

        }
        else if (src[i] == '\n')
            num_clauses++;
    }

    map->num_vars = max;

    Lexer_t* lexer = init_lexer(src);

    int** formula = parse_formula(lexer);

    int solution = solve_formula(formula, map, num_clauses);
    free(lexer);
    free(map);

    return solution;
}

int** gen_formula()
{
    int num_clauses = srand(time(0));
}