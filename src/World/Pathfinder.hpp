#ifndef DIVCONQ_PATHFINDER_HPP
#define DIVCONQ_PATHFINDER_HPP


#include "World.hpp"
#include <unordered_map>
#include <queue>

#define eps (10e-10)

class PF_Tile {
public:
    int x, y;
    double estimate, lookahead;
    double cost;
    int num;

    std::pair<double,double> key;

    bool operator == (const PF_Tile &t) const {
        return ((x == t.x) && (y == t.y));
    }

    bool operator != (const PF_Tile &t) const {
        return ((x != t.x) || (y != t.y));
    }

    bool operator > (const PF_Tile &t) const {
        if (key.first - eps > t.key.first) return true;
        else if (key.first < t.key.first - eps) return false;
        return key.second > t.key.second;
    }

    bool operator <= (const PF_Tile &t) const {
        if (key.first < t.key.first) return true;
        else if (key.first > t.key.first) return false;
        return key.second < t.key.second + eps;
    }

    bool operator < (const PF_Tile &t) const {
        if (key.first + eps < t.key.first) return true;
        else if (key.first - eps > t.key.first) return false;
        return key.second < t.key.second;
    }
};

//typedef __gnu_cxx::hash_map<state, ivec2, state_hash, equal_to<state> > ds_oh;
//typedef __gnu_cxx::priority_queue<state, vector<state>, greater<state> > ds_pq;

class TileHash {
public:
    size_t operator()(const PF_Tile &t) const {
        return t.x + 34245 * t.y;
    }
};

struct tileData {
    int v[2];
};

typedef std::unordered_map<PF_Tile, tileData, TileHash> TileSet;
typedef std::priority_queue<PF_Tile, std::vector<PF_Tile>, std::greater<PF_Tile> > TileQueue;

class Pathfinder {
public:
    explicit Pathfinder(World world);
    void init(int startX, int startY, int goalX, int goalY);
private:
    World world;
    int maxSteps;
    double defaultCost;

    PF_Tile start, goal, last;
    double k_m;

    TileSet openSet;
    TileQueue openList;
    void insert(PF_Tile t);

    PF_Tile& calculateKey(PF_Tile& t) const;

    double heuristic(const PF_Tile &a, const PF_Tile &b) const;
    double eightCondist(const PF_Tile &a, const PF_Tile &b) const;
};


#endif //DIVCONQ_PATHFINDER_HPP
