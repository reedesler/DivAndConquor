#ifndef DIVCONQ_CAMERA_HPP
#define DIVCONQ_CAMERA_HPP


#include <Common.hpp>


class Camera {
public:
    explicit Camera(rect viewPort, unsigned int i, unsigned int i1, int i2);
    void update();
    void move(vec2 dir, float zoom);
    mat3 getProjection(int pixelScale);
    bounds getCameraBounds();
    void boundCameraToWorld();
    vec2 viewToWorld(vec2 pos);
    rect viewPort;
    float zoom;
private:
    vec2 pos;
    vec2 vel;
    float zoomVel;
    float actualZoom;
    unsigned int worldWidth, worldHeight;
    int tileSize;
};


#endif //DIVCONQ_CAMERA_HPP
