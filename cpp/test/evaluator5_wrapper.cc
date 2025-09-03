#include "../include/phevaluator/phevaluator.h"
#include "../include/phevaluator/rank.h"
#include "../include/phevaluator/card.h"

namespace phevaluator
{

    Rank EvaluateCards(const Card &a, const Card &b, const Card &c, const Card &d, const Card &e)
    {
        // Convert Card objects to integer IDs and call the C function
        int rank = evaluate_5cards(static_cast<int>(a), static_cast<int>(b),
                                   static_cast<int>(c), static_cast<int>(d), static_cast<int>(e));
        return Rank(rank);
    }

} // namespace phevaluator
