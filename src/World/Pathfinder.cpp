#include "Pathfinder.hpp"

#undef near
Pathfinder::Pathfinder(World* world) : world(world) {
    maxSteps = 40000;
    defaultCost = 1;
}

void Pathfinder::init(int sX, int sY, int gX, int gY) {

    cellHash.clear();
    path.clear();
    openHash.clear();
    while (!openList.empty()) openList.pop();

    k_m = 0;

    cellInfo tmp{};

    for (int x = 0; x < world->tilemap.width; x++) {
        for (int y = 0; y < world->tilemap.height; y++) {
            Tile& t = world->tilemap.map[x][y];
            if (t.explored) {
                PF_Tile tile;
                tile.x = x;
                tile.y = y;

                tmp.rhs = INFINITY;
                tmp.g = INFINITY;

                if (world->selectedObject->landUnit){
                    tmp.cost = (t.type == 2 || t.type == 1) ? defaultCost : -1;

                } else {
                    tmp.cost = t.type == 0 ? defaultCost : -1;

                }

                cellHash[tile] = tmp;
            }
        }
    }

    s_start.x = sX;
    s_start.y = sY;

    s_goal.x = gX;
    s_goal.y = gY;
    setRHS(s_goal, 0);
    insert(s_goal);

    tmp.g = tmp.rhs = INFINITY; //heuristic(s_start,s_goal);
    tmp.cost = defaultCost;
    cellHash[s_start] = tmp;
    calculateKey(s_start);

    s_last = s_start;
}

bool Pathfinder::queuePop() {
    PF_Tile u = openList.top();
    openList.pop();
    OpenHash::iterator cur = openHash.find(u);
    bool b_recent = false;

    if (cur == openHash.end()) {
        fprintf(stderr, "queuePop(): assertion failed\n");
        return false; // should never happen
    }

    cur->second.v[0]--; // remove, decrease # in Q
    if (u.num == cur->second.v[1]) { // u is most recent
        b_recent = true; // equal most recent num?
    }

    if (cur->second.v[0] == 0) openHash.erase(cur); // that was last cell

    return b_recent;

}

Path &Pathfinder::getPath() {
    return path;
}

bool Pathfinder::occupied(const PF_Tile &u) const {

    CellHash::const_iterator cur = cellHash.find(u);

    if (cur == cellHash.end()) return false;
    return (cur->second.cost < 0);
}

void Pathfinder::makeNewCell(const PF_Tile &u) {

    if (cellHash.find(u) != cellHash.end()) return;

    cellInfo tmp{};
    tmp.g = tmp.rhs = INFINITY; //heuristic(u,s_goal);
    tmp.cost = defaultCost;
    cellHash[u] = tmp;

}

double Pathfinder::getG(const PF_Tile &u) const {

    CellHash::const_iterator cur = cellHash.find(u);
    if (cur == cellHash.end())
        return INFINITY; //heuristic(u,s_goal);
    return cur->second.g;
}

double Pathfinder::getRHS(const PF_Tile &u) const {
    CellHash::const_iterator cur = cellHash.find(u);
    if (cur == cellHash.end())
        return INFINITY; //heuristic(u,s_goal);
    return cur->second.rhs;
}

void Pathfinder::setG(const PF_Tile &u, double g) {
    makeNewCell(u);
    cellHash[u].g = g;
}

void Pathfinder::setRHS(const PF_Tile &u, double rhs) {
    makeNewCell(u);
    cellHash[u].rhs = rhs;
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
    return ((M_SQRT2 - 1.0) * min + max);
}

bool Pathfinder::isConsistent(const PF_Tile &u) {
    return (getRHS(u) == getG(u));
}

int Pathfinder::computeShortestPath() {
    list<PF_Tile> s;
    list<PF_Tile>::iterator i;

    if (openList.empty()) return 1;

    int steps = 0;
    while ((!openList.empty()) &&
           (openList.top() < (calculateKey(s_start))) ||
           (!isConsistent(s_start))) {

        if (steps++ > maxSteps) {
            fprintf(stderr, "At maxsteps in computeShortestPath\n");
            return -1;
        }

        PF_Tile u;

        // check consistency (one of the loop conditions)
        bool test = isConsistent(s_start);
        //(getRHS(s_start) != getG(s_start));

        // lazy remove
        while (true) {
            if (openList.empty()) return 1; // checks outer loop condition #1
            u = openList.top();

            if (!queuePop()) continue;

            if (!(u < s_start) && test) return 2; // checks outer loop conditions #2,3 still hold

            break;
        }

        PF_Tile k_old = u;

        if (k_old < calculateKey(u)) { // u is out of date
            insert(u); // u has been removed already, reinsert into pq with new key
        } else if (getG(u) > getRHS(u)) { // needs update (got better)
            setG(u, getRHS(u));
            getPred(u, s);
            for (i = s.begin(); i != s.end(); i++) {
                updateVertex(*i);
            }
        } else {   // g <= rhs, state has got worse
            setG(u, INFINITY);
            getPred(u, s);
            for (i = s.begin(); i != s.end(); i++) {
                updateVertex(*i);
            }
            updateVertex(u);
        }
    }
    return 0;
}

bool Pathfinder::near(double x, double y) const {

    if (isinf(x) && isinf(y)) return true;
    return (fabs(x - y) < eps);

}

void Pathfinder::updateVertex(PF_Tile &u) {
    list<PF_Tile> s;
    list<PF_Tile>::iterator i;

    if (u != s_goal) {
        getSucc(u, s);
        double tmp = INFINITY;
        double tmp2;

        for (i = s.begin(); i != s.end(); i++) {
            tmp2 = getG(*i) + cost(u, *i);
            if (tmp2 < tmp) tmp = tmp2;
        }
        setRHS(u, tmp);
    }

    if (!near(getG(u), getRHS(u))) insert(u);
    else remove(u);

}

void Pathfinder::insert(PF_Tile u) {
    OpenHash::iterator cur;
    cur = openHash.find(u);
    int num;

    if (cur == openHash.end()) {
        num = 1;
        ivec2 val{};
        val.v[0] = val.v[1] = 1;
        openHash[u] = val;
    } else {
        cur->second.v[0]++;
        cur->second.v[1]++; // = cur->second.v[0];
        num = cur->second.v[1];
    }

    calculateKey(u);
    u.num = num;
    openList.push(u);
}

void Pathfinder::remove(const PF_Tile &u) {
    OpenHash::iterator cur = openHash.find(u);
    if (cur == openHash.end()) return;
    else cur->second.v[1]++; // inc most recent flag
}

double Pathfinder::trueDist(const PF_Tile &a, const PF_Tile &b) const {
    float x = a.x - b.x;
    float y = a.y - b.y;
    return sqrt(x * x + y * y);
}

double Pathfinder::heuristic(const PF_Tile &a, const PF_Tile &b) const {
    return eightCondist(a, b) * defaultCost;
}

PF_Tile &Pathfinder::calculateKey(PF_Tile &u) const {

    double val = fmin(getRHS(u), getG(u));

    u.key.first = val + heuristic(u, s_start) + k_m;
    u.key.second = val;

    return u;

}

double Pathfinder::cost(const PF_Tile &a, const PF_Tile &b) const {

    int xd = abs(a.x - b.x);
    int yd = abs(a.y - b.y);
    double scale = 1;

    if (xd + yd > 1) scale = M_SQRT2;

    CellHash::const_iterator cur = cellHash.find(a);
    if (cur == cellHash.end()) return scale * defaultCost;
    if ((cur->second).cost < 0) return INFINITY;
    return scale * (cur->second).cost;
}

void Pathfinder::updateCell(int x, int y, double val) {

    PF_Tile u;

    u.x = x;
    u.y = y;

    if ((u == s_start) || (u == s_goal)) return;

    // if the value is still the same, don't need to do anything
    CellHash::iterator cur = cellHash.find(u);
    if ((cur != cellHash.end()) && (near(cur->second.cost, val))) return;

    makeNewCell(u);
    cellHash[u].cost = val;

    updateVertex(u);
}

void Pathfinder::getSucc(PF_Tile u, list<PF_Tile> &s) const {

    s.clear();
    u.key.first = -1;
    u.key.second = -1;

    PF_Tile v = u;

    if (occupied(u)) return;

    for (int x = -1; x < 2; x++) {
        v.x = u.x + x;
        if (v.x >= 0 && v.x < world->tilemap.width) {
            for (int y = -1; y < 2; y++) {
                v.y = u.y + y;
                if (!(x == 0 && y == 0) && !occupied(v) && v.y >= 0 && v.y < world->tilemap.height) {
                    if (x != 0 && y != 0) {
                        PF_Tile w = v;
                        w.x = u.x;
                        if (occupied(w)) continue;
                        w.x = v.x;
                        w.y = u.y;
                        if (occupied(w)) continue;
                    }
                    s.push_front(v);
                }
            }
        }
    }
}

void Pathfinder::getPred(PF_Tile u, list<PF_Tile> &s) const {

    s.clear();
    u.key.first = -1;
    u.key.second = -1;

    PF_Tile v = u;

    for (int x = -1; x < 2; x++) {
        v.x = u.x + x;
        if (v.x >= 0 && v.x < world->tilemap.width) {
            for (int y = -1; y < 2; y++) {
                v.y = u.y + y;
                if (!(x == 0 && y == 0) && !occupied(v) && v.y >= 0 && v.y < world->tilemap.height) {
                    if (x != 0 && y != 0) {
                        PF_Tile w = v;
                        w.x = u.x;
                        if (occupied(w)) continue;
                        w.x = v.x;
                        w.y = u.y;
                        if (occupied(w)) continue;
                    }
                    s.push_front(v);
                }
            }
        }
    }
}

void Pathfinder::updateStart(int x, int y) {

    s_start.x = x;
    s_start.y = y;

    k_m += heuristic(s_last, s_start);

    CellHash::const_iterator cur = cellHash.find(s_start);
    if (cur == cellHash.end()) {
        setRHS(s_start, INFINITY);
        setG(s_start, INFINITY);
    }

    s_start = calculateKey(s_start);
    s_last = s_start;
}

void Pathfinder::updateGoal(int x, int y) {

    list<pair<ipoint2, double> > toAdd;
    pair<ipoint2, double> tp;

    CellHash::iterator i;
    list<pair<ipoint2, double> >::iterator kk;

    for (i = cellHash.begin(); i != cellHash.end(); i++) {
        if (!near(i->second.cost, defaultCost)) {
            tp.first.x = i->first.x;
            tp.first.y = i->first.y;
            tp.second = i->second.cost;
            toAdd.push_back(tp);
        }
    }

    cellHash.clear();
    openHash.clear();

    while (!openList.empty())
        openList.pop();

    k_m = 0;

    s_goal.x = x;
    s_goal.y = y;

    cellInfo tmp{};
    tmp.g = tmp.rhs = 0;
    tmp.cost = defaultCost;

    cellHash[s_goal] = tmp;
    insert(s_goal);

    tmp.g = tmp.rhs = heuristic(s_start, s_goal);
    tmp.cost = defaultCost;
    cellHash[s_start] = tmp;
    s_start = calculateKey(s_start);

    s_last = s_start;

    for (kk = toAdd.begin(); kk != toAdd.end(); kk++) {
        updateCell(kk->first.x, kk->first.y, kk->second);
    }


}

bool Pathfinder::replan() {

    path.clear();

    int res = computeShortestPath();
    //  printf("res: %d ols: %d ohs: %d tk: [%f %f] sk: [%f %f] sgr: (%f,%f)\n",res,openList.size(),openHash.size(),openList.top().k.first,openList.top().k.second, s_start.k.first, s_start.k.second,getRHS(s_start),getG(s_start));

    if (res < 0) {
        //fprintf(stderr, "NO PATH TO GOAL\n");
        path.cost = INFINITY;
        return false;
    }
    list<PF_Tile> n;
    list<PF_Tile>::iterator i;

    PF_Tile cur = s_start;
    PF_Tile prev = s_start;

    if (isinf(getG(s_start))) {
        //fprintf(stderr, "NO PATH TO GOAL\n");
        path.cost = INFINITY;
        return false;
    }

    // constructs the path
    int steps = 0;
    while (cur != s_goal) {

        if (steps++ > maxSteps) {
            fprintf(stderr, "At maxsteps in replan\n");
            return -1;
        }

        path.path.push_back(cur);
        path.cost += cost(prev, cur);
        getSucc(cur, n);

        if (n.empty()) {
            //fprintf(stderr, "NO PATH TO GOAL\n");
            path.cost = INFINITY;
            return false;
        }

        double cmin = INFINITY;
        double tmin = INFINITY;
        PF_Tile smin = cur;

        for (i = n.begin(); i != n.end(); i++) {

            if (occupied(*i)) continue;
            double val = cost(cur, *i);
            double val2 = trueDist(*i, s_goal) + trueDist(s_start, *i); // (Euclidean) cost to goal + cost to pred
            double val3 = getG(*i);
            val += val3;

            // tiebreak if curent neighbour is equal to current best
            // choose the neighbour that has the smallest tmin value
            if (!isinf(val) && near(val, cmin)) {
                if (val2 < tmin) {
                    tmin = val2;
                    cmin = val;
                    smin = *i;
                }
            }
                // if next neighbour (*i) is scrictly lower cost than the
                // current best, then set it to be the current best.
            else if (val < cmin) {
                tmin = val2;
                cmin = val;
                smin = *i;
            }
        } // end for loop

        n.clear();
        if (isinf(cmin)) break;
        prev = cur;
        cur = smin;
    } // end while loop


    path.path.push_back(s_goal);
    path.cost += cost(prev, s_goal);
    return true;
}
