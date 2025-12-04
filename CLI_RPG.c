#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "./include/game.h"

int main()
{
    srand(time(NULL));

    puts("================[RPG START]================");

    unsigned long long loopCnt = startGame();

    puts("================[FINISHED]================");
    printf("The game ended with %llu loops", loopCnt);

    return 0;
}
