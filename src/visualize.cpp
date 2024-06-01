#include "include/all_pairs_min_cut.hpp"
#include "include/graph_gen.hpp"
// 0: specific graph, 1: random graph, 2: CG1, 3: CG2, 4: AMO
#define GRAPH_TYPE 1

int main()
{
    Graph g;

    switch (GRAPH_TYPE)
    {
    case 0:
    {
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
        Edge e_v2_t = boost::add_edge(v2, t, g).first;
        capacity[e_v2_t] = 2;
    }
        break;
    case 1:
        g = gen::gen_connected_random(40, 100, 1, 100);
        break;
    case 2:
        g = gen::gen_cg1(20);
        break;
    case 3:
        g = gen::gen_cg2(20);
        break;
    case 4:
        g = gen::gen_amo(20);
        break;
    }

    SeparatorTree st = algo::all_pairs_min_cut(g);
    return 0;
}