#include "solver.h"
#include <stdio.h>

int main()
{
    char* src = "0 1 -2 14 5";

    Lexer_t* lexer = init_lexer(src);
    int* clause = parse_clause(lexer);
    printf("\n%i", clause[0]);
    printf("\n%i", clause[1]);
    printf("\n%i", clause[2]);
    printf("\n%i", clause[3]);
    printf("\n%i", clause[4]);
}