#include "GameObject.hpp"

GameObject::GameObject(World* world, vec2 loc) : world(world) {
    w = 75;
    h = 50;
    if (!sprite.init(w, h, textures_path("turtle.png")))
    {
        printf("ERROR initializing sprite\n");
    }
    position = loc;
    velocity = {0, 0};
    forces = {0, 0};
    rotation = 0;
    scale = {1.f, 1.f};
}

GameObject::~GameObject() {
    delete pathfinder;

    world->selectedObjects.erase(std::remove_if(world->selectedObjects.begin(), world->selectedObjects.end(), [this](GameObject* o){ return  o== this;}), world->selectedObjects.end());
    if (world->selectedObject == this){
        world->selectedObject = world->selectedObjects.empty()? nullptr : world->selectedObjects.at(0);
    }
}

void GameObject::draw(const mat3 &projection)
{
    Tile t = world->tilemap.getTile(position.x, position.y);
    if (t.visible) {
        sprite.draw(projection, position, rotation, scale);
    }


}

bounds GameObject::getBounds() {
    return {position.x - w / 2, position.x + w / 2, position.y - h / 2, position.y + h / 2};
}

void GameObject::move(vec2 pos) {
}

void GameObject::fire(vec2 dest, vec2 pos){
       // if (sprite.selected && playerControlled){
        fight = true;

        Mix_PlayChannel(-1, world->fire, 0);

            Attack * attack = new Attack({pos.x, pos.y}, dest, this);
    world->bullets.push_back(attack);

            //attack->target = dest;
        //attack->init();
   // }



}

bool GameObject::tooFar(GameObject * a, GameObject * b){
    vec2 dist = {abs(a->getPosition().x - b->getPosition().x), abs(a->getPosition().y - b->getPosition().y)};
    float length = sqrtf((dist.x * dist.x) + (dist.y * dist.y));

    if (length > 40){
        return true;
    } else {
        return false;
    }

}


void GameObject::update() {

    const float friction = -0.5f;
    addForce({velocity.x  * friction, velocity.y * friction});

    ticks++;
    position.x += velocity.x;
    position.y += velocity.y;
    velocity.x += forces.x;
    velocity.y += forces.y;
    forces = {0, 0};

    float topLeftBorder = 0 - TILE_SIZE / 2.f;
    if (position.x < topLeftBorder) {
        position.x = topLeftBorder;
    }

    float rightBorder = world->w * TILE_SIZE - TILE_SIZE / 2.f;
    if (position.x > rightBorder) {
        position.x = rightBorder;
    }

    if (position.y < topLeftBorder) {
        position.y = topLeftBorder;
    }

    float bottomBorder = world->h * TILE_SIZE - TILE_SIZE / 2.f;
    if (position.y > bottomBorder) {
        position.y = bottomBorder;
    }
}

void GameObject::setSelected(bool selected) {
    sprite.selected = selected;
}

void GameObject::lockOn() {
    sprite.lock = !sprite.lock;
}

bool GameObject::onTerrain(vec2 pos, int type){

    int rT = world->tilemap.getTile(pos.x + w/2, pos.y - h/2).type;
    int lT = world->tilemap.getTile(pos.x - w/2, pos.y - h/2).type;
    int rB = world->tilemap.getTile(pos.x + w/2, pos.y + h/2).type;
    int lB = world->tilemap.getTile(pos.x - w/2, pos.y + h/2).type;
    bool res = false;
    if (rT == type && (pos.x + w/2) < world->w - 1)
        if (rB == type && (pos.y + h/2) < world->h - 1)
            if (lB == type && (pos.x - w/2) >= 0)
                if (lT == type && (pos.y - h/2) >= 0)
                    res = true;

    return res;
}

void GameObject::addForce(vec2 f) {
    forces.x += f.x;
    forces.y += f.y;
}

void GameObject::collide(GameObject* obj) {
}

void GameObject::destroy() {
    world->removeGameObject(this);
}

double inline clamp(double d, double min, double max)
{
    const double t = d < min ? min : d;
    return t > max ? max : t;
}

bool GameObject::collideAttack(bounds b1, bounds b2) {
    return b1.left <= b2.right && b1.right >= b2.left && b1.top <= b2.bottom && b1.bottom >= b2.top;
}

bool GameObject::checkCollision(Attack *one, GameObject *two) // AABB - Circle collision
{
    if (two != one->shooter) {
        bounds ob2 = two->getBounds();
        return one->collidesWith(one->position, 3, {ob2.left, ob2.top}, {ob2.right, ob2.bottom});
//       if(collideAttack(other, ob2) && (abs(one->target.x - two->getPosition().x) < 20) && (abs(one->target.y - two->getPosition().y) < 20)){
//           return true;
//       } else {
//           return false;
//       }
//
//
//
////        vec2 center = {(one->width/2) + one->position.x, (one->height/2) + one->position.y};
////        // Calculate AABB info (center, half-extents)
////        vec2 aabb_half_extents= {(two->getBounds().left - two->getBounds().right) / 2, (two->getBounds().top - two->getBounds().bottom) /2 };
////        vec2 aabb_center = {
////                two->getPosition().x + aabb_half_extents.x,
////                two->getPosition().y + aabb_half_extents.y
////        };
////        // Get difference vector between both centers
////        vec2 difference = {center.x - aabb_center.x, center.y - aabb_center.y};
////        auto valA = (float)clamp(difference.x, -aabb_half_extents.x, aabb_half_extents.x);
////        auto valB = (float)clamp(difference.y, -aabb_half_extents.y, aabb_half_extents.y);
////
////        vec2 clamped = {valA, valB};
////
////        // Add clamped value to AABB_center and we get the value of box closest to circle
////        vec2 closest = {aabb_center.x + clamped.x, aabb_center.y + clamped.y};
////        // Retrieve vector between center circle and closest point AABB and check if length <= radius
////        difference = {closest.x - center.x,closest.y - center.y};
////        float length = sqrtf((difference.x * difference.x) + (difference.y + difference.y));
////
////        return length < two->w;
//    } else {
//        return false;
    }
    return false;
}


bool GameObject::missed(Attack *one, GameObject *two) // AABB - Circle collision
{

    if (one) {

        if (abs(two->position.x - one->position.x) < 2 && abs(two->position.y - one->position.y) < 2) {

            return true;
        } else {
            return false;
        }
    }
}

