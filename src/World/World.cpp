#include "World.hpp"

World::World(rect viewPort) : camera(Camera(viewPort)),
                              tilemap(Tilemap::LoadFromFile(maps_path("map_horizontal.txt")))
{
    turtle = new GameObject(this);
    gameObjects.push_back(turtle);
    gameObjects.push_back(new ShipObject(this, {300, 300}));
    pathRenderer = new PathRenderer();
    w = tilemap.width *  TILE_SIZE;
    h = tilemap.height * TILE_SIZE;
    pirate.init();
}

void World::addShip(ShipObject *ship)
{
    this->fleet.insert(ship);
}

void World::update(float time)
{
    tilemap.clearVisible(visibleTiles);
    visibleTiles.clear();

    camera.update(tilemap.width, tilemap.height, TILE_SIZE);
    for (auto o : gameObjects)
    {
        o->update();
    }
    pirate.update(time);

    tilemap.setExplored(visibleTiles);

    pathRenderer->init(turtle->pathfinder->getPath());
}

void World::draw(int pixelScale)
{
    mat3 projection = camera.getProjection(pixelScale);
    tilemap.draw(projection);
    for (auto o : gameObjects)
    {
        o->draw(projection);
    }
    //pirate.draw(projection);
    pathRenderer->draw(projection);
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
            if (selectedObject == turtle) {
                pathRenderer->init(selectedObject->path);
            }
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
                if (tilemap.map[x][y].type != 0) {
                    for (auto o : gameObjects) {
                        o->pathfinder->updateCell(x, y, -1);
                    }
                }
                visibleTiles.insert(TilePos{x, y});
            }
        }
    }
}
