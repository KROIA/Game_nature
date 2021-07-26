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
            GAME_OBJECT_BLOCK("Grass()",profiler::colors::Gold);
            m_texturePainter    = new TexturePainter();
            m_collider          = new Collider();

            RectI boundingBox = RectI::getFrame(m_textureList[variation]->getRects());
            m_collider->setShape(Shape::rect(boundingBox.getSize().x,boundingBox.getSize().y,Vector2f(boundingBox.getPos())));


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
            GAME_OBJECT_BLOCK("setTexture()",profiler::colors::Gold);
            m_texturePainter->setTexture(m_textureList[variation]);
            GAME_OBJECT_END_BLOCK;
            GameObject::addPainter(m_texturePainter);
            GameObject::setCollider(m_collider);

        }

        ~Grass(){};

    protected:
        static vector<Texture*> m_textureList;
        TexturePainter *m_texturePainter;
        Collider       *m_collider;
    private:

};
#endif
