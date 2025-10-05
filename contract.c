#include <stdint.h>
/*  */
typedef struct
{
    char* name;
    char* context;
    uint32_t payout;
    uint32_t fine;
    uint8_t difficulty;
} Contract;

Contract* init_contract(char* name, char* context, uint32_t payout, uint32_t fine, uint8_t difficulty)
{
    Contract* contract = malloc(sizeof(Contract));
    contract->name = name;
    contract->payout = payout;
    contract->fine = fine;
    contract->difficulty = difficulty;
    contract->context = context;
}

Contract* CONTRACTS_EASY = calloc(16, sizeof(Contract)):