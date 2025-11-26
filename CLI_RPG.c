#include <stdio.h>
#include "./include/game.h"

int main()
{
    puts("================[RPG START]================");

    unsigned long long loopCnt = startGame();

    puts("================[FINISHED]================");
    printf("The game ended with %llu loops", loopCnt);

    return 0;
}
