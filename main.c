#include "solver.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int main()
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

    printf("\nMax: %i", max);
    fflush(stdout);
    Lexer_t* lexer = init_lexer(src);

    int** formula = parse_formula(lexer);

    printf("\nClause: %i", solve_formula(formula, map, num_clauses));
}
