#include "include/preflow_push.hpp"

namespace algo
{
HighestLevelSet::HighestLevelSet(int total_max) : _total_max(total_max), _current_max(-1), _levels(total_max + 1) {}

Vertex HighestLevelSet::del()
{
    while (_current_max >= 0 && _levels[_current_max].empty())
    {
        --_current_max;
    }

    if (_current_max >= 0)
    {
        Vertex v = _levels[_current_max].front();
        _levels[_current_max].pop_front();
        return v;
    }

    return Graph::null_vertex();
}

void HighestLevelSet::insert(Vertex v, int level)
{
    _levels[level].push_front(v);
    _current_max = std::max(_current_max, level);
}

void HighestLevelSet::insert0(Vertex v, int level)
{
    _levels[level].push_back(v);
}

bool HighestLevelSet::empty()
{
    while (_current_max >= 0 && _levels[_current_max].empty())
    {
        --_current_max;
    }

    return _current_max < 0;
}

int preflow_push(Graph &g, Vertex s, Vertex t, EdgeCapacityMap &capacity, EdgeFlowMap &flow)
{
    if (s == t || boost::degree(s, g) == 0 || boost::degree(t, g) == 0)
    {
        return 0;
    }

    const int n = num_vertices(g);
    const int m = num_edges(g);

    std::vector<int> excess(n, 0);
    std::vector<int> height(n, 0);
    HighestLevelSet active(2*n - 1);

    height[s] = n;

    // Initialize flow
    EdgeIterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei)
    {
        flow[*ei].value = 0;
        flow[*ei].from = Graph::null_vertex();
    }

    OutEdgeIterator oei, oei_end;
    // Push initial flow from source
    for (boost::tie(oei, oei_end) = boost::out_edges(s, g); oei != oei_end; ++oei)
    {
        flow[*oei].value = capacity[*oei];
        flow[*oei].from = s;
        excess[s] -= capacity[*oei];
        Vertex v = boost::opposite(*oei, s, g);
        excess[v] += capacity[*oei];
        // Vertex becomes active since it has excess flow
        active.insert(v, height[v]);
    }

    // Main loop
    while (!active.empty())
    {
        Vertex v = active.del();
        if (v == t)
        {
            continue;
        }

        // Push out of v
        // Since the graph is undirected, boost::out_edges returns all edges incident to v
        for (boost::tie(oei, oei_end) = boost::out_edges(v, g); oei != oei_end; ++oei)
        {
            Vertex u = boost::opposite(*oei, v, g);
            // Flow can be pushed if v is higher than u
            if (height[u] < height[v])
            {
                // If the edge flow source is v, r(e) = c(e) - f(e)
                // Else, r(e) = c(e) + f(e), because f(e) can be sent back, and an additional c(e) can be sent
                int residual_capacity = capacity[*oei] + (flow[*oei].from == v ? -1 : 1) * flow[*oei].value;
                if (residual_capacity == 0)
                {
                    continue;
                }

                // Since u gets excess flow, it becomes active if it wasn't already
                if (excess[u] == 0)
                {
                    active.insert0(u, height[u]);
                }
                // Push as much flow as possible (minimum of excess[v] and residual_capacity)
                int to_push = std::min(excess[v], residual_capacity);
                excess[v] -= to_push;
                excess[u] += to_push;
                // If the edge flow source is v, add to_push to flow
                // Else, subtract, because we're pushing in the opposite direction
                flow[*oei].value += (flow[*oei].from == v ? 1 : -1) * to_push;
                // If the edge flow is negative, all existing flow was pushed back, plus more
                // Therefore, change flow source from u to v
                if (flow[*oei].value < 0)
                {
                    flow[*oei].value *= -1;
                    flow[*oei].from = v;
                }
                else if (flow[*oei].from == Graph::null_vertex())
                {
                    flow[*oei].from = v;
                }
            }
        }

        // Relabel v
        if (excess[v] > 0)
        {
            ++height[v];
            active.insert(v, height[v]);
        }
    }

    return excess[t];
}

std::unordered_set<Vertex> get_min_cut(const Graph &g, Vertex s, EdgeCapacityMap &capacity, EdgeFlowMap &flow)
{
    std::queue<Vertex> q;
    std::unordered_set<Vertex> min_cut;
    q.push(s);
    min_cut.insert(s);

    // BFS to find all vertices reachable from s
    while (!q.empty())
    {
        Vertex v = q.front();
        q.pop();

        OutEdgeIterator oei, oei_end;
        for (boost::tie(oei, oei_end) = boost::out_edges(v, g); oei != oei_end; ++oei)
        {
            Vertex u = boost::opposite(*oei, v, g);
            // Edge is usable if it's not saturated by this vertex
            // If the flow source is not v, the edge can always be used
            if (min_cut.find(u) == min_cut.end() && (flow[*oei].from != v || flow[*oei].value < capacity[*oei]))
            {
                q.push(u);
                min_cut.insert(u);
            }
        }
    }

    return min_cut;
}
}