#include "../../include/phevaluator/phevaluator.h"

namespace phevaluator
{

    Rank EvaluatePlo4Cards(const Card &c1, const Card &c2, const Card &c3,
                           const Card &c4, const Card &c5, const Card &h1,
                           const Card &h2, const Card &h3, const Card &h4)
    {
        return evaluate_plo4_cards(c1, c2, c3, c4, c5, h1, h2, h3, h4);
    }

    Rank EvaluateOmahaCards(const Card &c1, const Card &c2, const Card &c3,
                            const Card &c4, const Card &c5, const Card &h1,
                            const Card &h2, const Card &h3, const Card &h4)
    {
        return EvaluatePlo4Cards(c1, c2, c3, c4, c5, h1, h2, h3, h4);
    }

} // namespace phevaluator
