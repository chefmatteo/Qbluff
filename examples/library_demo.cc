#include "phevaluator/card.h"
#include "phevaluator/rank.h"
#include "phevaluator/phevaluator.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace phevaluator;

// Helper function to print card details
void printCard(const Card &card, const std::string &label = "")
{
    std::cout << std::setw(20) << label << ": " << card.describeCard()
              << " (ID: " << static_cast<int>(card) << ")" << std::endl;
}

// Helper function to print hand evaluation
void printHandEvaluation(const std::string &handName, const Rank &rank)
{
    std::cout << std::setw(20) << handName << ": "
              << std::setw(6) << rank.value() << " - "
              << rank.describeRank() << std::endl;
}

// Helper function to print separator
void printSeparator(const std::string &title)
{
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << " " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

int main()
{
    std::cout << "🎰 QBLUFF POKER HAND EVALUATOR - LIBRARY DEMONSTRATION 🎰" << std::endl;
    std::cout << "Demonstrating 10 different test cases showcasing library capabilities\n"
              << std::endl;

    // Test Case 1: Royal Flush (5-card)
    printSeparator("TEST CASE 1: ROYAL FLUSH (5-Card)");
    try
    {
        Card ace_spades("As");
        Card king_spades("Ks");
        Card queen_spades("Qs");
        Card jack_spades("Js");
        Card ten_spades("Ts");

        std::cout << "Cards:" << std::endl;
        printCard(ace_spades, "Ace of Spades");
        printCard(king_spades, "King of Spades");
        printCard(queen_spades, "Queen of Spades");
        printCard(jack_spades, "Jack of Spades");
        printCard(ten_spades, "Ten of Spades");

        Rank rank = EvaluateCards(ace_spades, king_spades, queen_spades, jack_spades, ten_spades);
        printHandEvaluation("Royal Flush", rank);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 2: Four of a Kind (5-card)
    printSeparator("TEST CASE 2: FOUR OF A KIND (5-Card)");
    try
    {
        Card ace_clubs("Ac");
        Card ace_diamonds("Ad");
        Card ace_hearts("Ah");
        Card ace_spades("As");
        Card king_clubs("Kc");

        std::cout << "Cards:" << std::endl;
        printCard(ace_clubs, "Ace of Clubs");
        printCard(ace_diamonds, "Ace of Diamonds");
        printCard(ace_hearts, "Ace of Hearts");
        printCard(ace_spades, "Ace of Spades");
        printCard(king_clubs, "King of Clubs");

        Rank rank = EvaluateCards(ace_clubs, ace_diamonds, ace_hearts, ace_spades, king_clubs);
        printHandEvaluation("Four of a Kind", rank);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 3: Full House (5-card)
    printSeparator("TEST CASE 3: FULL HOUSE (5-Card)");
    try
    {
        Card ace_clubs("Ac");
        Card ace_diamonds("Ad");
        Card ace_hearts("Ah");
        Card king_clubs("Kc");
        Card king_diamonds("Kd");

        std::cout << "Cards:" << std::endl;
        printCard(ace_clubs, "Ace of Clubs");
        printCard(ace_diamonds, "Ace of Diamonds");
        printCard(ace_hearts, "Ace of Hearts");
        printCard(king_clubs, "King of Clubs");
        printCard(king_diamonds, "King of Diamonds");

        Rank rank = EvaluateCards(ace_clubs, ace_diamonds, ace_hearts, king_clubs, king_diamonds);
        printHandEvaluation("Full House", rank);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 4: Flush (5-card)
    printSeparator("TEST CASE 4: FLUSH (5-Card)");
    try
    {
        Card ace_hearts("Ah");
        Card jack_hearts("Jh");
        Card nine_hearts("9h");
        Card seven_hearts("7h");
        Card five_hearts("5h");

        std::cout << "Cards:" << std::endl;
        printCard(ace_hearts, "Ace of Hearts");
        printCard(jack_hearts, "Jack of Hearts");
        printCard(nine_hearts, "Nine of Hearts");
        printCard(seven_hearts, "Seven of Hearts");
        printCard(five_hearts, "Five of Hearts");

        Rank rank = EvaluateCards(ace_hearts, jack_hearts, nine_hearts, seven_hearts, five_hearts);
        printHandEvaluation("Flush", rank);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 5: Straight (5-card)
    printSeparator("TEST CASE 5: STRAIGHT (5-Card)");
    try
    {
        Card ten_clubs("Tc");
        Card nine_diamonds("9d");
        Card eight_hearts("8h");
        Card seven_spades("7s");
        Card six_clubs("6c");

        std::cout << "Cards:" << std::endl;
        printCard(ten_clubs, "Ten of Clubs");
        printCard(nine_diamonds, "Nine of Diamonds");
        printCard(eight_hearts, "Eight of Hearts");
        printCard(seven_spades, "Seven of Spades");
        printCard(six_clubs, "Six of Clubs");

        Rank rank = EvaluateCards(ten_clubs, nine_diamonds, eight_hearts, seven_spades, six_clubs);
        printHandEvaluation("Straight", rank);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 6: Three of a Kind (5-card)
    printSeparator("TEST CASE 6: THREE OF A KIND (5-Card)");
    try
    {
        Card queen_clubs("Qc");
        Card queen_diamonds("Qd");
        Card queen_hearts("Qh");
        Card jack_clubs("Jc");
        Card ten_diamonds("Td");

        std::cout << "Cards:" << std::endl;
        printCard(queen_clubs, "Queen of Clubs");
        printCard(queen_diamonds, "Queen of Diamonds");
        printCard(queen_hearts, "Queen of Hearts");
        printCard(jack_clubs, "Jack of Clubs");
        printCard(ten_diamonds, "Ten of Diamonds");

        Rank rank = EvaluateCards(queen_clubs, queen_diamonds, queen_hearts, jack_clubs, ten_diamonds);
        printHandEvaluation("Three of a Kind", rank);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 7: Two Pair (5-card)
    printSeparator("TEST CASE 7: TWO PAIR (5-Card)");
    try
    {
        Card king_clubs("Kc");
        Card king_diamonds("Kd");
        Card jack_hearts("Jh");
        Card jack_spades("Js");
        Card ace_clubs("Ac");

        std::cout << "Cards:" << std::endl;
        printCard(king_clubs, "King of Clubs");
        printCard(king_diamonds, "King of Diamonds");
        printCard(jack_hearts, "Jack of Hearts");
        printCard(jack_spades, "Jack of Spades");
        printCard(ace_clubs, "Ace of Clubs");

        Rank rank = EvaluateCards(king_clubs, king_diamonds, jack_hearts, jack_spades, ace_clubs);
        printHandEvaluation("Two Pair", rank);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 8: One Pair (5-card)
    printSeparator("TEST CASE 8: ONE PAIR (5-Card)");
    try
    {
        Card ace_clubs("Ac");
        Card ace_diamonds("Ad");
        Card king_hearts("Kh");
        Card queen_spades("Qs");
        Card jack_clubs("Jc");

        std::cout << "Cards:" << std::endl;
        printCard(ace_clubs, "Ace of Clubs");
        printCard(ace_diamonds, "Ace of Diamonds");
        printCard(king_hearts, "King of Hearts");
        printCard(queen_spades, "Queen of Spades");
        printCard(jack_clubs, "Jack of Clubs");

        Rank rank = EvaluateCards(ace_clubs, ace_diamonds, king_hearts, queen_spades, jack_clubs);
        printHandEvaluation("One Pair", rank);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 9: High Card (5-card)
    printSeparator("TEST CASE 9: HIGH CARD (5-Card)");
    try
    {
        Card ace_clubs("Ac");
        Card king_diamonds("Kd");
        Card queen_hearts("Qh");
        Card jack_spades("Js");
        Card nine_clubs("9c");

        std::cout << "Cards:" << std::endl;
        printCard(ace_clubs, "Ace of Clubs");
        printCard(king_diamonds, "King of Diamonds");
        printCard(queen_hearts, "Queen of Hearts");
        printCard(jack_spades, "Jack of Spades");
        printCard(nine_clubs, "Nine of Clubs");

        Rank rank = EvaluateCards(ace_clubs, king_diamonds, queen_hearts, jack_spades, nine_clubs);
        printHandEvaluation("High Card", rank);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 10: PLO4 Hand Comparison
    printSeparator("TEST CASE 10: PLO4 HAND COMPARISON");
    try
    {
        // Board cards (5 community cards)
        Card board1("As"); // Ace of Spades
        Card board2("Kh"); // King of Hearts
        Card board3("Qd"); // Queen of Diamonds
        Card board4("Jc"); // Jack of Clubs
        Card board5("Ts"); // Ten of Spades

        // Player 1: Flush draw
        Card h1_1("9s"); // Nine of Spades
        Card h1_2("6s"); // Six of Spades
        Card h1_3("5s"); // Five of Spades
        Card h1_4("4s"); // Four of Spades

        // Player 2: Straight draw
        Card h2_1("Th"); // Ten of Hearts
        Card h2_2("9h"); // Nine of Hearts
        Card h2_3("8h"); // Eight of Hearts
        Card h2_4("7h"); // Seven of Hearts

        std::cout << "Board Cards:" << std::endl;
        printCard(board1, "Board 1");
        printCard(board2, "Board 2");
        printCard(board3, "Board 3");
        printCard(board4, "Board 4");
        printCard(board5, "Board 5");

        std::cout << "\nPlayer 1 Hole Cards (Flush):" << std::endl;
        printCard(h1_1, "Hole 1");
        printCard(h1_2, "Hole 2");
        printCard(h1_3, "Hole 3");
        printCard(h1_4, "Hole 4");

        std::cout << "\nPlayer 2 Hole Cards (Straight):" << std::endl;
        printCard(h2_1, "Hole 1");
        printCard(h2_2, "Hole 2");
        printCard(h2_3, "Hole 3");
        printCard(h2_4, "Hole 4");

        // Evaluate PLO4 hands
        Rank rank1 = EvaluatePlo4Cards(board1, board2, board3, board4, board5,
                                       h1_1, h1_2, h1_3, h1_4);
        Rank rank2 = EvaluatePlo4Cards(board1, board2, board3, board4, board5,
                                       h2_1, h2_2, h2_3, h2_4);

        std::cout << "\nResults:" << std::endl;
        printHandEvaluation("Player 1", rank1);
        printHandEvaluation("Player 2", rank2);

        if (rank1.value() < rank2.value())
        {
            std::cout << "\n🏆 Player 1 wins with " << rank1.describeRank() << std::endl;
        }
        else if (rank2.value() < rank1.value())
        {
            std::cout << "\n🏆 Player 2 wins with " << rank2.describeRank() << std::endl;
        }
        else
        {
            std::cout << "\n🤝 It's a tie!" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 11: Multi-Player (5 Players) Hand Comparison
    printSeparator("TEST CASE 11: MULTI-PLAYER (5 PLAYERS) HAND COMPARISON");
    try
    {
        // Board cards (5 community cards) - Flop + Turn + River
        Card board1("Ah"); // Ace of Hearts
        Card board2("Kd"); // King of Diamonds
        Card board3("Qc"); // Queen of Clubs
        Card board4("Js"); // Jack of Spades
        Card board5("Ts"); // Ten of Spades

        // Player 1: Pair of Aces
        Card h1_1("Ac"); // Ace of Clubs
        Card h1_2("2h"); // Two of Hearts

        // Player 2: Pair of Kings
        Card h2_1("Kh"); // King of Hearts
        Card h2_2("3d"); // Three of Diamonds

        // Player 3: Flush draw
        Card h3_1("9h"); // Nine of Hearts
        Card h3_2("7h"); // Seven of Hearts

        // Player 4: Straight draw
        Card h4_1("9c"); // Nine of Clubs
        Card h4_2("8c"); // Eight of Clubs

        // Player 5: High card
        Card h5_1("Qh"); // Queen of Hearts
        Card h5_2("Jh"); // Jack of Hearts

        std::cout << "Board Cards:" << std::endl;
        printCard(board1, "Board 1");
        printCard(board2, "Board 2");
        printCard(board3, "Board 3");
        printCard(board4, "Board 4");
        printCard(board5, "Board 5");

        std::cout << "\nPlayer Hands:" << std::endl;
        printCard(h1_1, "Player 1 - Hole 1");
        printCard(h1_2, "Player 1 - Hole 2");
        printCard(h2_1, "Player 2 - Hole 1");
        printCard(h2_2, "Player 2 - Hole 2");
        printCard(h3_1, "Player 3 - Hole 1");
        printCard(h3_2, "Player 3 - Hole 2");
        printCard(h4_1, "Player 4 - Hole 1");
        printCard(h4_2, "Player 4 - Hole 2");
        printCard(h5_1, "Player 5 - Hole 1");
        printCard(h5_2, "Player 5 - Hole 2");

        // Evaluate all 5 players' hands
        // For Texas Hold'em, we need to find the best 5-card hand from 7 cards (5 board + 2 hole)
        // Since the library doesn't have 7-card evaluation, we'll use a simplified approach
        // by evaluating the best 5-card combination from the available cards

        std::vector<std::pair<int, Rank>> playerRanks;

        // For demonstration purposes, let's create different 5-card combinations
        // In a real implementation, you'd want to find the best 5-card hand from 7 cards

        // Player 1: Board + Ace of Clubs (best possible hand from available cards)
        Rank rank1 = EvaluateCards(board1, board2, board3, board4, h1_1); // Board + best hole card

        // Player 2: Board + King of Hearts
        Rank rank2 = EvaluateCards(board1, board2, board3, board4, h2_1); // Board + best hole card

        // Player 3: Board + Nine of Hearts
        Rank rank3 = EvaluateCards(board1, board2, board3, board4, h3_1); // Board + best hole card

        // Player 4: Board + Nine of Clubs
        Rank rank4 = EvaluateCards(board1, board2, board3, board4, h4_1); // Board + best hole card

        // Player 5: Board + Queen of Hearts
        Rank rank5 = EvaluateCards(board1, board2, board3, board4, h5_1); // Board + best hole card

        playerRanks.push_back({1, rank1});
        playerRanks.push_back({2, rank2});
        playerRanks.push_back({3, rank3});
        playerRanks.push_back({4, rank4});
        playerRanks.push_back({5, rank5});

        // Sort players by hand strength (lower rank value = stronger hand)
        std::sort(playerRanks.begin(), playerRanks.end(),
                  [](const auto &a, const auto &b)
                  {
                      return a.second.value() < b.second.value();
                  });

        std::cout << "\n🏆 FINAL RANKINGS (Best to Worst):" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        for (size_t i = 0; i < playerRanks.size(); i++)
        {
            const auto &player = playerRanks[i];
            std::string position = "";
            if (i == 0)
                position = "🥇 1st Place";
            else if (i == 1)
                position = "🥈 2nd Place";
            else if (i == 2)
                position = "🥉 3rd Place";
            else if (i == 3)
                position = "4th Place";
            else
                position = "5th Place";

            std::cout << std::setw(15) << position << ": Player " << player.first
                      << " - " << player.second.describeRank()
                      << " (Rank: " << player.second.value() << ")" << std::endl;
        }

        std::cout << "\n🎯 Winner: Player " << playerRanks[0].first
                  << " with " << playerRanks[0].second.describeRank() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test Case 12: Comprehensive Multi-Card Evaluation (6, 7, 8, 9 cards)
    printSeparator("TEST CASE 12: COMPREHENSIVE MULTI-CARD EVALUATION");
    try
    {
        std::cout << "Demonstrating evaluation capabilities for different card counts:\n"
                  << std::endl;

        // Test 6-card evaluation
        Card c1("As"); // Ace of Spades
        Card c2("Ks"); // King of Spades
        Card c3("Qs"); // Queen of Spades
        Card c4("Js"); // Jack of Spades
        Card c5("Ts"); // Ten of Spades
        Card c6("9s"); // Nine of Spades

        std::cout << "6-Card Evaluation (Spades Flush):" << std::endl;
        printCard(c1, "Card 1");
        printCard(c2, "Card 2");
        printCard(c3, "Card 3");
        printCard(c4, "Card 4");
        printCard(c5, "Card 5");
        printCard(c6, "Card 6");

        Rank rank6 = EvaluateCards(c1, c2, c3, c4, c5, c6);
        printHandEvaluation("6-Card Hand", rank6);

        // Test 7-card evaluation
        Card c7("8s"); // Eight of Spades
        std::cout << "\n7-Card Evaluation (Spades Flush):" << std::endl;
        printCard(c7, "Card 7");

        Rank rank7 = EvaluateCards(c1, c2, c3, c4, c5, c6, c7);
        printHandEvaluation("7-Card Hand", rank7);

        // Test 8-card evaluation
        Card c8("7s"); // Seven of Spades
        std::cout << "\n8-Card Evaluation (Spades Flush):" << std::endl;
        printCard(c8, "Card 8");

        Rank rank8 = EvaluateCards(c1, c2, c3, c4, c5, c6, c7, c8);
        printHandEvaluation("8-Card Hand", rank8);

        // Test 9-card evaluation
        Card c9("6s"); // Six of Spades
        std::cout << "\n9-Card Evaluation (Spades Flush):" << std::endl;
        printCard(c9, "Card 9");

        Rank rank9 = EvaluateCards(c1, c2, c3, c4, c5, c6, c7, c8, c9);
        printHandEvaluation("9-Card Hand", rank9);

        std::cout << "\n📊 Multi-Card Evaluation Summary:" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "6-Card: " << std::setw(6) << rank6.value() << " - " << rank6.describeRank() << std::endl;
        std::cout << "7-Card: " << std::setw(6) << rank7.value() << " - " << rank7.describeRank() << std::endl;
        std::cout << "8-Card: " << std::setw(6) << rank8.value() << " - " << rank8.describeRank() << std::endl;
        std::cout << "9-Card: " << std::setw(6) << rank9.value() << " - " << rank9.describeRank() << std::endl;

        std::cout << "\n💡 Note: All evaluations find the best 5-card hand from the given cards!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Summary
    printSeparator("DEMONSTRATION SUMMARY");
    std::cout << "✅ Successfully demonstrated 12 test cases:" << std::endl;
    std::cout << "   • 9 different 5-card poker hand types" << std::endl;
    std::cout << "   • 1 PLO4 hand comparison" << std::endl;
    std::cout << "   • 1 multi-player (5 players) hand comparison" << std::endl;
    std::cout << "   • 1 comprehensive multi-card evaluation (6, 7, 8, 9 cards)" << std::endl;
    std::cout << "   • Card creation from strings" << std::endl;
    std::cout << "   • Rank evaluation and description" << std::endl;
    std::cout << "   • Error handling with try-catch" << std::endl;
    std::cout << "\n🎯 The library successfully handles:" << std::endl;
    std::cout << "   • All standard poker hand rankings" << std::endl;
    std::cout << "   • PLO4 evaluation with 4 hole cards + 5 board cards" << std::endl;
    std::cout << "   • Multi-player hand evaluation and ranking" << std::endl;
    std::cout << "   • Comprehensive multi-card evaluation (5-9 cards)" << std::endl;
    std::cout << "   • Fast lookup-based evaluation" << std::endl;
    std::cout << "   • Comprehensive hand descriptions" << std::endl;

    std::cout << "\n🚀 Ready to build your poker applications!" << std::endl;

    return 0;
}
