#include "solver.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));
    char* formula = gen_formula(4);
    printf(formula);

    printf("\nSolution: %i", solve(formula));
}