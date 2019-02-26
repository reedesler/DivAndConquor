#include <cmath>
#include "Pathfinder.hpp"

Pathfinder::Pathfinder(World world) : world(world) {
    maxSteps = 80000;
    defaultCost = 1;
}

void Pathfinder::init(int startX, int startY, int goalX, int goalY) {
    openSet.clear();
    while(!openList.empty()) openList.pop();

    start.x = startX;
    start.y = startY;
    start.lookahead = start.estimate = INFINITY;
    start.cost = defaultCost;

    goal.x = goalX;
    goal.y = goalY;
    goal.lookahead = 0;
    goal.estimate = INFINITY;
    goal.cost = defaultCost;
    insert(goal);

    k_m = 0;

    last = start;
}

void Pathfinder::insert(PF_Tile t) {
    TileSet::iterator cur;
    cur  = openSet.find(t);
    int num;

    if (cur == openSet.end()) {
        num = 1;
        tileData val;
        val.v[0] = val.v[1] = 1;
        openSet[t] = val;
    } else {
        cur->second.v[0]++;
        cur->second.v[1]++; // = cur->second.v[0];
        num = cur->second.v[1];
    }

    calculateKey(t);
    t.num = num;
    openList.push(t);
}

PF_Tile &Pathfinder::calculateKey(PF_Tile &t) const {
    double val = fmin(t.lookahead, t.estimate);

    t.key.first  = val + heuristic(t,start) + k_m;
    t.key.second = val;

    return t;
}

double Pathfinder::heuristic(const PF_Tile &a, const PF_Tile &b) const {
    return eightCondist(a,b) * defaultCost;
}

double Pathfinder::eightCondist(const PF_Tile &a, const PF_Tile &b) const {
    double temp;
    double min = abs(a.x - b.x);
    double max = abs(a.y - b.y);
    if (min > max) {
        temp = min;
        min = max;
        max = temp;
    }
    return ((M_SQRT2-1.0)*min + max);
}
