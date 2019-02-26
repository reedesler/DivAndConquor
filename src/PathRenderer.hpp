#ifndef DIVCONQ_PATH_HPP
#define DIVCONQ_PATH_HPP

#include <World/Pathfinder.hpp>
#include "Common.hpp"

class PathRenderer : public Renderable {
public:
    bool init(Path path);
    void draw(const mat3 &projection);
};


#endif //DIVCONQ_PATH_HPP
