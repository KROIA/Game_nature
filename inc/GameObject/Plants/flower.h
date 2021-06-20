#ifndef FLOWER_H
#define FLOWER_H
#include "gameobject.h"
#include "texturePaths.h"

class Flower     : public GameObject
{
    public:
        Flower(unsigned int variation = 0)
        {
            if(variation >= TexturePath::Plant::flower.size())
                variation = 0;

            GameObject::setTexturePath(TexturePath::Plant::flower[variation]);
            GameObject::loadTexture();
            GameObject::setTextureOnPainter();
            Rect boundingBox = Rect::getFrame(m_texture->getRects());
            GameObject::addHitbox(boundingBox);

            Property::Type type;
            Property::Body body;
            Property::Food food;

            GameObject::setTexturePath(TexturePath::Block::grass);

            type.description        = Property::Description::staticObstacle;

            body.material           = Property::Material::Grass;
            body.density            = 0.4;
            body.weight             = body.density * body.density;
            body.nutritionalValue   = 2.5;

            food.isEatable          = true;
            food.healthyLevel       = 3;
            food.foodAmount         = 2;

            Property::Property property;
            property.setType(type);
            property.setBody(body);
            property.setFood(food);

            GameObject::setProperty(property);

        }

        ~Flower(){};

    protected:

    private:

};
#endif // FLOWER_H
