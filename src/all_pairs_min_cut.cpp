#include "include/all_pairs_min_cut.hpp"
#include "include/preflow_push.hpp"

namespace algo
{
SeparatorTree all_pairs_min_cut(Graph &g)
{
    SeparatorTree st;
    EdgeWeightMap weight_map = boost::get(boost::edge_weight, st);

    boost::add_vertex(st);

    for (int p = 1; p < boost::num_vertices(g); ++p)
    {
        Vertex k = locate_next(st, p);
        STEdge e = boost::add_edge(k, p, st).first;

        EdgeCapacityMap capacity = boost::get(boost::edge_capacity, g);
        EdgeFlowMap flow = boost::get(boost::edge_flow, g);
        weight_map[e].weight = algo::preflow_push(g, k, p, capacity, flow);;
        weight_map[e].min_cut = algo::get_min_cut(g, k, capacity, flow);

        boost::add_vertex(st);
    }

    return st;
}

Vertex locate_next(SeparatorTree &st, Vertex p)
{
    EdgeWeightMap weight_map = boost::get(boost::edge_weight, st);

    // Set of vertices v which were incident to a minimum weight edge and were not picked
    std::unordered_set<Vertex> removed;
    // Vertex to start each BFS from, used to keep track of current separator subtree
    Vertex bfs_start = 0;

    bool stop;

    while (true)
    {
        // Perform BFS from bfs_start to find the minimum weight edge in the current separator subtree
        // By skipping vertices in removed, we ensure that removed subtrees are never revisited
        stop = true;

        STEdge min_edge;
        int min_weight = std::numeric_limits<int>::max();

        std::queue<Vertex> q;
        std::unordered_set<Vertex> visited;
        q.push(bfs_start);
        visited.insert(bfs_start);

        while (!q.empty())
        {
            Vertex v = q.front();
            q.pop();

            STOutEdgeEdgeIterator ei, ei_end;
            for (boost::tie(ei, ei_end) = boost::out_edges(v, st); ei != ei_end; ++ei)
            {
                Vertex u = boost::opposite(*ei, v, st);

                // If a vertex is in removed, it was part of a minimum weight edge, so the entire subtree rooted at it can be skipped
                // If a vertex has already been visited, it has already been processed
                if (removed.find(u) != removed.end() || visited.find(u) != visited.end())
                {
                    continue;
                }

                // If a vertex not in removed is found, the current subtree still contains more than one vertex
                stop = false;
                q.push(u);
                visited.insert(u);

                // Keep the edge with the minimum weight (breaking ties by order index)
                if (weight_map[*ei].weight < min_weight || (weight_map[*ei].weight == min_weight && boost::get(boost::edge_index, st, *ei) < boost::get(boost::edge_index, st, min_edge)))
                {
                    min_weight = weight_map[*ei].weight;
                    min_edge = *ei;
                }

            }
        }

        if (stop)
        {
            break;
        }

        Vertex source = boost::source(min_edge, st);
        Vertex target = boost::target(min_edge, st);
        // In the minimum cut that corresponds to the minimum weight edge, if p doesn't belong to the same set as the source, we keep the target's subtree
        if (weight_map[min_edge].min_cut.find(p) == weight_map[min_edge].min_cut.end() ^ weight_map[min_edge].min_cut.find(source) == weight_map[min_edge].min_cut.end())
        {
            removed.insert(boost::source(min_edge, st));
            bfs_start = boost::target(min_edge, st);
        }
        // Else, we keep the source's subtree
        else
        {
            removed.insert(boost::target(min_edge, st));
            bfs_start = boost::source(min_edge, st);
        }
    }

    return bfs_start;
}

}