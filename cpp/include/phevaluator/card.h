#ifndef PHEVALUATOR_CARD_H
#define PHEVALUATOR_CARD_H
#ifdef __cplusplus
#include <array>
#include <functional> //for hash
#include <string>
#include <unordered_map>

namespace phevaluator {
    //use namespace here as a container to prevent name collisions and for readability
const static std::unordered_map<char, int> rankMap = {
    //using unorder_map here because we want the fastest possible average-case lookups and insertions. 
    //order of elements are not important here as we defined the key value pairs here
    {'2', 0}, {'3', 1}, {'4', 2}, {'5', 3},  {'6', 4},  {'7', 5},  {'8', 6},
    {'9', 7}, {'T', 8}, {'J', 9}, {'Q', 10}, {'K', 11}, {'A', 12},
};
const static std::unordered_map<char, int> suitMap = {
    // 'C' or 'c' (Clubs) -> 0
    // 'D' or 'd' (Diamonds) -> 1
    // 'H' or 'h' (Hearts) -> 2
    // 'S' or 's' (Spades) -> 3
    {'C', 0}, {'D', 1}, {'H', 2}, {'S', 3},
    {'c', 0}, {'d', 1}, {'h', 2}, {'s', 3},
};
const static std::array<char, 13> rankReverseArray = {
    '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A',
};
const static std::array<char, 4> suitReverseArray = {'c', 'd', 'h', 's'};

class Card {
 public:
  Card() {} //default constructor

  // Constructor that creates a Card from its integer id (0-51)
  Card(int id) {
    id_ = id;
  }
  //the id_(id) is the member variable of the class Card

  Card(std::string name) { //this is the constructor that creates a Card from its string name
    if (name.length() < 2) {
      // TODO: throw an exception here (Done)
      throw std::invalid_argument("Invalid Card Name");
    }

    // This line converts a card's string name (like "As" for Ace of spades) into its unique integer id (0-51).
    // - rankMap.at(name[0]) looks up the rank character (e.g., 'A' -> 12 for Ace) and gets its index (0-12).
    // - suitMap.at(name[1]) looks up the suit character (e.g., 's' -> 3 for spades) and gets its index (0-3).
    //  Multiplying the rank index by 4 allocates 4 consecutive ids for each rank (one for each suit). Adding the suit index (0-3) then selects the specific suit within that rank. This ensures every card (rank, suit) pair gets a unique id from 0 to 51.
    //   id = rank_index * 4 + suit_index, so cards are ordered by rank, then suit.
    id_ = rankMap.at(name[0]) * 4 + suitMap.at(name[1]);
  }

  Card(const char* name) { *this = Card(std::string(name)); } //constructor that creates a Card from its string name

  char describeRank(void) const { 
    int rank_index = id_ / 4;
    if (rank_index > 12 || rank_index < 0) {
      throw std::invalid_argument("Invalid Rank");
    }//error handling for invalid rank
    return rankReverseArray[rank_index]; 
} //returns the rank of the card

  char describeSuit(void) const { 
    int suit_index = id_ % 4;
    if (suit_index > 3 || suit_index < 0) {
      throw std::invalid_argument("Invalid Suit");
    }//error handling for invalid suit
    return suitReverseArray[suit_index]; 

} //returns the suit of the card

  std::string describeCard(void) const {
    return std::string{describeRank(), describeSuit()}; 
    //returns the string representation of the card: rank + suit e.g. "As" for Ace of spades
  }

  //converts the Card object to an integer, which is the id_ of the card
  //expected input: Card object
  operator int() const { return id_; }

  //converts the Card object to a string, which is the string representation of the card
  //expected input: Card object
  operator std::string() const { return describeCard(); }

 private:
  int id_;
};

}  // namespace phevaluator: finish defining the Card class

// This code specializes the std::hash template for the phevaluator::Card class,
// allowing Card objects to be used as keys in hash-based containers like std::unordered_map or std::unordered_set.
//
// - The specialization is placed in the std namespace, as required by the C++ standard for custom hash specializations.
// - The struct hash<phevaluator::Card> defines how to compute a hash value for a Card object.
// - The operator() takes a const reference to a Card and returns a size_t hash value.
// - It does this by converting the Card to its integer id (via the Card's int conversion operator), and then
//   applies std::hash<int> to that id. This ensures that the hash value for a Card is simply the hash of its unique id.
// - This approach is efficient and guarantees that each Card will have a unique hash value corresponding to its id.

// This allows Card objects to be used as keys in hash tables like unordered_map.
// We tell the C++ standard library how to hash a Card: just use its id number.
namespace std {
template <>
struct hash<phevaluator::Card> {
  size_t operator()(const phevaluator::Card& card) const {
    //size_t is an unsigned integer type that can represent the size of any object in bytes.
    // Get the card's id (as an int) and use the standard hash for int
    int card_id = static_cast<int>(card);
    return std::hash<int>()(card_id);
  }
};
} // namespace std

#endif  // __cplusplus
#endif  // PHEVALUATOR_CARD_H