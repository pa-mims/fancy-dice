#include <curses.h>
#include "fancy_dice.h"

int main(int argc, char *argv[]) {
    initscr();
    noecho();
    while (getch() != 'q') {
        clear();
        printw("%d\n", flip_coin());
        printw("%d\n", roll(1, d20));
        printw("%d\n", roll_percentile());
    }
    endwin();
    return 0;
}
