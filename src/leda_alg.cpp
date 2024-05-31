#include "include/leda_alg.hpp"
#include <iostream>

namespace leda_alg
{
void boost_to_leda(const Graph &g, leda::graph &leda_g, leda::edge_array<int> &leda_capacity)
{
    // Map to store the mapping between Boost and LEDA vertices
    // Required to create LEDA edges based on Boost edges
    std::unordered_map<Vertex, leda::node> vertex_boost_to_leda;

    // For each Boost vertex, create a corresponding LEDA node
    VertexIterator vi, vi_end;
    for (boost::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi)
    {
        leda::node leda_v = leda_g.new_node();
        vertex_boost_to_leda[*vi] = leda_v;
    }

    ConstEdgeCapacityMap capacity_map = boost::get(boost::edge_capacity, g);
    // For each leda edge created, store its capacity
    // Required because leda_capacity array must be initialized with the graph after all edges are created
    std::vector<std::pair<leda::edge, int>> leda_edge_capacity;

    // For each Boost edge, create a corresponding LEDA edge
    EdgeIterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei)
    {
        leda::edge leda_e = leda_g.new_edge(vertex_boost_to_leda[boost::source(*ei, g)], vertex_boost_to_leda[boost::target(*ei, g)]);
        leda_edge_capacity.push_back(std::make_pair(leda_e, capacity_map[*ei]));
        leda::edge leda_e_rev = leda_g.new_edge(vertex_boost_to_leda[boost::target(*ei, g)], vertex_boost_to_leda[boost::source(*ei, g)]);
        leda_edge_capacity.push_back(std::make_pair(leda_e_rev, capacity_map[*ei]));
    }

    // Initialize the LEDA edge array with the LEDA graph
    // This makes the array valid for all current edges of the graph
    leda_capacity.init(leda_g);

    // For each LEDA edge, set its capacity in the array
    for (int i = 0; i < leda_edge_capacity.size(); ++i)
    {
        leda_capacity[leda_edge_capacity[i].first] = leda_edge_capacity[i].second;
    }
}
}