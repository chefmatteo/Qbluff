 #ifndef PHEVALUATOR_H //macro guard to prevent multiple inclusion
 #define PHEVALUATOR_H 
 
 #ifdef __cplusplus
 extern "C" { //written in C language 
 #endif
 
 /*
  * Return an integer indicating the rank of the hand. The strongest hand
  * returns 1, and the weakest hand returns 7462.
  * return 7462 because there are C(52,5) = 2,598,960 possible 5-card poker hands, but after accounting for hand equivalence
  * (i.e., hands with the same rank are considered equal), 
  * there are 7,462 distinct hand ranks. The weakest hand is assigned rank 7,462.
  *
  * Each parameter is a card ID, ranged [0 to 52).
  *
  * The two least significant bits represent the 4 suits, ranged from 0-3.
  *
  * The rest of it represent the 13 ranks, ranged from 0-12.
  *
  * More specifically:
  * deuce = 0, trey = 1, four = 2, five = 3, six = 4, seven = 5, eight = 6,
  * nine = 7, ten = 8, jack = 9, queen = 10, king = 11, ace = 12.
  *
  * So that you can use `rank * 4 + suit` to get the card ID.
  *
  * The complete card Id mapping can be found below. The rows are the ranks
  * from 2 to Ace, and the columns are the suits: club, diamond, heart and
  * spade.
  * 
  * c for club, d for diamond, h for heart, s for spade
  *
  * |   | C | D | H | S |
  * |---|---|---|---|---|
  * | 2 | 0 | 1 | 2 | 3 |
  * | 3 | 4 | 5 | 6 | 7 |
  * | 4 | 8 | 9 | 10| 11|
  * | 5 | 12| 13| 14| 15|
  * | 6 | 16| 17| 18| 19|
  * | 7 | 20| 21| 22| 23|
  * | 8 | 24| 25| 26| 27|
  * | 9 | 28| 29| 30| 31|
  * | T | 32| 33| 34| 35|
  * | J | 36| 37| 38| 39|
  * | Q | 40| 41| 42| 43|
  * | K | 44| 45| 46| 47|
  * | A | 48| 49| 50| 51|
  *
  */


 int evaluate_5cards(int a, int b, int c, int d, int e);
 int evaluate_6cards(int a, int b, int c, int d, int e, int f);
 int evaluate_7cards(int a, int b, int c, int d, int e, int f, int g);
 
 /*
  * The first five parameters are the community cards on the board
  * The last four parameters are the hole cards of the player
  */

  //plo as in community cards and hole cards
 int evaluate_plo4_cards(int c1, int c2, int c3, int c4, int c5, int h1, int h2,
                         int h3, int h4);
 
 /*
  * The first five parameters are the community cards on the board
  * The last four parameters are the hole cards of the player
  * Alias of evaluate_plo4_cards
  */

 int evaluate_omaha_cards(int c1, int c2, int c3, int c4, int c5, int h1, int h2,
                          int h3, int h4);
 
 /*
  * The first five parameters are the community cards on the board
  * The last five parameters are the hole cards of the player
  */
 int evaluate_plo5_cards(int c1, int c2, int c3, int c4, int c5, int h1, int h2,
                         int h3, int h4, int h5);
 
 /*
  * The first five parameters are the community cards on the board
  * The last six parameters are the hole cards of the player
  */
 int evaluate_plo6_cards(int c1, int c2, int c3, int c4, int c5, int h1, int h2,
                         int h3, int h4, int h5, int h6);
 
 #ifdef __cplusplus
 }  // closing brace for extern "C"
 #endif
 
 #ifdef __cplusplus //C++ linkage
 
 #include <phevaluator/card.h>
 #include <phevaluator/rank.h>
 
 namespace phevaluator {
 
 Rank EvaluateCards(const Card& a, const Card& b, const Card& c, const Card& d,
                    const Card& e);
 
 Rank EvaluateCards(const Card& a, const Card& b, const Card& c, const Card& d,
                    const Card& e, const Card& f);
 
 Rank EvaluateCards(const Card& a, const Card& b, const Card& c, const Card& d,
                    const Card& e, const Card& f, const Card& g);
 
 /*
  * The first five parameters are the community cards on the board
  * The last four parameters are the hole cards of the player
  */
 Rank EvaluatePlo4Cards(const Card& c1, const Card& c2, const Card& c3,
                        const Card& c4, const Card& c5, const Card& h1,
                        const Card& h2, const Card& h3, const Card& h4);
 
 /*
  * The first five parameters are the community cards on the board
  * The last four parameters are the hole cards of the player
  * Alias of EvaluatePlo4Cards
  */
 Rank EvaluateOmahaCards(const Card& c1, const Card& c2, const Card& c3,
                         const Card& c4, const Card& c5, const Card& h1,
                         const Card& h2, const Card& h3, const Card& h4);
 
 /*
  * The first five parameters are the community cards on the board
  * The last five parameters are the hole cards of the player
  */
 Rank EvaluatePlo5Cards(const Card& c1, const Card& c2, const Card& c3,
                        const Card& c4, const Card& c5, const Card& h1,
                        const Card& h2, const Card& h3, const Card& h4,
                        const Card& h5);
 
 /*
  * The first five parameters are the community cards on the board
  * The last six parameters are the hole cards of the player
  */
 Rank EvaluatePlo6Cards(const Card& c1, const Card& c2, const Card& c3,
                        const Card& c4, const Card& c5, const Card& h1,
                        const Card& h2, const Card& h3, const Card& h4,
                        const Card& h5, const Card& h6);
 
 }  // namespace phevaluator
 
 #endif  // __cplusplus

 
 #endif  // PHEVALUATOR_H