//
// Created by Reed on 2019-01-30.
//

#include "Boat.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>

typedef struct
{
    uint32_t x;
    uint32_t y;
} GridLocation;

Boat::Boat(float x, float y) : Unit(x, y)
{
}

void Boat::move(uint32_t src_x, uint32_t src_y, uint32_t dest_x, uint32_t dest_y)
{
    std::vector<GridLocation> path;
}

inline double heuristic(GridLocation a, GridLocation b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

template <typename Location, typename Graph>
void a_star_search(Graph graph,
                   Location start,
                   Location goal,
                   std::unordered_map<Location, Location> &came_from,
                   std::unordered_map<Location, double> &cost_so_far)
{
    std::priority_queue<Location, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty())
    {
        Location current = frontier.get();

        if (current == goal)
        {
            break;
        }

        for (Location next : graph.neighbors(current))
        {
            double new_cost = cost_so_far[current] + graph.cost(current, next);
            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
}