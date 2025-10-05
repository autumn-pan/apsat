typedef struct
{
    char* name;
    char* context;
    uint32_t payout;
    uint32_t fine;
    uint8_t difficulty;
} Contract;

Contract* init_contract(char* name, char* context, uint32_t payout, uint32_t fine, uint8_t difficulty);