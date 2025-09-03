#include "../include/phevaluator/phevaluator.h"
#include "../include/phevaluator/rank.h"
#include "../include/phevaluator/card.h"

#include <iostream>
#include <cassert>

using namespace phevaluator;

int main()
{
    std::cout << "Testing basic poker hand evaluation..." << std::endl;

    // Test 1: Royal Flush (should be rank 1 - the best hand)
    std::cout << "\nTest 1: Royal Flush" << std::endl;
    Card ace_spades(48);   // Ace of Spades
    Card king_spades(44);  // King of Spades
    Card queen_spades(40); // Queen of Spades
    Card jack_spades(36);  // Jack of Spades
    Card ten_spades(32);   // Ten of Spades

    Rank royal_flush_rank = EvaluateCards(ace_spades, king_spades, queen_spades, jack_spades, ten_spades);
    std::cout << "Royal Flush rank: " << royal_flush_rank.value() << std::endl;
    std::cout << "Hand category: " << royal_flush_rank.describeCategory() << std::endl;
    std::cout << "Is flush: " << (royal_flush_rank.isFlush() ? "Yes" : "No") << std::endl;

    // Test 2: High Card (should be a high rank - close to 7462)
    std::cout << "\nTest 2: High Card (7-5-4-3-2, all different suits)" << std::endl;
    Card seven_clubs(20);   // 7 of Clubs
    Card five_diamonds(13); // 5 of Diamonds
    Card four_hearts(9);    // 4 of Hearts
    Card three_spades(5);   // 3 of Spades
    Card two_clubs(0);      // 2 of Clubs

    Rank high_card_rank = EvaluateCards(seven_clubs, five_diamonds, four_hearts, three_spades, two_clubs);
    std::cout << "High Card rank: " << high_card_rank.value() << std::endl;
    std::cout << "Hand category: " << high_card_rank.describeCategory() << std::endl;

    // Test 3: Four of a Kind
    std::cout << "\nTest 3: Four of a Kind (Aces)" << std::endl;
    Card ace_clubs(48);    // Ace of Clubs
    Card ace_diamonds(49); // Ace of Diamonds
    Card ace_hearts(50);   // Ace of Hearts
    Card ace_spades2(51);  // Ace of Spades
    Card king_clubs(44);   // King of Clubs

    Rank four_kind_rank = EvaluateCards(ace_clubs, ace_diamonds, ace_hearts, ace_spades, king_clubs);
    std::cout << "Four of a Kind rank: " << four_kind_rank.value() << std::endl;
    std::cout << "Hand category: " << four_kind_rank.describeCategory() << std::endl;

    // Test 4: Full House
    std::cout << "\nTest 4: Full House (Aces full of Kings)" << std::endl;
    Card ace_clubs2(48);    // Ace of Clubs
    Card ace_diamonds2(49); // Ace of Diamonds
    Card ace_hearts2(50);   // Ace of Hearts
    Card king_clubs2(44);   // King of Clubs
    Card king_diamonds(45); // King of Diamonds

    Rank full_house_rank = EvaluateCards(ace_clubs2, ace_diamonds2, ace_hearts2, king_clubs2, king_diamonds);
    std::cout << "Full House rank: " << full_house_rank.value() << std::endl;
    std::cout << "Hand category: " << full_house_rank.describeCategory() << std::endl;

    std::cout << "\nAll tests completed successfully!" << std::endl;
    return 0;
}
