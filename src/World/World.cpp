#include "World.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <typeindex>
#include <algorithm>


World::World(Game* game, rect viewPort) : tilemap(Tilemap::LoadFromFile(maps_path("map_demo.txt"))),
                              camera(Camera(viewPort, tilemap.width, tilemap.height, TILE_SIZE))
{
    this->game = game;
    state = neutral;
    printf("%c", state);
    auto *initialSet = new SettlementObject(this, {3150, 3700});
    centerCameraOn(*initialSet);
    camera.finishMovement();
    gameObjects.push_back(initialSet);
    //gameObjects.push_back(new PirateShip(this, {2300, 1300}));
    pathRenderer = new PathRenderer();
    //attack = new Attack({340, 900});
    // attack->init();
    w = tilemap.width * TILE_SIZE;
    h = tilemap.height * TILE_SIZE;
    this->setPirateSoldiers();
    this->setResources();
    this->setPirates();
    initialSet->updateResources(0, 3000);

    prevMouseXpos = viewPort.w / 2.f;
    prevMouseYpos = viewPort.h / 2.f;

    selectOverlay = Sprite();
    if (!selectOverlay.init(1, 1, textures_path("select_overlay.png")))
    {
        printf("ERROR initializing sprite\n");
    }

    hpBar = Sprite();
    if (!hpBar.init(1,1, textures_path("pixel.png")))
    {
        printf("ERROR initializing sprite\n");
    }
    selectRing = Sprite();
    if (!selectRing.init(1, 1, textures_path("select_ring.png")))
    {
        printf("ERROR initializing sprite\n");
    }
    //==================================
    // sound initialized here

    //TODO uncomment music
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");
    }

    background_music = Mix_LoadMUS(audio_path("divide_and_conquer.mp3"));
    fire = Mix_LoadWAV(audio_path("gunfire.wav"));


    if (background_music == nullptr || fire == nullptr)
    {
        fprintf(stderr, "Failed to load sounds\n %s\n %s\n %s\n make sure the data directory is present",
                audio_path("background.wav"),
                audio_path("gunfire.wav"));

    }

    // Playing background music undefinitely
    Mix_PlayMusic(background_music, -1);

    fprintf(stderr, "Loaded music\n");

    fprintf(stderr, "Loaded music\n");

}

void World::addShip()
{
    if (!selectedObject)
        return;

    vec2 pos = selectedObject->getPosition();

    float x = -1;
    float y = -1;
    while (x <= 0 || y <= 0 || tilemap.getTile(x, y).type != 0)
    {
        x = std::rand() % (10 * TILE_SIZE) + pos.x - 5 * TILE_SIZE;
        y = std::rand() % (10 * TILE_SIZE) + pos.y - 5 * TILE_SIZE;
    }
    vec3 cost = {100,500,100};
    auto settl = (SettlementObject *) selectedObject;
    vec3 res = settl->getResources();
    if (this->canAfford( res, cost, true)){
        settl->updateResources(0, -cost.x);
        settl->updateResources(1, -cost.y);
        settl->updateResources(2, -cost.z);
        auto tmpShip = new ShipObject(this, {x, y}, settl);
        this->gameObjects.push_back(tmpShip);
        this->fleet.push_back(tmpShip);
    }

}

void World::addSettlement()
{
    if (!selectedObject)
        return;

    vec2 pos = selectedObject->getPosition();

    float x = -1;
    float y = -1;
    int tries = 0;
    while (x <= 0 || y <= 0 || tilemap.getTile(x, y).type == 0)
    {
        x = std::rand() % (10 * TILE_SIZE) + pos.x - 5 * TILE_SIZE;
        y = std::rand() % (10 * TILE_SIZE) + pos.y - 5 * TILE_SIZE;
        if (tries++ >= 100)
            return;
    }
    SettlementObject * settl = nullptr;
    ShipObject * ship  = dynamic_cast<ShipObject*>(getSelected());
    if (ship  != nullptr) {
        settl = ship->settlement;
    }

    Sailor* sailor = dynamic_cast<Sailor*>(getSelected());
    if (sailor != nullptr) {
        settl = sailor->settlement;
    }
    if (settl == nullptr) {
        return;
    }
    vec3 cost = {500,500,500};
    vec3 res = settl->getResources();
    if (this->canAfford( res, cost, true)){
        settl->updateResources(0, -cost.x);
        settl->updateResources(1, -cost.y);
        settl->updateResources(2, -cost.z);
        this->gameObjects.push_back(new SettlementObject(this, {x, y}));
    }
}

void World::addSailor()
{
    if (!selectedObject)
        return;

    vec2 pos = selectedObject->getPosition();

    float x = -1;
    float y = -1;
    while (x <= 0 || y <= 0 || tilemap.getTile(x, y).type != 2 || (abs(x-pos.x) < 100 && abs(y-pos.y) < 100))
    {
        x = std::rand() % (10 * TILE_SIZE) + pos.x - 5 * TILE_SIZE;
        y = std::rand() % (10 * TILE_SIZE) + pos.y - 5 * TILE_SIZE;
    }
    vec3 cost = {100,0,0};
    auto settl = (SettlementObject *) selectedObject;
    vec3 res = settl->getResources();
    if (this->canAfford( res, cost, true)){
        settl->updateResources(0, -cost.x);
        settl->updateResources(1, -cost.y);
        settl->updateResources(2, -cost.z);
        auto *tmpSailor = new Sailor(this, {x, y}, settl);
        this->gameObjects.push_back(tmpSailor);
        this->army.push_back(tmpSailor);
    }

}

bool World::canAfford(vec3 resources, vec3 cost, bool verbose) {

    std::string names[] = {"gold", "iron", "timber"};
    float res[] = {resources.x, resources.y, resources.z};
    float costs[] = {cost.x, cost.y, cost.z};
    bool canAfford = true;
    for (int i = 0; i < 3; i++) {
        if(costs[i] > res[i])
        {
            canAfford = false;
            if (verbose) {
                std::ostringstream out;
                out << "Not enough " << names[i] << "! ";
                out << "You need " << (costs[i] - res[i]) << " more.";
                game->printLn(out.str());
            } else {
                return false;
            }
        }
    }
    return canAfford;
}

void World::centerCameraOn(GameObject &go)
{
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

    for (int i = 0; i < gameObjects.size(); i++)
    {
        for (int j = i + 1; j < gameObjects.size(); j++)
        {
            GameObject *ob1 = gameObjects[i];
            GameObject *ob2 = gameObjects[j];
            if (collide(ob1->getBounds(), ob2->getBounds()))
            {
                ob1->collide(ob2);
                ob2->collide(ob1);
            }
        }
    }

    for (auto o : toBeDeleted)
    {
        gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), o), gameObjects.end());
        delete o;
    }

    toBeDeleted.clear();


//    for (auto a : pastAttacks)
//    {
//        pastAttacks.erase(std::remove(pastAttacks.begin(), pastAttacks.end(), a), pastAttacks.end());
//        delete a;
//    }

    //check for loot collisions
    std::vector<int> toDelete;
    for (int i = 0; i < resources.size(); ++i)
    {
        for (auto o : army)
        {
            if (o->playerControlled && resources[i]->collect(game, o))
            {
                toDelete.push_back(i);
            }
        }
    }

    //remove collected loot
    for (int i : toDelete)
        resources.erase(resources.begin() + i);

    tilemap.setExplored(visibleTiles);

    if (selectedObject && selectedObject->pathfinder)
    {
        pathRenderer->init(selectedObject->pathfinder->getPath());
    }


    std::vector<Attack *> shot;

    for (auto a : bullets)
    {
        for (auto o : gameObjects)
        {if ( o->checkCollision(a, o))
            {
                o->health = o->health - 20;
                shot.push_back(a);
//                if(o->missed(a,o) ){
//                    shot.push_back(a);
//                }
            } else if(a->miss){
                shot.push_back(a);
            }
        }
        if (a->ticks >= 100) {
            shot.push_back(a);
        }
    }

    for (auto o : shot)
    {
        bullets.erase(std::remove(bullets.begin(), bullets.end(), o), bullets.end());
        //delete o;
    }

    shot.clear();

    ai->updateState(this);

    if (lock && !tilemap.getTile(lock->getPosition().x, lock->getPosition().y).visible) {
        lock = nullptr;
    }


    if (camera.followSelected && getSelected() != nullptr)
        centerCameraOn(*getSelected());

    if (ticks % 1800 == 0) {
        setPirates();
    }

    ticks++;
}

void World::draw(int pixelScale)
{
    mat3 projection = camera.getProjection(pixelScale);
    tilemap.draw(projection);

    for (auto a: bullets){
       // if(selectedObject && a != nullptr && selectedObject->fight){

            a->draw(projection);
        //}
}

    for (auto o : selectedObjects) {
        if (o == selectedObject)
        {
            selectRing.tint = {1.f, 1.f, 1.f};
        } else {
            selectRing.tint = {0.1f, 1.f, 0.1f};
        }
        vec2 spt_size = {o->getSprite().width, o->getSprite().height};
        glBlendFunc(GL_ONE, GL_ONE);
        selectRing.draw(projection, {o->position.x, o->position.y + spt_size.y/2.f}, 0.f, {spt_size.x*1.3f, spt_size.x});
        glBlendFunc(GL_ONE, GL_ZERO);
    }
    for (auto o : gameObjects)
    {
        o->draw(projection);
    }
    for (auto o : gameObjects)
    {
       // hp bar

        Tile t = tilemap.getTile(o->position.x,o->position.y);
        if (t.visible && o->health < o->maxHealth && o->health >= 0.f) {
            float maxWidth = 100.f;
            float border = 2.f;
            float width = maxWidth * (o->health/o->maxHealth);
            float height = 16.f;
            hpBar.tint = {0,0,0};
            hpBar.draw(projection, {o->position.x, o->position.y - o->getSprite().height/2 - 5}, 0 , {maxWidth + border*2.f, height + border*2.f});
            hpBar.tint = {0,1.f,0};
            hpBar.draw(projection, {o->position.x - maxWidth/2 + width/2 + border , o->position.y - o->getSprite().height/2 - 5}, 0 , {width, height});
        }
    }
    for (auto o : resources)
        o->draw(projection);



    if (selectedObject && selectedObject->pathfinder)
    {
        pathRenderer->draw(projection);
    }
    if( mouseDrag) {
        vec2 area = {-(mouseDragTempArea.right - mouseDragTempArea.left), mouseDragTempArea.bottom - mouseDragTempArea.top};
        // uncomment to give the selection box a cool negative effect :D
        //glBlendEquationSeparate(GL_FUNC_SUBTRACT, GL_FUNC_ADD);
        selectOverlay.draw(projection,{mouseDragTempArea.left - area.x/2, mouseDragTempArea.bottom - area.y/2},0.f, area);
        //glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    }




}

void World::onClick(int button, int action, float xpos, float ypos)
{
    vec2 worldCoords = camera.viewToWorld({xpos, ypos});
    if (button == GLFW_MOUSE_BUTTON_1 )
    {
        if (action == GLFW_RELEASE) {
            if (mouseDrag == false){
                std::cout << "Drag finished but wasn't started???" << std::endl;
            }
            mouseDrag=false;
            bounds dragArea = {mouseDragStart.x, worldCoords.x, mouseDragStart.y, worldCoords.y};
            mouseDragStart = {-1,-1};
            // swap values around to make sure w/h aren't negative
            if (dragArea.right < dragArea.left){
                dragArea = {dragArea.right, dragArea.left, dragArea.top, dragArea.bottom};
            }
            if (dragArea.bottom < dragArea.top){
                dragArea = {dragArea.left, dragArea.right, dragArea.bottom, dragArea.top};
            }
            // std::cout << "Drag complete:" << std::endl;
            // std::cout << "\tw: "<< dragArea.right - dragArea.left << std::endl;
            // std::cout << "\th: "<< dragArea.bottom - dragArea.top << std::endl;
            for (auto o : selectedObjects){
                o->setSelected(false);
            }
            selectedObjects.clear();
            selectedObject = nullptr;
            std::vector<GameObject *> selectionCandidates;
            std::map<std::type_index, int> counts;
            for (auto o : gameObjects)
            {
                if (o->playerControlled && collide(o->getBounds(), dragArea))
                {
                    counts[typeid(*o)]++;
                    // std::cout << "Selected a " << typeid(*o).name() << std::endl;
                    selectionCandidates.push_back(o);
                }
            }

            if (!selectionCandidates.empty()) {
                // find the type that shows up the most
                type_index maxType = typeid(*selectionCandidates.at(0));
                for (auto x : counts){
                    if(x.second >= counts.at(maxType))
                        maxType = x.first;
                }
                // only keep objects with that type
                for (auto o : selectionCandidates){
                    if(std::type_index(typeid(*o)) == maxType)
                       selectedObjects.push_back(o);
                }
                selectedObject = selectedObjects.at(0);


            }
            return;
        }
        if (action == GLFW_PRESS) {
            mouseDrag = true;
            mouseDragStart = worldCoords;
            mouseDragTempArea = {worldCoords.x, worldCoords.x, worldCoords.y, worldCoords.y };
        }

    }
    if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
    {
        for (auto o : gameObjects)
        {
            if (!o->playerControlled && inBounds(o->getBounds(), worldCoords))
            {
                //int a = 1;
                if (lock == o)
                    lock = nullptr;
                else
                {
                    if (lock)
                        lock->lockOn();
                    lock = o;
                }
                o->lockOn();
                return;
            }
        }

        int x,y,dx,dy;
        x = y = dx = 0;
        dy = -1;
        int t;
        for (GameObject* o : selectedObjects) {
            if (lock != nullptr && o->canShoot) {

                o->fire(lock->getPosition(), o->getPosition());
            }
            else if (o == selectedObject) {
                o->move(worldCoords);
            } else {
                vec2 target = {0, 0};
                do {
                    if( (x == y) || ((x < 0) && (x == -y)) || ((x > 0) && (x == 1-y))){
                        t = dx;
                        dx = -dy;
                        dy = t;
                    }
                    x += dx;
                    y += dy;
                    target = {worldCoords.x + x * TILE_SIZE, worldCoords.y + y * TILE_SIZE};
                } while (!inBounds(getWorldBounds(), target) || (o->landUnit ? tilemap.getTile(target.x, target.y).type == 0 : tilemap.getTile(target.x, target.y).type != 0));
                o->move(target);
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
                for (auto o : gameObjects)
                {
                    if (o->pathfinder && !o->pathfinder->canSeeAll)
                    {
                        o->pathfinder->updateCell(x, y, tilemap.map[x][y].type == 0);
                    }
                }
                visibleTiles.insert(TilePos{x, y});
            }
        }
    }
}

#define MOUSE_MOVE_SIZE 50

void World::onMouseMove(double xpos, double ypos)
{
    // std::cout << "mouse move\t" << xpos << "\t" << ypos << std::endl;
    vec2 worldCoords = camera.viewToWorld({(float)xpos, (float)ypos});
    if (mouseDrag) {
            mouseDragTempArea = {mouseDragStart.x, worldCoords.x, mouseDragStart.y, worldCoords.y};
            // swap values around to make sure w/h aren't negative
            if (mouseDragTempArea.right < mouseDragTempArea.left){
                mouseDragTempArea = {mouseDragTempArea.right, mouseDragTempArea.left, mouseDragTempArea.top, mouseDragTempArea.bottom};
            }
            if (mouseDragTempArea.bottom < mouseDragTempArea.top){
                mouseDragTempArea = {mouseDragTempArea.left, mouseDragTempArea.right, mouseDragTempArea.bottom, mouseDragTempArea.top};
            }
    }
    if (xpos == -1 && ypos == -1)
    {
        xpos = camera.viewPort.w / 2.f;
        ypos = camera.viewPort.h / 2.f;
    }
    vec2 cameraDir = {0, 0};
    if (xpos <= MOUSE_MOVE_SIZE && prevMouseXpos > MOUSE_MOVE_SIZE)
        cameraDir.x -= 1;
    if (prevMouseXpos <= MOUSE_MOVE_SIZE && xpos > MOUSE_MOVE_SIZE)
        cameraDir.x += 1;

    if (xpos >= camera.viewPort.w - MOUSE_MOVE_SIZE && prevMouseXpos < camera.viewPort.w - MOUSE_MOVE_SIZE)
        cameraDir.x += 1;
    if (prevMouseXpos >= camera.viewPort.w - MOUSE_MOVE_SIZE && xpos < camera.viewPort.w - MOUSE_MOVE_SIZE)
        cameraDir.x -= 1;

    if (ypos <= MOUSE_MOVE_SIZE && prevMouseYpos > MOUSE_MOVE_SIZE)
        cameraDir.y -= 1;
    if (prevMouseYpos <= MOUSE_MOVE_SIZE && ypos > MOUSE_MOVE_SIZE)
        cameraDir.y += 1;

    if (ypos >= camera.viewPort.h - MOUSE_MOVE_SIZE && prevMouseYpos < camera.viewPort.h - MOUSE_MOVE_SIZE)
        cameraDir.y += 1;
    if (prevMouseYpos >= camera.viewPort.h - MOUSE_MOVE_SIZE && ypos < camera.viewPort.h - MOUSE_MOVE_SIZE)
        cameraDir.y -= 1;

    camera.move(cameraDir, 0);

    prevMouseXpos = xpos;
    prevMouseYpos = ypos;
}

GameObject *World::getClosestObject(vec2 pos, bool playerControlled, bool landUnit)
{
    float minDist = INFINITY;
    GameObject *closest = nullptr;
    for (auto o : gameObjects)
    {
        if (o->playerControlled == playerControlled && o->landUnit == landUnit)
        {
            float difX = pos.x - o->getPosition().x;
            float difY = pos.y - o->getPosition().y;
            float dist = difX * difX + difY * difY;
            if (dist < minDist)
            {
                minDist = dist;
                closest = o;
            }
        }
    }
    return closest;
}

GameObject *World::getClosestObjectOnLand(vec2 pos, bool playerControlled, bool landUnit)
{
    float minDist = 900;
    GameObject *closest = nullptr;
    for (auto o : gameObjects)
    {
        if (o->playerControlled == playerControlled && o->landUnit == landUnit)
        {
            float difX = pos.x - o->getPosition().x;
            float difY = pos.y - o->getPosition().y;
            float dist = difX * difX + difY * difY;
            if (dist < minDist)
            {
                minDist = dist;
                closest = o;
            }
        }
    }
    return closest;
}


void World::fireOnClosestObject(GameObject * attacker, bool playerControlled, bool landUnit)
{
    float minDist = 500;
    GameObject *closest = nullptr;
    for (auto o : gameObjects)
    {
        if (o->playerControlled == playerControlled || o->landUnit == landUnit && o->landUnit != landUnit)
        {
            float difX = attacker->getPosition().x - o->getPosition().x;
            float difY = attacker->getPosition().y - o->getPosition().y;
            float dist = sqrt(difX * difX + difY * difY);
            if (dist < minDist)
            {
                minDist = dist;
                closest = o;
            }

            if(closest != nullptr){
                attacker->fire(closest->getPosition(), attacker->getPosition());
            }
        }
    }





}


void World::setPirates()
{
    if(pirateStrength < 3){
        printf("Adding pirates\n");
        for (int i = 0; i < 1; i++){
            float x = std::rand() % (this->w - 100);
            float y = std::rand() % (this->h - 100);
            while (tilemap.getTile(x, y).type != 0 && !tilemap.getTile(x, y).visible)
            {
                x = std::rand() % (this->w - 100);
                y = std::rand() % (this->h - 100);
            }
            gameObjects.push_back(new PirateShip(this, {x, y}));
        }


    }

}
void World::setResources()
{
    //setting gold
    for (int i = 0; i < 50; i++)
    {
        float x = std::rand() % (this->w - 100);
        float y = std::rand() % (this->h - 100);
        while (tilemap.getTile(x, y).type != 2)
        {
            x = std::rand() % (this->w - 100);
            y = std::rand() % (this->h - 100);
        }
        resources.push_back(new Resource(this, {x, y}, 0, 500));
    }
    //setting iron
    for (int i = 0; i < 50; i++)
    {
        float x = std::rand() % (this->w - 100);
        float y = std::rand() % (this->h - 100);
        while (tilemap.getTile(x, y).type != 2)
        {
            x = std::rand() % (this->w - 100);
            y = std::rand() % (this->h - 100);
        }
        resources.push_back(new Resource(this, {x, y}, 1, 500));
    }
    //setting timber
    for (int i = 0; i < 50; i++)
    {
        float x = std::rand() % (this->w - 100);
        float y = std::rand() % (this->h - 100);
        while (tilemap.getTile(x, y).type != 2)
        {
            x = std::rand() % (this->w - 100);
            y = std::rand() % (this->h - 100);
        }
        resources.push_back(new Resource(this, {x, y}, 2, 500));
    }
}

void World::setPirateSoldiers()
{
    //setting gold
    for (int i = 0; i < 20; i++)
    {
        float x = std::rand() % (this->w - 100);
        float y = std::rand() % (this->h - 100);
        while (tilemap.getTile(x, y).type != 2)
        {
            x = std::rand() % (this->w - 100);
            y = std::rand() % (this->h - 100);
        }
        gameObjects.push_back(new Pirate(this, {x, y}));
    }

}

void World::removeGameObject(GameObject *obj)
{
    if (selectedObject == obj)
    {
        selectedObject = nullptr;
    }
    toBeDeleted.push_back(obj);
}

bounds World::getWorldBounds() {

    float topLeftBorder = 0 - TILE_SIZE / 2.f;
    float rightBorder = w * TILE_SIZE + topLeftBorder;
    float bottomBorder = h * TILE_SIZE + topLeftBorder;
    return {topLeftBorder, rightBorder, topLeftBorder, bottomBorder};
}

bool World::checkWinCond(){
    float areaAvailable = w * h;
    float areaConquered = 2 * ((settlementPoints * settlementPoints)/areaAvailable);
    coverage = areaConquered * 100;
    if(areaConquered > 0.8){
        return true;
    }
    return false;

};
