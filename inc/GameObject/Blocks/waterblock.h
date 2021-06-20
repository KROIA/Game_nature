#ifndef WATERBLOCK_H
#define WATERBLOCK_H

#include "block.h"

class WaterBlock : public Block
{
    public:
        WaterBlock()
            :   Block()
        {
            Property::Type type;
            Property::Body body;
            Property::Food food;

            Block::setTexturePath(TexturePath::Block::water);

            type.description        = Property::Description::staticObstacle;

            body.material           = Property::Material::Water;
            body.density            = 1.0;
            body.weight             = body.density * body.density;
            body.nutritionalValue   = 1;

            food.isEatable          = true;
            food.healthyLevel       = 1;
            food.foodAmount         = 10;

            Property::Property property;
            property.setType(type);
            property.setBody(body);
            property.setFood(food);

            Block::setProperty(property);
            Block::setup_collider();
        }
};
#endif // WATERBLOCK_H
