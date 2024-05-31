#include "include/benchmark.hpp"

namespace benchmark
{
void get_random(const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range, Graph &g)
{
    g = gen::gen_connected_random(graph_size.first, graph_size.second, cap_range.first, cap_range.second);
}

void get_cg1(const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range, Graph &g) { g = gen::gen_cg1(graph_size.first); }

void get_cg2(const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range, Graph &g) { g = gen::gen_cg2(graph_size.first); }

void get_amo(const std::pair<int, int> &graph_size, const std::pair<int, int> &cap_range, Graph &g) { g = gen::gen_amo(graph_size.first); }
} // namespace benchmark