#include <phevaluator/card_sampler.h>

#include <array>
#include <chrono> //for the system clock
#include <numeric>
#include <random>
#include <utility>
#include <vector>


//this file is used to sample the cards from the deck

namespace card_sampler {

static unsigned seed =
    std::chrono::system_clock::now().time_since_epoch().count(); //for the seed

static std::default_random_engine generator(seed); //for the random number generator 

CardSampler::CardSampler(void) { std::iota(deck.begin(), deck.end(), 0); } //for the initial deck

// This function samples `size` unique cards from the deck using a partial Fisher-Yates shuffle.
// Algorithm explanation:
// - We maintain a "residual" deck of cards (initially all 52).
// - For each card to sample:
//   1. Pick a random index within the range of remaining (unpicked) cards.
//   2. Swap the card at that index with the last unpicked card in the deck.
//   3. Add the swapped card (now at the end of the unpicked range) to the result.
//   4. Reduce the range of unpicked cards by one (so we don't pick the same card again).
// - This ensures each card is sampled uniformly at random and without replacement.

std::vector<int> CardSampler::sample(int size) {
  std::vector<int> ret;
  int residual_cards = deck.size();

  
  for (int i = 0; i < size; i++) {
    // Pick a random index from the remaining unpicked cards
    int target_index = generator() % residual_cards;
    int tail_index = residual_cards - 1;
    // Swap the chosen card to the end of the unpicked range
    std::swap(deck[target_index], deck[tail_index]);
    // Add the selected card to the result
    ret.push_back(deck[tail_index]);
    // Decrease the number of unpicked cards
    residual_cards--;
  }
  return ret;
}
}  // namespace card_sampler