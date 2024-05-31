#include "include/graph_gen.hpp"

namespace gen
{
const Graph gen_connected_random(int n, int m, int cap_min, int cap_max)
{
    Graph g;
    boost::mt19937 rgen(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

    boost::generate_random_graph(g, n, m, rgen, false);
    boost::make_connected(g);

    EdgeCapacityMap capacity = boost::get(boost::edge_capacity, g);

    EdgeIterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei)
    {
        capacity[*ei] = cap_min + rgen() % (cap_max - cap_min + 1);
    }

    return g;
}

const Graph gen_cg1(int n)
{
    Graph g;
    EdgeCapacityMap capacity = boost::get(boost::edge_capacity, g);
    
    std::vector<Vertex> vertices(2*n);
    vertices[0] = boost::add_vertex(g);

    for (int i = 1; i < 2*n; ++i)
    {
        vertices[i] = boost::add_vertex(g);
        Edge e = boost::add_edge(vertices[i - 1], vertices[i], g).first;
        capacity[e] = i <= n ? i + n - 1 : n;
    }

    for (int i = 0; i < n; ++i)
    {
        Edge e = boost::add_edge(vertices[i], vertices[n], g).first;
        capacity[e] = 1;
    }

    Edge e = boost::add_edge(vertices[n - 1], vertices[2*n - 1], g).first;
    capacity[e] = 1;

    return g;
}

const Graph gen_cg2(int n)
{
    Graph g;
    EdgeCapacityMap capacity = boost::get(boost::edge_capacity, g);

    std::vector<Vertex> vertices(2*n);
    vertices[0] = boost::add_vertex(g);

    for (int i = 1; i < 2*n; ++i)
    {
        vertices[i] = boost::add_vertex(g);
        Edge e = boost::add_edge(vertices[i - 1], vertices[i], g).first;
        if (i < n)
        {
            capacity[e] = 2*n;
        }
        else if (i > n)
        {
            capacity[e] = n;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        Edge e = boost::add_edge(vertices[i], vertices[2*n - 1 - i], g).first;
        capacity[e] = 1;
    }

    return g;
}

const Graph gen_amo(int n)
{
    Graph g;
    EdgeCapacityMap capacity = boost::get(boost::edge_capacity, g);

    std::vector<Vertex> vertices(2*n);
    vertices[0] = boost::add_vertex(g);
    vertices[1] = boost::add_vertex(g);

    for (int i = 2; i < 2*n; ++i)
    {
        vertices[i] = boost::add_vertex(g);
        Edge e = boost::add_edge(vertices[i - 1], vertices[i], g).first;
        capacity[e] = 1;
    }

    for (int i = 1; i < 2*n - 1; ++i)
    {
        Edge e = boost::add_edge(vertices[0], vertices[i], g).first;
        capacity[e] = 2; // use a value much smaller than numeric_limits<int>::max() to avoid overflow
    }

    return g;
}
}