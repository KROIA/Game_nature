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
            m_texture           = new Texture();
            m_texturePainter    = new TexturePainter();

            if(variation >= TexturePath::Plant::flower.size())
                variation = 0;

            m_texture->loadTexture(TexturePath::Plant::flower[variation]);

            //GameObject::setTexturePath(TexturePath::Plant::flower[variation]);
            //GameObject::loadTexture();
            //GameObject::setTextureOnPainter();
            RectI boundingBox = RectI::getFrame(m_texture->getRects());
            GameObject::addHitbox(boundingBox);

            Property::Type type;
            Property::Body body;
            Property::Food food;

            //GameObject::setTexturePath(TexturePath::Block::grass);

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

            m_texturePainter->setTexture(m_texture);
            GameObject::setPainter(m_texturePainter);

        }

        ~Flower(){ delete m_texture; };

    protected:
        Texture *m_texture;
        TexturePainter *m_texturePainter;
    private:

};
#endif // FLOWER_H
