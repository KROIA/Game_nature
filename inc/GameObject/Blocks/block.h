#ifndef BLOCK_H
#define BLOCK_H
#include "gameobject.h"
#include "texturePaths.h"
#include "texturePainter.h"

class Block     : public GameObject
{
    public:
        Block(const Vector2u  &size = Vector2u (16,16));
        Block(const Vector2u  &size,
              const string &texturePath,
              const Property::Property &property);
        Block(const Block &other);
        virtual ~Block();
        virtual const Block &operator=(const Block &other);

        virtual void setPos(float x, float y);
        virtual void setPos(const Vector2f& pos);

        virtual void setX(float x);
        virtual void setY(float y);

        virtual const Vector2f &getMovingVector() const;

        virtual const Vector2u  &getSize();

        virtual void setTexturePath(const string &path);
        virtual void setTexture(Texture *texture);

        virtual void setProperty(const Property::Property &property);
        virtual const Property::Property &getProperty() const;

    protected:
        virtual void setup_collider();
        virtual void loadTextures();

        Vector2u  m_size;
        Texture         *m_texture;
        TexturePainter  *m_texturePainter;
        Collider        *m_collider;
        static vector<Texture*> m_textureList;
    private:

};
#endif // BLOCK_H
