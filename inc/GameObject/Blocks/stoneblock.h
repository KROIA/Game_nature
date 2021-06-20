#ifndef STONEBLOCK_H
#define STONEBLOCK_H

#include "block.h"

class StoneBlock : public Block
{
    public:
        StoneBlock()
            :   Block()
        {
            Property::Type type;
            Property::Body body;
            Property::Food food;

            Block::setTexturePath(TexturePath::Block::stone);

            type.description        = Property::Description::staticObstacle;

            body.material           = Property::Material::Stone;
            body.density            = 2;
            body.weight             = body.density * body.density;
            body.nutritionalValue   = 0;

            food.isEatable          = false;
            food.healthyLevel       = 0;
            food.foodAmount         = 0;

            Property::Property property;
            property.setType(type);
            property.setBody(body);
            property.setFood(food);

            Block::setProperty(property);
            Block::setup_collider();
        }
};
#endif // STONEBLOCK_H
