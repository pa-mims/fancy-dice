#include "fancy_dice.h"
#include <stdint.h>

static uint32_t x = 0;                   // default value

typedef uint32_t wheel32;
static wheel32 c_wheel = 19937;         // must be a circular prime
static wheel32 a_wheel = 11939;         // must be a circular prime

static const uint32_t c_multiplier = 7 * 7 * 7 * 7;  // any odd number

// Don't alter these formulas
static const uint32_t max_16bit_number = 65520;
uint32_t a(void) { return (4 * a_wheel + 1); }
uint32_t c(void) { return (c_multiplier * c_wheel); }


uint32_t new_16bits(void) {
    x = a() * x + c();
    if ((x >> 16) > max_16bit_number)
        new_16bits();
    return (x >> 16);
}

/*void rotate_wheel(static wheel32 *wheel) {
    *wheel = *wheel / 10 + 10000 * (*wheel % 10);
    return;
}*/

void seed_dice(int seed) {
    x = (uint32_t)seed;
    return;
}

void shake_dice(int num) {
    new_16bits();
    return;
}

int flip_coin(void) {
    return (int)new_16bits() % 2;
}

int flip_coins(int num) {
    int value = 0;
    for (int i = 0; i < num; i++) value += flip_coin();
    return value;
}

int roll(int num, dice_type dice) {
    int value = 0;
    for (int i = 0; i < num; i++)
        value += (int)new_16bits() % (int)dice;
        if (dice != d10) value++; // d10's go from 0 -> 9
    return value;
}

int roll_percentile(void) {
    int value = roll(1, d10) * 10 + roll(1, d10);
    return (value ? value : 100); // 00 + 0 is 100 for percentile rolls
}
