#include "solver.h"

int main()
{
    char* src = "0 1 -2 14 5";

    Lexer_t* lexer = init_lexer(src);
    parse_clause(lexer);
}