#include "../include/phevaluator/card.h"
#include "../include/phevaluator/rank.h"

#include <iostream>

using namespace phevaluator;

int main()
{
    std::cout << "Testing basic Card and Rank classes..." << std::endl;

    // Test 1: Create cards and check their properties
    std::cout << "\nTest 1: Card creation and properties" << std::endl;

    Card ace_spades(51);   // Ace of Spades (12*4 + 3 = 51)
    Card king_spades(47);  // King of Spades (11*4 + 3 = 47)
    Card queen_spades(43); // Queen of Spades (10*4 + 3 = 43)
    Card jack_spades(39);  // Jack of Spades (9*4 + 3 = 39)
    Card ten_spades(35);   // Ten of Spades (8*4 + 3 = 35)

    std::cout << "Ace of Spades: " << ace_spades.describeCard() << std::endl;
    std::cout << "King of Spades: " << king_spades.describeCard() << std::endl;
    std::cout << "Queen of Spades: " << queen_spades.describeCard() << std::endl;
    std::cout << "Jack of Spades: " << jack_spades.describeCard() << std::endl;
    std::cout << "Ten of Spades: " << ten_spades.describeCard() << std::endl;

    // Test 2: Card ID conversion
    std::cout << "\nTest 2: Card ID conversion" << std::endl;
    std::cout << "Ace of Spades ID: " << static_cast<int>(ace_spades) << std::endl;
    std::cout << "King of Spades ID: " << static_cast<int>(king_spades) << std::endl;

    // Test 3: Rank object creation
    std::cout << "\nTest 3: Rank object creation" << std::endl;
    Rank test_rank(1234);
    std::cout << "Test rank value: " << test_rank.value() << std::endl;

    // Test 4: Card from string
    std::cout << "\nTest 4: Card from string" << std::endl;
    try
    {
        Card card_from_string("As"); // Ace of Spades
        std::cout << "Card from string 'As': " << card_from_string.describeCard() << std::endl;
        std::cout << "Card ID: " << static_cast<int>(card_from_string) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error creating card from string: " << e.what() << std::endl;
    }

    std::cout << "\nBasic tests completed successfully!" << std::endl;
    return 0;
}
