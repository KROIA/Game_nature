#ifndef FLOWER_H
#define FLOWER_H
#include "gameobject.h"
#include "texturePaths.h"
#include "texturePainter.h"

class Flower     : public GameObject
{
    public:
        Flower(unsigned int variation = 0)
            :   GameObject()
        {
            if(variation >= TexturePath::Plant::flower.size())
                variation = 0;
            if(m_textureList.size() == 0)
            {
                m_textureList.reserve(TexturePath::Plant::flower.size());
                for(size_t i=0; i<TexturePath::Plant::flower.size(); i++)
                {
                    m_textureList.push_back(new Texture());
                    m_textureList[i]->loadTexture(TexturePath::Plant::flower[i]);
                }
            }
            GAME_OBJECT_BLOCK("Flower()",profiler::colors::Gold);
            m_texturePainter    = new TexturePainter();

            RectI boundingBox = RectI::getFrame(m_textureList[variation]->getRects());
            GameObject::addHitbox(boundingBox);

            Property::Type type;
            Property::Body body;
            Property::Food food;

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

            GAME_OBJECT_BLOCK("setTexture()",profiler::colors::Gold);
            m_texturePainter->setTexture(m_textureList[variation]);
            GAME_OBJECT_END_BLOCK;
            GameObject::setPainter(m_texturePainter);

        }

        ~Flower(){};

    protected:
        static vector<Texture*> m_textureList;
        TexturePainter *m_texturePainter;

    private:

};

#endif // FLOWER_H
