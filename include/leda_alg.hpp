#ifndef LEDA_ALG_HPP
#define LEDA_ALG_HPP

#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "graph_defs.hpp"

#include <LEDA/graph/graph.h>
#include <LEDA/core/queue.h>

namespace leda_alg
{
/* Boost to LEDA network converter
 * Converts a Boost network to LEDA graph (undirected)
 * INPUT Parameters:
 * -> g: Boost network
 * OUTPUT Parameters:
 * -> leda_g: LEDA network
 * -> leda_capacity: LEDA edge array for capacities
 * Returns:
 * -> void
 */
void boost_to_leda(const Graph &g, leda::graph &leda_g, leda::edge_array<int> &leda_capacity);
}

#endif // LEDA_ALG_HPP