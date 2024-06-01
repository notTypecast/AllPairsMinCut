#include <iostream>
#include <vector>
#include <chrono>
#include "include/benchmark.hpp"

int main()
{
    std::cout << "Random graphs" << std::endl;
    std::cout << "-----------" << std::endl;

    const std::vector<std::pair<int, int>> graph_sizes = {{50, 100}, {100, 200}, {200, 400}};

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
    std::cout << std::endl;

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

    return 0;
}