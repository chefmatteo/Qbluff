#include "../../include/phevaluator/phevaluator.h"
#include "../../include/phevaluator/rank.h"
#include "../../include/phevaluator/card.h"

namespace phevaluator
{

    Rank EvaluateCards(const Card &a, const Card &b, const Card &c, const Card &d, const Card &e)
    {
        // Convert Card objects to integer IDs and call the C function
        int rank = evaluate_5cards(static_cast<int>(a), static_cast<int>(b),
                                   static_cast<int>(c), static_cast<int>(d), static_cast<int>(e));
        return Rank(rank);
    }

    Rank EvaluateCards(const Card &a, const Card &b, const Card &c, const Card &d, const Card &e, const Card &f)
    {
        // Convert Card objects to integer IDs and call the C function
        int rank = evaluate_6cards(static_cast<int>(a), static_cast<int>(b),
                                   static_cast<int>(c), static_cast<int>(d), static_cast<int>(e), static_cast<int>(f));
        return Rank(rank);
    }

    Rank EvaluateCards(const Card &a, const Card &b, const Card &c, const Card &d, const Card &e, const Card &f, const Card &g)
    {
        // Convert Card objects to integer IDs and call the C function
        int rank = evaluate_7cards(static_cast<int>(a), static_cast<int>(b),
                                   static_cast<int>(c), static_cast<int>(d), static_cast<int>(e), static_cast<int>(f), static_cast<int>(g));
        return Rank(rank);
    }

    Rank EvaluateCards(const Card &a, const Card &b, const Card &c, const Card &d, const Card &e, const Card &f, const Card &g, const Card &h)
    {
        // Convert Card objects to integer IDs and call the C function
        int rank = evaluate_8cards(static_cast<int>(a), static_cast<int>(b),
                                   static_cast<int>(c), static_cast<int>(d), static_cast<int>(e), static_cast<int>(f), static_cast<int>(g), static_cast<int>(h));
        return Rank(rank);
    }

    Rank EvaluateCards(const Card &a, const Card &b, const Card &c, const Card &d, const Card &e, const Card &f, const Card &g, const Card &h, const Card &i)
    {
        // Convert Card objects to integer IDs and call the C function
        int rank = evaluate_9cards(static_cast<int>(a), static_cast<int>(b),
                                   static_cast<int>(c), static_cast<int>(d), static_cast<int>(e), static_cast<int>(f), static_cast<int>(g), static_cast<int>(h), static_cast<int>(i));
        return Rank(rank);
    }

} // namespace phevaluator
