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
            m_texture           = new Texture();
            m_texturePainter    = new TexturePainter();

            if(variation >= TexturePath::Plant::grass.size())
                variation = 0;


            m_texture->loadTexture(TexturePath::Plant::grass[variation]);
            //GameObject::setTexturePath(TexturePath::Plant::grass[variation]);
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

            m_texturePainter->setTexture(m_texture);
            GameObject::setPainter(m_texturePainter);

        }

        ~Grass(){};

    protected:
        Texture *m_texture;
        TexturePainter *m_texturePainter;
    private:

};
#endif
