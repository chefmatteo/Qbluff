// this file is used to evaluate the 6-card poker hand
#include "../include/phevaluator/phevaluator.h"
#include "../include/phevaluator/rank.h"

#include "hash.h"
extern "C"
{
#include "../../database/tables/tables.h"
}

namespace phevaluator
{

    Rank EvaluateCards(const Card &a, const Card &b, const Card &c, const Card &d,
                       const Card &e, const Card &f)
    {
        return evaluate_6cards(a, b, c, d, e, f);
    }

} // namespace phevaluator