#include "../../math/hash/hash.h"
#include "../../database/tables/tables.h"

static int hash_binary(const int binary, int k) {
// The binary should have 15 bits
int sum = 0;
int i;
const int len = 15;

for (i = 0; i < len; i++) {
    if (binary & (1 << i)) {
    if (len - i - 1 >= k) sum += choose[len - i - 1][k];

    k--;

    if (k == 0) {
        break;
    }
    }
}

return sum;
}

/*
* Card id, ranged from 0 to 51.
* The two least significant bits represent the suit, ranged from 0-3.
* The rest of it represent the rank, ranged from 0-12.
* 13 * 4 gives 52 ids.
*
* The first five parameters are the community cards on the board
* The last four parameters are the hole cards of the player
*/
int evaluate_plo4_cards(int c1, int c2, int c3, int c4, int c5, int h1, int h2,
                        int h3, int h4) {
int value_flush = 10000;
int value_noflush = 10000;
int suit_count_board[4] = {0};
int suit_count_hole[4] = {0};

suit_count_board[c1 & 0x3]++;
suit_count_board[c2 & 0x3]++;
suit_count_board[c3 & 0x3]++;
suit_count_board[c4 & 0x3]++;
suit_count_board[c5 & 0x3]++;

suit_count_hole[h1 & 0x3]++;
suit_count_hole[h2 & 0x3]++;
suit_count_hole[h3 & 0x3]++;
suit_count_hole[h4 & 0x3]++;

for (int i = 0; i < 4; i++) {
    if (suit_count_board[i] >= 3 && suit_count_hole[i] >= 2) {
    // flush
    int suit_binary_board[4] = {0};
    suit_binary_board[c1 & 0x3] |= bit_of_div_4[c1];  // (1 << (c1 / 4))
    suit_binary_board[c2 & 0x3] |= bit_of_div_4[c2];  // (1 << (c2 / 4))
    suit_binary_board[c3 & 0x3] |= bit_of_div_4[c3];  // (1 << (c3 / 4))
    suit_binary_board[c4 & 0x3] |= bit_of_div_4[c4];  // (1 << (c4 / 4))
    suit_binary_board[c5 & 0x3] |= bit_of_div_4[c5];  // (1 << (c5 / 4))

    int suit_binary_hole[4] = {0};
    suit_binary_hole[h1 & 0x3] |= bit_of_div_4[h1];  // (1 << (h1 / 4))
    suit_binary_hole[h2 & 0x3] |= bit_of_div_4[h2];  // (1 << (h2 / 4))
    suit_binary_hole[h3 & 0x3] |= bit_of_div_4[h3];  // (1 << (h3 / 4))
    suit_binary_hole[h4 & 0x3] |= bit_of_div_4[h4];  // (1 << (h4 / 4))

    if (suit_count_board[i] == 3 && suit_count_hole[i] == 2) {
        value_flush = flush[suit_binary_board[i] | suit_binary_hole[i]];
    } else {
        // Padding is trying to make sure the binary has the same amount of
        // bits set. For the board cards, we want 5 bits set, and for the hole
        // cards, we want 4 bits set.
        // For example, if the current board binary has only 3 bits set, we
        // need to pad 2 extra bits.
        // The resulting binary will have 15 bits in total, with 5 bits set for
        // the board binary, and 4 bits set for the hole binary.
        const int padding[3] = {0x0000, 0x2000, 0x6000};

        suit_binary_board[i] |= padding[5 - suit_count_board[i]];
        suit_binary_hole[i] |= padding[4 - suit_count_hole[i]];

        const int board_hash = hash_binary(suit_binary_board[i], 5);
        const int hole_hash = hash_binary(suit_binary_hole[i], 4);

        value_flush = flush_plo4[board_hash * 1365 + hole_hash];
    }

    break;
    }
}

unsigned char quinary_board[13] = {0};
unsigned char quinary_hole[13] = {0};

quinary_board[(c1 >> 2)]++;
quinary_board[(c2 >> 2)]++;
quinary_board[(c3 >> 2)]++;
quinary_board[(c4 >> 2)]++;
quinary_board[(c5 >> 2)]++;

quinary_hole[(h1 >> 2)]++;
quinary_hole[(h2 >> 2)]++;
quinary_hole[(h3 >> 2)]++;
quinary_hole[(h4 >> 2)]++;

const int board_hash = hash_quinary(quinary_board, 5);
const int hole_hash = hash_quinary(quinary_hole, 4);

value_noflush = noflush_plo4[board_hash * 1820 + hole_hash];

if (value_flush < value_noflush)
    return value_flush;
else
    return value_noflush;
}

int evaluate_omaha_cards(int c1, int c2, int c3, int c4, int c5, int h1, int h2,
                        int h3, int h4) {
return evaluate_plo4_cards(c1, c2, c3, c4, c5, h1, h2, h3, h4);
}