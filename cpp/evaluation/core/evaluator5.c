//this file is used to evaluate the 5-card poker hand

#include <stdio.h>

#include "../../math/hash/hash.h"
#include "../../database/tables/tables.h"

/*
* Card id, ranged from 0 to 51.
* The two least significant bits represent the suit, ranged from 0-3.
* The rest of it represent the rank, ranged from 0-12.
* 13 * 4 gives 52 ids.
*/



int evaluate_5cards(int a, int b, int c, int d, int e) {
int suit_hash = 0;

suit_hash += bit_of_mod_4_x_3[a];  // (1 << ((a % 4) * 3))
suit_hash += bit_of_mod_4_x_3[b];  // (1 << ((b % 4) * 3))
suit_hash += bit_of_mod_4_x_3[c];  // (1 << ((c % 4) * 3))
suit_hash += bit_of_mod_4_x_3[d];  // (1 << ((d % 4) * 3))
suit_hash += bit_of_mod_4_x_3[e];  // (1 << ((e % 4) * 3))

if (suits[suit_hash]) {
    int suit_binary[4] = {0};

    suit_binary[a & 0x3] |= bit_of_div_4[a];  // (1 << (a / 4))
    suit_binary[b & 0x3] |= bit_of_div_4[b];  // (1 << (b / 4))
    suit_binary[c & 0x3] |= bit_of_div_4[c];  // (1 << (c / 4))
    suit_binary[d & 0x3] |= bit_of_div_4[d];  // (1 << (d / 4))
    suit_binary[e & 0x3] |= bit_of_div_4[e];  // (1 << (e / 4))

    return flush[suit_binary[suits[suit_hash] - 1]];
}

unsigned char quinary[13] = {0};

quinary[(a >> 2)]++;
quinary[(b >> 2)]++;
quinary[(c >> 2)]++;
quinary[(d >> 2)]++;
quinary[(e >> 2)]++;

const int hash = hash_quinary(quinary, 5);

return noflush5[hash];
}