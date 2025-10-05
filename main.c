#include "solver.h"
#include <stdio.h>

int main()
{
    char* src = "-1 \n 1";

    Lexer_t* lexer = init_lexer(src);

    AssignmentMap_t* map = init_map();
    append_var(map);
    int** formula = parse_formula(lexer);

    map->assignment = 0;

    printf("\nClause: %i", evaluate_formula(formula, map, 2));
}
