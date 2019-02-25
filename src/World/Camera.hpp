#ifndef DIVCONQ_CAMERA_HPP
#define DIVCONQ_CAMERA_HPP


#include <Common.hpp>

class Camera {
public:
    explicit Camera(rect viewPort);
    void update(unsigned int width, unsigned int height, int tileSize);
    void move(vec2 dir, int zoom);
    mat3 getProjection(int pixelScale);
    bounds getCameraBounds();
    vec2 viewToWorld(vec2 pos);
    rect viewPort;
private:
    vec2 pos;
    vec2 vel;
    float zoomVel;
    float zoom;
};


#endif //DIVCONQ_CAMERA_HPP
