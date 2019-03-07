/* Dstar.h
 * James Neufeld (neufeld@cs.ualberta.ca)
 */

#undef near
#ifndef DIVCONQ_PATHFINDING_H
#define DIVCONQ_PATHFINDING_H
#ifndef DIVCONQ_PATHFINDING_H_DEFINED
    #define DIVCONQ_PATHFINDING_H_DEFINED
    class Pathfinder;

    class PF_Tile;

#include <list>
typedef struct{
    std::list<PF_Tile> path;
    double cost;

    void clear(){
        path.clear();
        cost = 0.0;
    }

} Path;
#endif

#include <math.h>
#include <stack>
#include <queue>
#include <ext/hash_map>
#include "World.hpp"

#define eps (10e-10)

using namespace std;
using namespace __gnu_cxx;

class PF_Tile {

public:
    int x;
    int y;
    pair<double,double> key;
    int num;

    bool operator == (const PF_Tile &s2) const {
        return ((x == s2.x) && (y == s2.y));
    }

    bool operator != (const PF_Tile &s2) const {
        return ((x != s2.x) || (y != s2.y));
    }

    bool operator > (const PF_Tile &s2) const {
        if (key.first-eps > s2.key.first) return true;
        else if (key.first < s2.key.first-eps) return false;
        return key.second > s2.key.second;
    }

    bool operator <= (const PF_Tile &s2) const {
        if (key.first < s2.key.first) return true;
        else if (key.first > s2.key.first) return false;
        return key.second < s2.key.second + eps;
    }


    bool operator < (const PF_Tile &s2) const {
        if (key.first + eps < s2.key.first) return true;
        else if (key.first - eps > s2.key.first) return false;
        return key.second < s2.key.second;
    }

};

struct ipoint2 {
    int x,y;
};

struct ivec2 {
    int v[2];
};



struct cellInfo {

    double g;
    double rhs;
    double cost;


};

class PF_TileHash {
public:
    size_t operator()(const PF_Tile &s) const {
        return s.x + 34245*s.y;
    }
};


typedef hash_map<PF_Tile, cellInfo, PF_TileHash, equal_to<PF_Tile> > CellHash;
typedef hash_map<PF_Tile, ivec2, PF_TileHash, equal_to<PF_Tile> > OpenHash;
typedef priority_queue<PF_Tile, vector<PF_Tile>, greater<PF_Tile> > OpenQueue;

class Pathfinder {
public:
    explicit Pathfinder(World* world);
    void   init(int sX, int sY, int gX, int gY);
    void   updateCell(int x, int y, double val);
    void   updateStart(int x, int y);
    void   updateGoal(int x, int y);
    bool   replan();

    Path &getPath();

private:

    World* world;

    Path path;

    double defaultCost;
    double k_m;
    PF_Tile s_start, s_goal, s_last;
    int maxSteps;

    PF_Tile qstate;

    OpenQueue openList;
    CellHash cellHash;
    OpenHash openHash;

    bool   near(double x, double y) const;
    void   makeNewCell(const PF_Tile &u);
    double getG(const PF_Tile &u) const;
    double getRHS(const PF_Tile &u) const;
    void   setG(const PF_Tile &u, double g);
    void   setRHS(const PF_Tile &u, double rhs);
    double eightCondist(const PF_Tile &a, const PF_Tile &b) const;
    int    computeShortestPath();
    void   updateVertex(PF_Tile &u);
    void   insert(PF_Tile u);
    void   remove(const PF_Tile &u);
    double trueDist(const PF_Tile &a, const PF_Tile &b) const;
    double heuristic(const PF_Tile &a, const PF_Tile &b) const;
    PF_Tile  &calculateKey(PF_Tile &u) const;
    void   getSucc(PF_Tile u, list<PF_Tile> &s) const;
    void   getPred(PF_Tile u, list<PF_Tile> &s) const;
    double cost(const PF_Tile &a, const PF_Tile &b) const;
    bool   occupied(const PF_Tile &u) const;
    bool   queuePop();
    bool   isConsistent(const PF_Tile &u);
};

#endif
