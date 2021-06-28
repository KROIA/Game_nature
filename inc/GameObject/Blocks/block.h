#ifndef BLOCK_H
#define BLOCK_H
#include "gameobject.h"
#include "texturePaths.h"
#include "texturePainter.h"

class Block     : public GameObject
{
    public:
        Block(const PointU &size = PointU(16,16));
        Block(const PointU &size,
              const string &texturePath,
              const Property::Property &property);
        Block(const Block &other);
        virtual ~Block();
        virtual const Block &operator=(const Block &other);

        virtual void setPos(const int &x,const int &y);
        virtual void setPos(const Point &pos);

        virtual void setX(const int &x);
        virtual void setY(const int &y);

        virtual void moveToPos(const Point &destination,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveToPos(const int &x,const int &y,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const Vector &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const VectorF &vec,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void move(const double &deltaX, const double &deltaY,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveX(const double &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual void moveY(const double &delta,Controller::MovingMode mode = Controller::MovingMode::add);
        virtual const Point getPos() const;
        virtual const VectorF      &getMovingVector() const;

        virtual const PointU &getSize();

        virtual void setTexturePath(const string &path);

        virtual void setProperty(const Property::Property &property);
        virtual const Property::Property &getProperty() const;

    protected:
        virtual void setup_collider();

        PointU m_size;
        Texture         *m_texture;
        TexturePainter  *m_texturePainter;
    private:

};
#endif // BLOCK_H
