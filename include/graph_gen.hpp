#ifndef GRAPH_GEN_HPP
#define GRAPH_GEN_HPP

#include <chrono>
#include <vector>

#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <boost/graph/make_connected.hpp>

#include "include/graph_defs.hpp"

namespace gen
{
/* Connected Random Network Generator
 * Generates a random connected network with specified number of vertices, and random edge capacities in the specified range
 * The number of edges is at least the specified number, but might be more to ensure connectivity
 * INPUT Parameters:
 * -> n: number of vertices
 * -> m: lower bound on number of edges
 * -> cap_min: minimum edge capacity
 * -> cap_max: maximum edge capacity
 * Returns:
 * -> generated graph
 */
const Graph gen_connected_random(int n, int m, int cap_min, int cap_max);

/* CG1 Generator
 * INPUT Parameters:
 * -> n: half the number of vertices
 * Returns:
 * -> generated graph
 */
const Graph gen_cg1(int n);

/* CG2 Generator
 * INPUT Parameters:
 * -> n: half the number of vertices
 * Returns:
 * -> generated graph
 */
const Graph gen_cg2(int n);

/* AMO Generator
 * INPUT Parameters:
 * -> n: number of vertices
 * Returns:
 * -> generated graph
 */
const Graph gen_amo(int n);
}

#endif // GRAPH_GEN_HPP