
#include <phevaluator/rank.h>

#include "../../database/tables/tables.h"

const char* rank_category_description[] = {
    "",         "Straight Flush",  "Four of a Kind", "Full House", "Flush",
    "Straight", "Three of a Kind", "Two Pair",       "One Pair",   "High Card",
};

enum rank_category get_rank_category(int rank) {
if (rank > 6185) return HIGH_CARD;        // 1277 high card
if (rank > 3325) return ONE_PAIR;         // 2860 one pair
if (rank > 2467) return TWO_PAIR;         //  858 two pair
if (rank > 1609) return THREE_OF_A_KIND;  //  858 three-kind
if (rank > 1599) return STRAIGHT;         //   10 straights
if (rank > 322) return FLUSH;             // 1277 flushes
if (rank > 166) return FULL_HOUSE;        //  156 full house
if (rank > 10) return FOUR_OF_A_KIND;     //  156 four-kind
return STRAIGHT_FLUSH;                    //   10 straight-flushes
}

const char* describe_rank_category(enum rank_category category) {
return rank_category_description[category];
}

const char* describe_rank(int rank) { return rank_description[rank][1]; }

const char* describe_sample_hand(int rank) { return rank_description[rank][0]; }

bool is_flush(int rank) {
switch (get_rank_category(rank)) {
    case STRAIGHT_FLUSH:
    case FLUSH:
    return true;
    default:
    return false;
}
}