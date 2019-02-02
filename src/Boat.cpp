//
// Created by Reed on 2019-01-30.
//

#include "Boat.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>

Boat::Boat(float x, float y) : Unit(x, y)
{
}

void Boat::move(TileLocation src, TileLocation dest)
{
    std::vector<TileLocation> path;
}

inline double heuristic(TileLocation src, TileLocation dest)
{
    return std::abs(static_cast<int>(src.x - dest.x)) + std::abs(static_cast<int>(src.y - dest.y));
}

/*
void a_star_search(TileLocation start, TileLocation goal,
                   std::unordered_map<TileLocation, TileLocation> &came_from,
                   std::unordered_map<TileLocation, double> &cost_so_far)
{
    std::priority_queue<TileLocation, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty())
    {
        TileLocation current = frontier.get();

        if (current == goal)
        {
            break;
        }

        for (TileLocation next : graph.neighbors(current))
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
}*/