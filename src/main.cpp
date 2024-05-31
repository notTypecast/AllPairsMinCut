#include <iostream>
#include <vector>
#include <chrono>
#include "include/benchmark.hpp"

int main()
{
    std::cout << "Random graphs" << std::endl;
    std::cout << "-----------" << std::endl;

    const std::vector<std::pair<int, int>> graph_sizes = {{50, 100}, {100, 200}, {200, 400}};

    /*
    std::cout << "Capacities in [1, 4]" << std::endl;
    std::cout << "-----------------" << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Graph size: " << graph_sizes[i].first << "x" << graph_sizes[i].second << std::endl;
        benchmark::benchmark<std::chrono::milliseconds>(benchmark::get_random, graph_sizes[i], {1, 4});
    }
    std::cout << std::endl;

    std::cout << "Capacities in [1, 1000]" << std::endl;
    std::cout << "-------------------" << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Graph size: " << graph_sizes[i].first << "x" << graph_sizes[i].second << std::endl;
        benchmark::benchmark<std::chrono::milliseconds>(benchmark::get_random, graph_sizes[i], {1, 1000});
    }
    std::cout << std::endl;*/

    std::cout << "CG1 graphs" << std::endl;
    std::cout << "----------" << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Graph size: " << graph_sizes[i].first << "x" << graph_sizes[i].second << std::endl;
        benchmark::benchmark<std::chrono::milliseconds>(benchmark::get_cg1, graph_sizes[i], {-1, -1});
    }
    std::cout << std::endl;

    std::cout << "CG2 graphs" << std::endl;
    std::cout << "----------" << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Graph size: " << graph_sizes[i].first << "x" << graph_sizes[i].second << std::endl;
        benchmark::benchmark<std::chrono::milliseconds>(benchmark::get_cg2, graph_sizes[i], {-1, -1});
    }
    std::cout << std::endl;

    std::cout << "AMO graphs" << std::endl;
    std::cout << "----------" << std::endl;
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "Graph size: " << graph_sizes[i].first << "x" << graph_sizes[i].second << std::endl;
        benchmark::benchmark<std::chrono::milliseconds>(benchmark::get_amo, graph_sizes[i], {-1, -1});
    }
    std::cout << std::endl;

    /*
    Graph g;
    Vertex s, t;
    EdgeCapacityMap capacity = boost::get(boost::edge_capacity, g);
    s = boost::add_vertex(g);
    Vertex v1 = boost::add_vertex(g);
    Vertex v2 = boost::add_vertex(g);
    Vertex v3 = boost::add_vertex(g);
    t = boost::add_vertex(g);

    Edge e_s_v1 = boost::add_edge(s, v1, g).first;
    capacity[e_s_v1] = 9;
    Edge e_s_v2 = boost::add_edge(s, v2, g).first;
    capacity[e_s_v2] = 10;
    Edge e_v1_v2 = boost::add_edge(v1, v2, g).first;
    capacity[e_v1_v2] = 5;
    Edge e_v1_v3 = boost::add_edge(v1, v3, g).first;
    capacity[e_v1_v3] = 3;
    Edge e_v2_v3 = boost::add_edge(v2, v3, g).first;
    capacity[e_v2_v3] = 11;
    Edge e_v3_t = boost::add_edge(v3, t, g).first;
    capacity[e_v3_t] = 4;

    SeparatorTree st = algo::all_pairs_min_cut(g);

    EdgeWeightMap weight_map = boost::get(boost::edge_weight, st);

    STEdgeIterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(st); ei != ei_end; ++ei)
    {
        std::cout << "Edge (" << boost::source(*ei, st) << ", " << boost::target(*ei, st) << "): " << weight_map[*ei].weight << std::endl;
        std::cout << "Min cut: ";
        for (std::unordered_set<Vertex>::iterator it = weight_map[*ei].min_cut.begin(); it != weight_map[*ei].min_cut.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }*/

    return 0;
}