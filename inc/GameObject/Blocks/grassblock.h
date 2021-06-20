#ifndef GRASSBLOCK_H
#define GRASSBLOCK_H

#include "block.h"

class GrassBlock : public Block
{
    public:
        GrassBlock()
            :   Block()
        {
            Property::Type type;
            Property::Body body;
            Property::Food food;

            Block::setTexturePath(TexturePath::Block::grass);

            type.description        = Property::Description::staticObstacle;

            body.material           = Property::Material::Grass;
            body.density            = 1.2;
            body.weight             = body.density * body.density;
            body.nutritionalValue   = 1.5;

            food.isEatable          = true;
            food.healthyLevel       = 1.0;
            food.foodAmount         = 5;

            Property::Property property;
            property.setType(type);
            property.setBody(body);
            property.setFood(food);

            Block::setProperty(property);
        }

        virtual void checkEvent()
        {
            Block::checkEvent();
            if(m_property.getFood().foodAmount == 0)
            {
                GameObject::deleteMeFromEngine();
            }
        }
};
#endif // GRASSBLOCK_H
