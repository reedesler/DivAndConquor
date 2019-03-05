#ifndef DIVCONQ_CAMERA_HPP
#define DIVCONQ_CAMERA_HPP


#include <Common.hpp>


class Camera {
public:
    explicit Camera(rect viewPort, unsigned int i, unsigned int i1, int i2);
    void update();
    void move(vec2 dir, float zoom);
    void moveTo(vec2 target);
    mat3 getProjection(int pixelScale);
    bounds getCameraBounds();
    void boundCameraToWorld();
    vec2 viewToWorld(vec2 pos);
    rect viewPort;
    float zoom;
    bool followSelected = false;
private:
    vec2 pos, actualPos;
    vec2 vel;
    float zoomVel;
    float actualZoom;
    unsigned int worldWidth, worldHeight;
    int tileSize;

    bounds getCameraBoundsFor(vec2 vec);

    vec2 boundVecToWorld(vec2 initial);

    void enforceConstraints();
};


#endif //DIVCONQ_CAMERA_HPP
