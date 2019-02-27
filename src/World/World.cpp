#include "World.hpp"

World::World(rect viewPort) : camera(Camera(viewPort)),
                              tilemap(Tilemap::LoadFromFile(maps_path("map_horizontal.txt")))
{
    gameObjects.push_back(new ShipObject(this, {300, 300}));
    gameObjects.push_back(new SettlementObject(this, {770, 330}));
    gameObjects.push_back(new Pirate(this, {900, 500}));

    pathRenderer = new PathRenderer();
    w = tilemap.width *  TILE_SIZE;
    h = tilemap.height * TILE_SIZE;
}

void World::addShip(ShipObject *ship)
{
    this->fleet.insert(ship);
}

void World::update()
{
    tilemap.clearVisible(visibleTiles);
    visibleTiles.clear();

    camera.update(tilemap.width, tilemap.height, TILE_SIZE);
    for (auto o : gameObjects)
    {
        o->update();
    }

    tilemap.setExplored(visibleTiles);

    if (selectedObject && selectedObject->pathfinder) {
        pathRenderer->init(selectedObject->pathfinder->getPath());
    }
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
                int a = 1;
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
                if (tilemap.map[x][y].type != 0) {
                    for (auto o : gameObjects) {
                        if (o->pathfinder) {
                            o->pathfinder->updateCell(x, y, -1);
                        }
                    }
                }
                visibleTiles.insert(TilePos{x, y});
            }
        }
    }
}
