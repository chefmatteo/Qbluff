#include <stdio.h>
#include "../../math/hash/hash.h"
#include "../../database/tables/tables.h"

// This file is used to evaluate the 6-card poker hand
// It finds the best 5-card hand from 6 cards

/*
* Card id, ranged from 0 to 51.
* The two least significant bits represent the suit, ranged from 0-3.
* The rest of it represent the rank, ranged from 0-12.
* 13 * 4 gives 52 ids.
*/
int evaluate_6cards(int a, int b, int c, int d, int e, int f) {
    int best_rank = 10000; // Start with worst possible rank
    
    // Try all possible 5-card combinations from the 6 cards
    int cards[6] = {a, b, c, d, e, f};
    
    // Evaluate all 6 possible 5-card combinations
    int combinations[6][5] = {
        {a, b, c, d, e},     // Drop f
        {a, b, c, d, f},     // Drop e
        {a, b, c, e, f},     // Drop d
        {a, b, d, e, f},     // Drop c
        {a, c, d, e, f},     // Drop b
        {b, c, d, e, f}      // Drop a
    };
    
    for (int i = 0; i < 6; i++) {
        int suit_hash = 0;
        suit_hash += bit_of_mod_4_x_3[combinations[i][0]];
        suit_hash += bit_of_mod_4_x_3[combinations[i][1]];
        suit_hash += bit_of_mod_4_x_3[combinations[i][2]];
        suit_hash += bit_of_mod_4_x_3[combinations[i][3]];
        suit_hash += bit_of_mod_4_x_3[combinations[i][4]];
        
        int current_rank = 10000;
        
        if (suits[suit_hash]) {
            int suit_binary[4] = {0};
            suit_binary[combinations[i][0] & 0x3] |= bit_of_div_4[combinations[i][0]];
            suit_binary[combinations[i][1] & 0x3] |= bit_of_div_4[combinations[i][1]];
            suit_binary[combinations[i][2] & 0x3] |= bit_of_div_4[combinations[i][2]];
            suit_binary[combinations[i][3] & 0x3] |= bit_of_div_4[combinations[i][3]];
            suit_binary[combinations[i][4] & 0x3] |= bit_of_div_4[combinations[i][4]];
            
            current_rank = flush[suit_binary[suits[suit_hash] - 1]];
        }
        
        unsigned char quinary[13] = {0};
        quinary[(combinations[i][0] >> 2)]++;
        quinary[(combinations[i][1] >> 2)]++;
        quinary[(combinations[i][2] >> 2)]++;
        quinary[(combinations[i][3] >> 2)]++;
        quinary[(combinations[i][4] >> 2)]++;
        
        const int hash = hash_quinary(quinary, 5);
        int noflush_rank = noflush5[hash];
        
        if (noflush_rank < current_rank) {
            current_rank = noflush_rank;
        }
        
        if (current_rank < best_rank) {
            best_rank = current_rank;
        }
    }
    
    return best_rank;
}