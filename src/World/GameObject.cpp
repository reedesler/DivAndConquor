#include "GameObject.hpp"

GameObject::GameObject()
{
    w = 75;
    h = 50;
    if (!sprite.init(w, h, textures_path("turtle.png")))
    {
        printf("ERROR initializing sprite\n");
    }
    position = {200, 200};
    rotation = 0;
    scale = {1.f, 1.f};
}

void GameObject::draw(const mat3 &projection)
{
    sprite.draw(projection, position, rotation, scale);
}

bounds GameObject::getBounds() {
    return {position.x - w / 2, position.x + w / 2, position.y - h / 2, position.y + h / 2};
}

void GameObject::move(vec2 pos) {
    position = pos;
}
