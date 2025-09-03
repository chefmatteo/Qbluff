#include <phevaluator/phevaluator.h>

#include "hash.h"
extern "C"
{
#include "../../database/tables/tables.h"
}
namespace phevaluator
{

    Rank EvaluateCards(const Card &a, const Card &b, const Card &c, const Card &d,
                       const Card &e, const Card &f, const Card &g)
    {
        return evaluate_7cards(a, b, c, d, e, f, g);
    }

} // namespace phevaluator