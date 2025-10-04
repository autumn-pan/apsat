#include "solver.h"
#include <stdio.h>

int main()
{
    char* src = "1 \n -1";

    Lexer_t* lexer = init_lexer(src);
    int* clause = parse_clause(lexer);
    
    printf("\n%i",clause[0]);
    fflush(stdout);
    AssignmentMap_t* map = init_map();
    append_var(map);
    map->assignment = 1;

    evaluate_clause(clause, map);
}