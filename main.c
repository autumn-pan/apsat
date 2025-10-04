#include "solver.h"
#include <stdio.h>

int main()
{
    char* src = "0 1 -2 14 5 \n 12";

    Lexer_t* lexer = init_lexer(src);
    int** formula = parse_formula(lexer);
    printf("%i", formula[1][0]);
}