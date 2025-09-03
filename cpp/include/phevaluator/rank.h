 #ifndef PHEVALUATOR_RANK_H
 #define PHEVALUATOR_RANK_H
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 #include <stdbool.h> //used for boolean values
 
 enum rank_category {
   // FIVE_OF_A_KIND = 0, // Reserved for future use
   STRAIGHT_FLUSH = 1,
   FOUR_OF_A_KIND,
   FULL_HOUSE,
   FLUSH,
   STRAIGHT,
   THREE_OF_A_KIND,
   TWO_PAIR,
   ONE_PAIR,
   HIGH_CARD,
 };
 
 /*
  * Given a rank from 1 to 7462
  * Returns an integer from the enum rank_category
  */

// Use an enum as a function's return type to indicate that the function returns one of a set of named integer constants.
// Here, get_rank_category returns a value of type enum rank_category, which is an enum defined above.
// The function will return one of the possible values from the rank_category enum (e.g., STRAIGHT_FLUSH, FOUR_OF_A_KIND, etc.).

//function declaration: 




// Function: get_rank_category
// - Input: int rank (from 1 to 7462)
// - Output: enum rank_category
// - Purpose: Returns the general hand category (e.g., FLUSH, FULL_HOUSE) for a given hand rank value.

enum rank_category get_rank_category(int rank);

// Function: describe_rank_category
// - Input: enum rank_category
// - Output: const char* (string description)
// - Purpose: Returns a human-readable string for the hand category (e.g., "Flush", "Full House") given the enum value.

const char* describe_rank_category(enum rank_category category);

// Function: describe_rank
// - Input: int rank (from 1 to 7462)
// - Output: const char* (string description)
// - Purpose: Returns a detailed string describing the specific hand for the given rank (e.g., "King-High Straight Flush").

const char* describe_rank(int rank);

// Function: describe_sample_hand
// - Input: int rank (from 1 to 7462)
// - Output: const char* (string description)
// - Purpose: Returns a string representing a sample hand for the given rank (e.g., "AKQJT").

const char* describe_sample_hand(int rank);

// Function: is_flush
// - Input: int rank (from 1 to 7462)
// - Output: bool
// - Purpose: Returns true if the given rank corresponds to a flush hand, false otherwise.

bool is_flush(int rank);

#ifdef __cplusplus
}  // closing brace for extern "C"


#endif

#ifdef __cplusplus

#include <array>
#include <string>
#include <vector>

#include "card.h"

namespace phevaluator {

class Rank {
public:
int value() const { return value_; }

// These operator overloads allow you to compare two Rank objects using standard comparison operators.
// Note: In this ranking system, a lower integer value means a stronger hand (e.g., 1 is the best, 7462 is the worst).
// So, for comparisons, we invert the usual logic: a Rank with a lower value_ is considered "greater" poker strength.

// The operator< is needed to allow Rank objects to be compared using standard comparison operators (like <, >, etc.).
// This is especially useful when using Rank as a key in sorted containers (such as std::set or std::map), or when sorting a collection of Rank objects.
// In the context of poker hand rankings, operator< is defined such that a weaker hand (higher integer value) is considered "less than" a stronger hand (lower integer value),
// which is the opposite of the usual numeric comparison, but matches poker logic where a lower rank value means a stronger hand.

// defining 'bool operator<(const Rank& other) const' allows you to write expressions like 'rank1 < rank2' to compare two Rank objects directly.


//inverted logic: 
// 1 is the best hand and 7462 is the worst hand
bool operator<(const Rank& other) const {
    // Returns true if this hand is weaker than the other hand.
    // rank& other is a reference to another rank object other than the current object
    return value_ > other.value_;
}

bool operator<=(const Rank& other) const {
    // Returns true if this hand is weaker than or equal to the other hand.
    return value_ >= other.value_;
}

bool operator>(const Rank& other) const {
    // Returns true if this hand is stronger than the other hand.
    return value_ < other.value_;
}

bool operator>=(const Rank& other) const {
    // Returns true if this hand is stronger than or equal to the other hand.
    return value_ <= other.value_;
}

bool operator==(const Rank& other) const {
    // Returns true if both hands have the same rank value.
    return value_ == other.value_;
}

bool operator!=(const Rank& other) const {
    // Returns true if the hands have different rank values.
    return value_ != other.value_;
}


//function definition: 
// Returns the hand category (e.g., flush, straight, etc.) for this rank.
enum rank_category category() const {
    return get_rank_category(value_);
}

std::string describeCategory() const {
    return describe_rank_category(category());
}

std::string describeRank() const { 
    return describe_rank(value_); 
}

std::string describeSampleHand() const {
    return describe_sample_hand(value_);
}
bool isFlush() const { return is_flush(value_); }


Rank(int value) : value_(value) {} //constructor that creates a Rank object from an integer value
Rank() {} //default constructor that creates a Rank object with a value of 0

private:
int value_ = 0;
};

}  // namespace phevaluator

#endif  // __cplusplus

#endif  // PHEVALUATOR_STRENTH_H