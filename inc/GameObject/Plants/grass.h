#ifndef GRASS_H
#define GRASS_H
#include "gameobject.h"
#include "texturePaths.h"
#include "texturePainter.h"

class Grass     : public GameObject
{
    public:
        Grass(unsigned int variation = 0)
            :   GameObject()
        {
            if(variation >= TexturePath::Plant::grass.size())
                variation = 0;
            if(m_textureList.size() == 0)
            {
                m_textureList.reserve(TexturePath::Plant::grass.size());
                for(size_t i=0; i<TexturePath::Plant::grass.size(); i++)
                {
                    m_textureList.push_back(new Texture());
                    m_textureList[i]->loadTexture(TexturePath::Plant::grass[i]);
                }
            }
            m_texturePainter    = new TexturePainter();

            RectI boundingBox = RectI::getFrame(m_textureList[variation]->getRects());
            GameObject::addHitbox(boundingBox);


            Property::Type type;
            Property::Body body;
            Property::Food food;


            type.description        = Property::Description::staticObstacle;

            body.material           = Property::Material::Grass;
            body.density            = 0.8;
            body.weight             = body.density * body.density;
            body.nutritionalValue   = 1.5;

            food.isEatable          = true;
            food.healthyLevel       = 2;
            food.foodAmount         = 5;

            Property::Property property;
            property.setType(type);
            property.setBody(body);
            property.setFood(food);

            GameObject::setProperty(property);

            m_texturePainter->setTexture(new Texture(*m_textureList[variation]));
            GameObject::setPainter(m_texturePainter);

        }

        ~Grass(){};

    protected:
        static vector<Texture*> m_textureList;
        TexturePainter *m_texturePainter;
    private:

};
#endif
