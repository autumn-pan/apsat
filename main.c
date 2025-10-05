#include "solver.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "contract.h"

int main()
{
    // Contracts
    Contract* easy[4] = {
        init_contract("database-0", "An encrypted database full of passwords. Crack it and leave no trace.", 500, 350, 1),
        init_contract("bank_camera_13", "Wipe all data from the camera's history, and make it unrecoverable.", 650, 400, 1),
        init_contract("iris", "Contains evidence. Destroy everything", 1000, 700, 1),
        init_contract("anubis", "Security camera layout with outdated software.", 1200, 900, 1)
    };

    Contract* medium[4] = {
        init_contract("art_museum", "Take a screenshot of the art through the security cameras.", 1500, 1000, 2),
        init_contract("bank", "Find the passwords to this bank without a trace. You'll get a fair cut.", 2000, 2200, 2),
        init_contract("horse_decimator", "Destroy the horse decimator, it keeps decimating our horses.", 2200, 3000, 2),
        init_contract("helix", "Get the blueprint and don't leave a trace.", 3000, 4000, 2)
    };

    Contract* hard[2] = {
        init_contract("obilisk","A rival company about to overtake us. Take them down.", 5000, 7500, 3),
        init_contract("bro's wifi", "it will be a funny prank i swear", 7500, 10000, 3)
    };

    Contract* finale = init_contract("gamma", "Nuclear weapons program. Poses a threat to world peace. Destroy it.", 100000, 1000000, 5);

    srand(time(0));
    int32_t money = 100;

    printf("┌────────────────────────────────────────────────────┐ \n│ Hostname     █  localhost                          │\n│ OS           █  Silly Linux                        │\n│ Kernel       █  Linux 6.16.8                       │\n│ Uptime       █  67   days                          │\n│ Packages     █  1128                               │\n│ Shell        █  bash 5.3.3                         │\n└────────────────────────────────────────────────────┘");
    while(money > 0)
    {
        printf("\n\nWelcome, User.\nBalance: %i", money);

    }
}