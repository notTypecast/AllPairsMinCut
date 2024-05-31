#ifndef PREFLOW_PUSH_HPP
#define PREFLOW_PUSH_HPP

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <list>

#include "graph_defs.hpp"

namespace algo
{
/* HighestLevelSet class for preflow-push algorithm
 * Used for quick access to the highest level active vertices
 * This is faster than a priority queue, as the number of levels is limited
 */
class HighestLevelSet
{
public:
    HighestLevelSet(int total_max);

    Vertex del();
    void insert(Vertex v, int level);
    void insert0(Vertex v, int level);
    bool empty();

protected:
    int _total_max;
    int _current_max;
    std::vector<std::list<Vertex>> _levels;
};

/* Preflow-Push Algorithm for undirected flow networks
 * Calculates the maximum flow from source s to sink t in a flow network g
 * The implementation is an altered version of the original algorithm, which was designed for directed networks
 * The input graph must be undirected, and no additional (0-capacity) edges need to be added
 * The differences between the original algorithm and this implementation are as follows:
 * 
 * 1. Storing flow consists of storing a value, as well as the vertex from which the flow came
 *  This is done to preserve directional information, which is lost in undirected graphs
 * 2. Every iteration, the residual capacity of an edge (v, u) is calculated as such:
 *  -> r(e) = c(e) - f(e), if the current flow source vertex is v
 *  -> r(e) = c(e) + f(e), if the current flow source vertex is u
 *  As such, flow units that can be sent back are accounted for
 * 3. When updating the flow for the edge (u, v), the flow value is updated as such:
 *  -> f(e) = f(e) + m, if the current flow source vertex is v
 *  -> f(e) = f(e) - m, if the current flow source vertex is u
 *  Where m is the minimum of the calculated residual capacity and the excess flow of v
 *  The latter case can lead to negative flow values; this means that all existing flow was sent back,
 *  and additional flow was sent from u to v; in this case, the flow value is made positive and the flow
 *  source is updated to u
 * 
 * INPUT Parameters:
 * -> g: the flow network
 * -> s: the source vertex
 * -> t: the sink vertex
 * -> capacity: the edge capacity map; must contain the capacity of each edge in the network
 * OUTPUT Parameters:
 * -> flow: the edge flow map; will contain the flow and direction of each edge in the network
 * Returns:
 * -> The maximum flow from source s to sink t
 */
int preflow_push(Graph &g, Vertex s, Vertex t, EdgeCapacityMap &capacity, EdgeFlowMap &flow);

/* get_min_cut function for undirected flow networks
 * Calculates the minimum cut of a flow network g, given the source vertex s and the calculated maximum flow
 * Does this by performing BFS from s in the residual graph
 * Note that the residual graph is calculated on-the-fly, using the flow values
 * Since the graph is undirected, an edge in the graph is only unusable if it's saturated in the correct direction,
 * meaning that the flow source vertex is the current vertex and the flow value is equal to the capacity
 * INPUT Parameters:
 * -> g: the flow network
 * -> s: the source vertex
 * -> capacity: the edge capacity map; must contain the capacity of each edge in the network
 * -> flow: the edge flow map; must contain the maximum flow and flow direction of each edge in the network
 * Returns:
 * -> The set of vertices in the minimum cut; this is the set containing s; the other set is the complement of this set
 */
std::unordered_set<Vertex> get_min_cut(const Graph &g, Vertex s, EdgeCapacityMap &capacity, EdgeFlowMap &flow);
}

#endif // PREFLOW_PUSH_HPP