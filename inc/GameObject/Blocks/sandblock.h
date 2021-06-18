#ifndef SANDBLOCK_H
#define SANDBLOCK_H

#include "block.h"

class SandBlock : public Block
{
    public:
        SandBlock()
        {
            Property::Type type;
            Property::Body body;
            Property::Food food;

            Block::setTexturePath(TexturePath::Block::sand);

            type.description        = Property::Description::staticObstacle;

            body.material           = Property::Material::Sand;
            body.density            = 1.4;
            body.weight             = body.density * body.density;
            body.nutritionalValue   = 0;

            food.isEatable          = false;
            food.healthyLevel       = 0.1;
            food.foodAmount         = 0;

            Property::Property property;
            property.setType(type);
            property.setBody(body);
            property.setFood(food);

            Block::setProperty(property);
        }
};
#endif // SANDBLOCK_H
