#ifndef DIRTBLOCK_H
#define DIRTBLOCK_H

#include "block.h"

class DirtBlock : public Block
{
    public:
        DirtBlock()
            :   Block()
        {
            Property::Type type;
            Property::Body body;
            Property::Food food;

            //Block::setTexturePath(TexturePath::Block::dirt);
            Block::setTexture(m_textureList[1]);

            type.description        = Property::Description::staticObstacle;

            body.material           = Property::Material::Dirt;
            body.density            = 1.1;
            body.weight             = body.density * body.density;
            body.nutritionalValue   = 0.1;

            food.isEatable          = false;
            food.healthyLevel       = 0.3;
            food.foodAmount         = 0;

            Property::Property property;
            property.setType(type);
            property.setBody(body);
            property.setFood(food);

            Block::setProperty(property);
            Block::setup_collider();
        }
};
#endif // DIRTBLOCK_H
