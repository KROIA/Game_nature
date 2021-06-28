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

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Vector2i&pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual void moveToPos(const Vector2i&destination,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveToPos(const int &x,const int &y,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2i&vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector2f &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const float &deltaX, const float &deltaY,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveX(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveY(const float &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        //virtual const Vector2i &getPos() const;
        virtual const Vector2f &getMovingVector() const;

        virtual const Vector2u  &getSize();

        virtual void setTexturePath(const string &path);

        virtual void setProperty(const Property::Property &property);
        virtual const Property::Property &getProperty() const;

    protected:
        virtual void setup_collider();

        Vector2u  m_size;
        Texture         *m_texture;
        TexturePainter  *m_texturePainter;
    private:

};
#endif // BLOCK_H
