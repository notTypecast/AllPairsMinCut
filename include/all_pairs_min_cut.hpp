#ifndef ALL_PAIRS_MIN_CUT_HPP
#define ALL_PAIRS_MIN_CUT_HPP

#include <unordered_set>
#include <unordered_map>
#include <queue>

#include "include/graph_defs.hpp"

namespace algo
{
/* All Pairs Min Cut algorithm
 * Computes the minimum cut between all pairs of vertices in an undirected graph
 * The algorithm constructs a separator tree, which is an undirected graph
 * The separator tree contains n vertices, each representing a vertex in the original graph
 * The tree contains n-1 edges, each representing the minimum cut between the two vertices it connects
 * To find the minimum cut between any two vertices, the path between them in the separator tree is traversed;
 * the minimum cut corresponding to the pair is represented by the edge with the minimum weight on the path
 * The algorithm requires computation of the minimum cut between two vertices; to achieve this, a custom
 * implementation of the Preflow-Push algorithm is used, altered to work with undirected graphs
 * INPUT Parameters:
 * -> g: the undirected graph
 * Returns:
 * -> The separator tree, containing the minimum cut between all pairs of vertices
 *  The tree contains the property map EdgeWeightMap, as defined in graph_defs.hpp
 *  For each edge of the tree, the map contains an instance of STEdgeData, which contains
 *  an integer weight (the flow value of the minimum cut) and an unordered set of vertices
 *  (the vertices belonging to the same set as the source vertex of the minimum cut)
 */
SeparatorTree all_pairs_min_cut(Graph &g);

/* locate(T_{p-1}, p, k) procedure
 * Identifies the vertex k of the current separator tree T_{p-1}, for which the minimum cut k-p must be found
 * in order to construct the next separator tree T_p
 * In this implementation, the separator tree is not copied or modified; instead, a set of removed vertices, as
 * well as a current starting vertex are maintained
 * In each step, BFS is performed from the current starting vertex, and the minimum weight edge is found
 * The removed set is used to skip subtrees that have been removed in previous steps
 * The procedure ends when the current starting vertex is the only one left in the separator tree
 * INPUT Parameters:
 * -> st: the separator tree T_{p-1}
 * -> p: the next vertex to be added to the separator tree
 * Returns:
 * -> The vertex k of the current separator tree T_{p-1} for which the minimum cut k-p must be found
 * Worst Case Complexity: O(n^2); this could be improved to O(nlogn) or even O(n) by using a different approach
 * with an appropriate data structure
 */
Vertex locate_next(SeparatorTree &st, Vertex p);
}

#endif // ALL_PAIRS_MIN_CUT_HPP