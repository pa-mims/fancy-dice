#include <stdio.h>
#include "fancy_dice.h"

int main(int argc, char *argv[]) {
    printf("\n\nPress <ENTER> to flip a coin, roll d20, and roll percentile.");
    printf("\nEnter Q to exit.\n");

    seed_dice(457773);
    shake_dice(5);

    char ch = '\0';
    do {
        printf("----------\n");
        printf("   %d\n", flip_coin());
        printf("   %d\n", roll(1, d20));
        printf("   %d\n", roll_percentile());
        ch = getchar();
    } while (ch != 'q' && ch != 'Q');

    return 0;
}
