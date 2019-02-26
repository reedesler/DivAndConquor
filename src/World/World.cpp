#include "World.hpp"

World::World(rect viewPort) : camera(Camera(viewPort)),
                              tilemap(Tilemap::LoadFromFile(maps_path("map_horizontal.txt"))) {
    gameObjects.push_back(new GameObject(this));
    gameObjects.push_back(new ShipObject(this, {300, 300}));

}

void World::update(float time) {
    camera.update(tilemap.width, tilemap.height, TILE_SIZE);
    for (auto o : gameObjects) {
        o->update();
    }
    pirate.update(time);

//=======
//    cameraPos.x += cameraVel.x / cameraZoom;
//    cameraPos.y += cameraVel.y / cameraZoom;
//    if (cameraZoomVel > 0) {
//        cameraZoom *= cameraZoomVel;
//    } else if (cameraZoomVel < 0) {
//        cameraZoom /= -cameraZoomVel;
//    }
//
//
//>>>>>>> Stashed changes
}

void World::draw(int pixelScale) {
    mat3 projection = camera.getProjection(pixelScale);
    tilemap.draw(projection);
    for (auto o : gameObjects) {
        o->draw(projection);
    }

//    vec2 cameraPos2 = {210, 210};
//    mat3 T1 = { { 1.f, 0.f, 0.f },{ 0.f, 1.f, 0.f },{ -cameraPos2.x, -cameraPos2.y, 1.f } };
//    mat3 S1 = { { 1.f, 0.f, 0.f },{ 0.f, 1.f, 0.f },{ 0.f, 0.f, 1.f } };
//    mat3 camT1 = { { 1.f, 0.f, 0.f },{ 0.f, 1.f, 0.f },{ viewPort.w / 2.f, viewPort.h / 2.f, 1.f } };
//    mat3 newProjection1 = mul(mul(mul(projection_2D, camT1), S1), T1);
    pirate.draw(projection);

}

void World::onClick(int button, int action, float xpos, float ypos) {
    if (action == GLFW_PRESS) {
        vec2 worldCoords = camera.viewToWorld({xpos, ypos});
        for (auto o : gameObjects) {
            bounds b = o->getBounds();
            if (inBounds(b, worldCoords)) {
                if (selectedObject == o)
                    selectedObject = nullptr;
                else{
                    if(selectedObject)
                        selectedObject->setSelected();
                    selectedObject = o;
                }
                o->setSelected();
                return;
            }
        }

        if (selectedObject != nullptr) {
            selectedObject->move(worldCoords);
        }
    }
}

void World::setExplored(vec2 pos, float radius) {
    tilemap.setExplored(pos, radius);
}
void World::onClick2(int button, int action, float xpos, float ypos) {
    if (action == GLFW_PRESS) {
        vec2 worldCoords = camera.viewToWorld({xpos, ypos});
            bounds b = pirate.getBounds();
            if (inBounds(b, worldCoords)) {
                selected = &pirate;
                return;
            }


        if (selected != nullptr) {
            selected->moveToPos(worldCoords);
        }
    }
}

//void World::on_key(int button, int key, int, int action) {
//
//
//    if (action == GLFW_PRESS && key == GLFW_KEY_D) {
//
//        pirate.moveRight = true;
//
//
//    } else if (action == GLFW_RELEASE && key == GLFW_KEY_D) {
//
//        pirate.moveRight = false;
//
//    } else if (action == GLFW_PRESS && key == GLFW_KEY_A) {
//
//        pirate.moveLeft = true;
//
//    } else if (action == GLFW_RELEASE && key == GLFW_KEY_A) {
//
//        pirate.moveLeft = false;
//
//    } else if (action == GLFW_PRESS && key == GLFW_KEY_W) {
//
//        pirate.moveUp = true;
//
//    } else if (action == GLFW_RELEASE && key == GLFW_KEY_W) {
//
//        pirate.moveUp = false;
//
//    } else if (action == GLFW_PRESS && key == GLFW_KEY_S) {
//
//        pirate.moveDown = true;
//
//    } else if (action == GLFW_RELEASE && key == GLFW_KEY_S) {
//
//        pirate.moveDown = false;
//
//    }
//}


