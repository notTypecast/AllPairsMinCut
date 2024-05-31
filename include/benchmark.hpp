#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "include/all_pairs_min_cut.hpp"
#include "include/graph_gen.hpp"

#include "include/leda_alg.hpp"
#define MF_UNDIRECTED
#include <LEDA/graph/templates/max_flow.h>

namespace benchmark
{
namespace params
{
const int iterations = 50;
}

/* Benchmark function
 * Benchmarks All Pairs Min Cut algorithm (Boost) against brute force approach (LEDA)
 * Implemented in header file to allow for template specialization
 * INPUT Parameters:
 * -> get_graph: function to get graph
 * -> graph_size: size of graph
 * -> cap_range: range of edge capacities
 * Returns:
 * -> void
 */
template <typename Duration>
void benchmark(std::function<void(const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range, Graph &g)> get_graph,
               const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range)
{
    Graph g;

    leda::graph leda_g;
    leda::node leda_v;

    double apmc_time = 0.0;
    double leda_bf_time = 0.0;

    std::chrono::high_resolution_clock::time_point start, end;

    for (int i = 0; i < params::iterations; ++i)
    {
        g.clear();
        get_graph(graph_size, cap_range, g);

        start = std::chrono::high_resolution_clock::now();
        algo::all_pairs_min_cut(g);
        end = std::chrono::high_resolution_clock::now();
        apmc_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        leda_g.clear();
        leda::edge_array<int> leda_capacity;
        leda_alg::boost_to_leda(g, leda_g, leda_capacity);

        std::vector<leda::node> leda_nodes(leda_g.number_of_nodes());

        int j = 0;
        forall_nodes(leda_v, leda_g)
        {
            leda_nodes[j++] = leda_v;
        }

        for (j = 0; j < leda_nodes.size(); ++j)
        {
            for (int k = j + 1; k < leda_nodes.size(); ++k)
            {
                start = std::chrono::high_resolution_clock::now();
                leda::edge_array<int> leda_flow(leda_g);
                leda::list<leda::node> leda_min_cut;
                leda::MAX_FLOW_T(leda_g, leda_nodes[j], leda_nodes[k], leda_capacity, leda_flow, leda_min_cut);
                end = std::chrono::high_resolution_clock::now();
                leda_bf_time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }
    }

    std::string unit;
    if (std::is_same<Duration, std::chrono::nanoseconds>::value)
    {
        unit = "ns";
    }
    else if (std::is_same<Duration, std::chrono::microseconds>::value)
    {
        unit = "us";
        apmc_time /= 1000;
        leda_bf_time /= 1000;
    }
    else if (std::is_same<Duration, std::chrono::milliseconds>::value)
    {
        unit = "ms";
        apmc_time /= 1000000;
        leda_bf_time /= 1000000;
    }
    else if (std::is_same<Duration, std::chrono::seconds>::value)
    {
        unit = "s";
        apmc_time /= 1000000000;
        leda_bf_time /= 1000000000;
    }

    std::cout << "Average All Pairs Min Cut Time: " << apmc_time / params::iterations << " " << unit << std::endl;
    std::cout << "Average LEDA Brute Force Time: " << leda_bf_time / params::iterations << " " << unit << std::endl;
}

/* Network getter functions
 * These functions use the graph_gen functions to generate networks
 * Their constant signature allows them to be passed to, and used by, the benchmark function
 */

/* Random network getter
 * Generates a random undirected network with random edge capacities in the specified range
 * INPUT Parameters:
 * -> graph_size: size of network
 * -> cap_range: range of edge capacities
 * -> g: network to be generated
 * Returns:
 * -> void
 */
void get_random(const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range, Graph &g);

/* CG1 network getter
 * Generates a CG1 network with the specified parameter n (graph_size.first)
 * The CG1 network is a worst-case network for the preflow-push algorithm
 * INPUT Parameters:
 * -> graph_size: size of graph; only n = graph_size.first is used; n is half the number of vertices
 * -> cap_range: unused
 * -> g: graph to be generated
 * Returns:
 * -> void
 */
void get_cg1(const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range, Graph &g);

/* CG2 network getter
 * Generates a CG2 network with the specified parameter n (graph_size.first)
 * The CG2 network is a worst-case network for the preflow-push algorithm
 * INPUT Parameters:
 * -> graph_size: size of graph; only n = graph_size.first is used; n is half the number of vertices
 * -> cap_range: unused
 * -> g: graph to be generated
 * Returns:
 * -> void
 */
void get_cg2(const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range, Graph &g);


/* AMO network getter
 * Generates an AMO network with the specified parameter n (graph_size.first)
 * The AMO network is a worst-case network for the preflow-push algorithm
 * INPUT Parameters:
 * -> graph_size: size of graph; n = graph_size.first is used; n is half the number of vertices
 * -> cap_range: unused
 * -> g: graph to be generated
 * Returns:
 * -> void
 */
void get_amo(const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range, Graph &g);
}

#endif // BENCHMARK_HPP