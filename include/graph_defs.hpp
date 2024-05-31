#ifndef GRAPH_DEFS_HPP
#define GRAPH_DEFS_HPP

#include <unordered_set>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/one_bit_color_map.hpp>
#include <boost/graph/properties.hpp>

// Network definitions
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, boost::no_property>::vertex_descriptor
    Vertex; // forward declare for use in Flow struct

struct Flow
{
    int value;
    Vertex from;
};

typedef boost::property<boost::edge_capacity_t, int, boost::property<boost::edge_flow_t, Flow>> EdgeCapacityProperty;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeCapacityProperty> Graph;

typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIterator;

typedef boost::property_map<Graph, boost::edge_capacity_t>::type EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_capacity_t>::const_type ConstEdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_flow_t>::type EdgeFlowMap;

// Separator tree definitions
struct STEdgeData
{
    int weight;
    std::unordered_set<Vertex> min_cut;
};

typedef boost::property<boost::edge_weight_t, STEdgeData, boost::property<boost::edge_index_t, int>> STEdgeProperty;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, STEdgeProperty> SeparatorTree;

typedef boost::graph_traits<SeparatorTree>::edge_descriptor STEdge;

typedef boost::graph_traits<SeparatorTree>::edge_iterator STEdgeIterator;
typedef boost::graph_traits<SeparatorTree>::out_edge_iterator STOutEdgeEdgeIterator;

typedef boost::property_map<SeparatorTree, boost::edge_weight_t>::type EdgeWeightMap;

#endif // GRAPH_DEFS_HPP