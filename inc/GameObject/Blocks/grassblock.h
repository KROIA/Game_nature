#ifndef GRASSBLOCK_H
#define GRASSBLOCK_H

#include "block.h"

class GrassBlock : public Block
{
    public:
        GrassBlock()
            :   Block()
        {
            GAME_OBJECT_BLOCK("GrassBlock()",profiler::colors::Grey);
            Property::Type type;
            Property::Body body;
            Property::Food food;

            //Block::setTexturePath(TexturePath::Block::grass);
            GAME_OBJECT_BLOCK("setTexture()",profiler::colors::Grey50);
            Block::setTexture(m_textureList[0]);
            GAME_OBJECT_END_BLOCK;

            type.description        = Property::Description::staticObstacle;

            body.material           = Property::Material::Grass;
            body.density            = 1.2;
            body.weight             = body.density * body.density;
            body.nutritionalValue   = 1.5;

            food.isEatable          = false;
            food.healthyLevel       = 1.0;
            food.foodAmount         = 5;

            Property::Property property;
            property.setType(type);
            property.setBody(body);
            property.setFood(food);
            GAME_OBJECT_BLOCK("setProperty()",profiler::colors::Grey50);

            Block::setProperty(property);
            GAME_OBJECT_END_BLOCK;
            GAME_OBJECT_BLOCK("setup_collider()",profiler::colors::Grey50);

            Block::setup_collider();
            GAME_OBJECT_END_BLOCK;
        }
};
#endif // GRASSBLOCK_H
