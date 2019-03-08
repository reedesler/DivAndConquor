#include "World.hpp"

World::World(rect viewPort) : tilemap(Tilemap::LoadFromFile(maps_path("map_horizontal.txt"))),
                                camera(Camera(viewPort, tilemap.width, tilemap.height, TILE_SIZE))
{
    gameObjects.push_back(new ShipObject(this, {300, 300}));
    gameObjects.push_back(new SettlementObject(this, {770, 330}));
    gameObjects.push_back(new Pirate(this, {900, 500}));
    gameObjects.push_back(new Sailor(this, {900, 350}));
    pathRenderer = new PathRenderer();
    w = tilemap.width *  TILE_SIZE;
    h = tilemap.height * TILE_SIZE;

    prevMouseXpos = viewPort.w / 2.f;
    prevMouseYpos = viewPort.h / 2.f;
}

void World::addShip(ShipObject *ship)
{
    this->fleet.insert(ship);
}

void World::centerCameraOn(GameObject &go){
    this->camera.moveTo(go.getPosition());
}
void World::update()
{
    tilemap.clearVisible(visibleTiles);
    visibleTiles.clear();

    camera.update();
    for (auto o : gameObjects)
    {
        o->update();
    }

    tilemap.setExplored(visibleTiles);

    if (selectedObject && selectedObject->pathfinder) {
        pathRenderer->init(selectedObject->pathfinder->getPath());
    }


    if(camera.followSelected && getSelected() != nullptr)
        centerCameraOn(*getSelected());
}

void World::draw(int pixelScale)
{
    mat3 projection = camera.getProjection(pixelScale);
    tilemap.draw(projection);
    for (auto o : gameObjects)
    {
        o->draw(projection);
    }
    if (selectedObject && selectedObject->pathfinder) {
        pathRenderer->draw(projection);
    }
}

void World::onClick(int button, int action, float xpos, float ypos)
{
    if (action == GLFW_PRESS)
    {
        vec2 worldCoords = camera.viewToWorld({xpos, ypos});
        for (auto o : gameObjects)
        {
            bounds b = o->getBounds();
            if (inBounds(b, worldCoords))
            {
                //int a = 1;
                if (selectedObject == o)
                    selectedObject = nullptr;
                else
                {
                    if (selectedObject)
                        selectedObject->setSelected();
                    selectedObject = o;

                }
                o->setSelected();
                return;
            }
        }

        if (selectedObject != nullptr)
        {
            selectedObject->move(worldCoords);
        }
    }
}

void World::setExplored(vec2 pos, float radius)
{
    int minX = std::max(static_cast<int>(floor((pos.x - radius) / TILE_SIZE + 0.5f)), 0);
    int maxX = std::min(static_cast<unsigned int>(floor((pos.x + radius) / TILE_SIZE + 0.5f)), tilemap.width - 1);
    int minY = std::max(static_cast<int>(floor((pos.y - radius) / TILE_SIZE + 0.5f)), 0);
    int maxY = std::min(static_cast<unsigned int>(floor((pos.y + radius) / TILE_SIZE + 0.5f)), tilemap.height - 1);

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            if (inRadius(pos, radius, {static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE)}))
            {
                for (auto o : gameObjects) {
                    if (o->pathfinder) {
                        o->pathfinder->updateCell(x, y, tilemap.map[x][y].type == 0);
                    }
                }
                visibleTiles.insert(TilePos{x, y});
            }
        }
    }
}

#define MOUSE_MOVE_SIZE 50

void World::onMouseMove(double xpos, double ypos) {
    if (xpos == -1 && ypos == -1) {
        xpos = camera.viewPort.w / 2.f;
        ypos = camera.viewPort.h / 2.f;
    }
    vec2 cameraDir = {0, 0};
    if (xpos <= MOUSE_MOVE_SIZE && prevMouseXpos > MOUSE_MOVE_SIZE) cameraDir.x -= 1;
    if (prevMouseXpos <= MOUSE_MOVE_SIZE && xpos > MOUSE_MOVE_SIZE) cameraDir.x += 1;

    if (xpos >= camera.viewPort.w - MOUSE_MOVE_SIZE && prevMouseXpos < camera.viewPort.w - MOUSE_MOVE_SIZE) cameraDir.x += 1;
    if (prevMouseXpos >= camera.viewPort.w - MOUSE_MOVE_SIZE && xpos < camera.viewPort.w - MOUSE_MOVE_SIZE) cameraDir.x -= 1;

    if (ypos <= MOUSE_MOVE_SIZE && prevMouseYpos > MOUSE_MOVE_SIZE) cameraDir.y -= 1;
    if (prevMouseYpos <= MOUSE_MOVE_SIZE && ypos > MOUSE_MOVE_SIZE) cameraDir.y += 1;

    if (ypos >= camera.viewPort.h - MOUSE_MOVE_SIZE && prevMouseYpos < camera.viewPort.h - MOUSE_MOVE_SIZE) cameraDir.y += 1;
    if (prevMouseYpos >= camera.viewPort.h - MOUSE_MOVE_SIZE && ypos < camera.viewPort.h - MOUSE_MOVE_SIZE) cameraDir.y -= 1;

    camera.move(cameraDir, 0);

    prevMouseXpos = xpos;
    prevMouseYpos = ypos;
}
