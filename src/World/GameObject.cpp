#include "GameObject.hpp"

GameObject::GameObject()
{
    if (!sprite.init(150, 100))
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
