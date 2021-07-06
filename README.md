## Fancy Dice

This project uses a custom PRNG to simulate dice rolls and return the results. The aim of this project is to create a statistically-fair-enough set of dice to roll for simple applications.

### Functions - fancy_dice.h

The following functions are available:

**seed_dice**(int *seed*) - This function is for setting the seed of the PRNG to a
known value.

**flip_coin**() - This function returns either 1 or 0 to represent heads or tails.

**flip_coins**(int *num*) - This function flips *num* amount of coins and returns the number of heads results.

**roll**(int *num*, dice_type *dice*) - The dice_type enumeration contains the following
values:
- d4
- d6
- d8
- d10
- d20
Calling this function should be intuitively familiar.
"Roll three d6." -> roll(3, d6);

**roll_percentile**() - This function performs two d10 rolls to return a number between 1 and 100, inclusively.

**shake_dice**(int *num*) - In order to prevent the dice roll algorithm from being deterministically modeled into future rolls easily, this function alters the constants used within the PRNG that governs the dice roll results.

### Under the Hood - fancy_dice.c

This dice simulator runs on top of a simple [linear congruential generator](https://en.wikipedia.org/wiki/Linear_congruential_generator) algorithm. The PRNG seed, **x**, is a 32-bit unsigned integer value. The constants **a** and **c** were chosen to maximize the period of the PRNG.

Instead of having **a** and **c** exist as constants, the values are calculated by using what I have referred to in code as a *wheel*. A *wheel* is a [circular prime number](https://en.wikipedia.org/wiki/Circular_prime). As such, the digits of the wheels can be "turned" by moving the last digit to the first position, and the number will remain prime.

When **shake_dice**() is called, the wheels rotate algorithmically such that the values **a** and **c**, which govern the PRNG, are different. This function could be used based on some other input to make the next roll appear less deterministic.

When the PRNG is rolled, the least significant 16 bits is thrown away via bitshift. If the resulting 16 bit number is larger than 65520, the result is thrown away and the PRNG is rolled again. The results of the various functions use this value and modulus math to return a die result.

The **max_16bit_number**, 65520, is chosen because it is divisible by the least common multiple of 4, 6, 8, 10, 12, and 20. Throwing away PRNG results greater than this number ensures that for one complete period of the PRNG, the results of a single die type will not be weighted.
