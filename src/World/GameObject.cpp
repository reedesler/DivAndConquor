#include "GameObject.hpp"

GameObject::GameObject(World* world) : world(world) {
    w = 75;
    h = 50;
    if (!sprite.init(w, h, textures_path("turtle.png")))
    {
        printf("ERROR initializing sprite\n");
    }
    position = {200, 200};
    rotation = 0;
    scale = {1.f, 1.f};

    pathfinder = new Pathfinder(world);
}

void GameObject::draw(const mat3 &projection)
{
    sprite.draw(projection, position, rotation, scale);

}

bounds GameObject::getBounds() {
    return {position.x - w / 2, position.x + w / 2, position.y - h / 2, position.y + h / 2};
}

void GameObject::move(vec2 pos) {
    //position = pos;
    TilePos start = Tilemap::getTilePos(position.x, position.y);
    TilePos goal = Tilemap::getTilePos(pos.x, pos.y);
    pathfinder->init(start.x, start.y, goal.x, goal.y);
    pathfinder->replan();
    path = pathfinder->getPath();
}

void GameObject::update() {
    world->setExplored(position, 7 * TILE_SIZE);
    if (!path.path.empty()) {
        std::list<PF_Tile>::iterator next = std::next(path.path.begin());
        if (next == path.path.end()) return;
        float destX = next->x * TILE_SIZE;
        float destY = next->y * TILE_SIZE;
        if (abs(position.x - destX) <= 5 && abs(position.y - destY) <= 5) {
            pathfinder->updateStart(next->x, next->y);
            pathfinder->replan();
            path = pathfinder->getPath();
        } else {
            vec2 dir =  {destX - position.x, destY - position.y};
            float length = sqrt(dir.x*dir.x + dir.y*dir.y);
            const float VELOCITY = 5;
            vec2 newPos = {position.x + dir.x / length * VELOCITY, position.y + dir.y / length * VELOCITY};
            position = newPos;
        }
    }
}

void GameObject::setSelected() {
    sprite.selected = !sprite.selected;
}

bool GameObject::onTerrain(vec2 pos, int type){
    int rT = world->tilemap.getTile(pos.x + w/2, pos.y).type;
    int lT = world->tilemap.getTile(pos.x - w/2, pos.y).type;
    int rB = world->tilemap.getTile(pos.x + w/2, pos.y + h/2).type;
    int lB = world->tilemap.getTile(pos.x - w/2, pos.y + h/2).type;
    return rT == type && lT == type && type == rB && lB == type;
}