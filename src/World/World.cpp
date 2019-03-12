#include "World.hpp"

World::World(rect viewPort) : tilemap(Tilemap::LoadFromFile(maps_path("map_horizontal.txt"))),
                                camera(Camera(viewPort, tilemap.width, tilemap.height, TILE_SIZE))
{
    auto *initialSet = new SettlementObject(this, {770, 330});
    auto *initialShip = new ShipObject(this, {600, 400});
    auto *initialSailor = new Sailor(this, {900, 350}, initialSet);
    gameObjects.push_back(initialShip);
    gameObjects.push_back(initialSet);
    gameObjects.push_back(initialSailor);
    gameObjects.push_back(new PirateShip(this, {2300, 1300}));

    //to keep track of various unit types
    army.push_back(initialSailor);
    fleet.push_back(initialShip);

    pathRenderer = new PathRenderer();
    w = tilemap.width *  TILE_SIZE;
    h = tilemap.height * TILE_SIZE;
    this->setResources();

    prevMouseXpos = viewPort.w / 2.f;
    prevMouseYpos = viewPort.h / 2.f;
}

void World::addShip(ShipObject *ship)
{
    this->gameObjects.push_back(ship);
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

    for (int i = 0; i < gameObjects.size(); i++) {
        for (int j = i + 1; j < gameObjects.size(); j++) {
            GameObject* ob1 = gameObjects[i];
            GameObject* ob2 = gameObjects[j];
            if (collide(ob1->getBounds(), ob2->getBounds())) {
                ob1->collide(ob2);
                ob2->collide(ob1);
            }
        }
    }

    for (auto o : toBeDeleted) {
        gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), o), gameObjects.end());
        delete o;
    }

    toBeDeleted.clear();

    //check for loot collisions
        std::vector<int> toDelete;
    for (int i = 0; i < resources.size(); ++i) {
        for (auto o : army){
            if (o->playerControlled && resources[i]->collect(o)) {
                printf("current resources for settlement:\n");
                vec3 tmp = o->settlement->getResources();
                printf("gold: %f\niron: %f\ntimber: %f\n", tmp.x, tmp.y, tmp.z);
                toDelete.push_back(i);
            }
        }
    }

    //remove collected loot
    for (int i: toDelete)
        resources.erase(resources.begin()+i);

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
    for (auto o: resources)
        o->draw(projection);
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
            if (o->playerControlled && inBounds(o->getBounds(), worldCoords))
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
                    if (o->pathfinder && !o->pathfinder->canSeeAll) {
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

GameObject* World::getClosestObject(vec2 pos, bool playerControlled, bool landUnit) {
    float minDist = INFINITY;
    GameObject* closest;
    for (auto o : gameObjects) {
        if (o->playerControlled == playerControlled && o->landUnit == landUnit) {
            float difX = pos.x - o->getPosition().x;
            float difY = pos.y - o->getPosition().y;
            float dist = difX * difX + difY * difY;
            if (dist < minDist) {
                minDist = dist;
                closest = o;
            }
        }
    }
    return closest;
}

void World::setResources(){
    //setting gold
    for (int i = 0; i < 100; i++){
        float x = std::rand() % (this->w - 100);
        float y = std::rand() % (this->h - 100);
        while(tilemap.getTile(x, y).type != 2){
            x = std::rand() % (this->w - 100);
            y = std::rand() % (this->h - 100);
        }
        resources.push_back(new Resource(this, {x, y}, 0, 500));
    }
    //setting iron
    for (int i = 0; i < 100; i++){
        float x = std::rand() % (this->w - 100);
        float y = std::rand() % (this->h - 100);
        while(tilemap.getTile(x, y).type != 2){
            x = std::rand() % (this->w - 100);
            y = std::rand() % (this->h - 100);
        }
        resources.push_back(new Resource(this, {x, y}, 1, 500));
    }
    //setting timber
    for (int i = 0; i < 100; i++){
        float x = std::rand() % (this->w - 100);
        float y = std::rand() % (this->h - 100);
        while(tilemap.getTile(x, y).type != 2){
            x = std::rand() % (this->w - 100);
            y = std::rand() % (this->h - 100);
        }
        resources.push_back(new Resource(this, {x, y}, 2, 500));
    }
}

void World::removeGameObject(GameObject* obj) {
    if (selectedObject == obj) {
        selectedObject = nullptr;
    }
    toBeDeleted.push_back(obj);
}
