#include "block.h"

Block::Block(const PointU &size)
    :   GameObject()
{
    m_size = size;
    //this->setup_collider();
}
Block::Block(const PointU &size,
             const string &texturePath,
             const Property::Property &property)
    :   GameObject()
{
    m_size = size;
    this->setTexturePath(texturePath);
    this->setProperty(property);
    this->setup_collider();
}
Block::Block(const Block &other)
    :   GameObject()
{
    this->operator=(other);
}
Block::~Block()
{

}
const Block &Block::operator=(const Block &other)
{
    GameObject::operator=(other);
    this->m_size    = other.m_size;
    return *this;
}

void Block::setPos(const int &x,const int &y)
{
    GameObject::setPos(x,y);
}
void Block::setPos(const Point &pos)
{
    GameObject::setPos(pos);
}

void Block::setX(const int &x)
{
    GameObject::setX(x);
}
void Block::setY(const int &y)
{
    GameObject::setY(y);
}

void Block::moveToPos(const Point &destination,Controller::MovingMode mode)
{
    GameObject::moveToPos(destination,mode);
}
void Block::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    GameObject::moveToPos(x,y,mode);
}
void Block::move(const Vector &vec,Controller::MovingMode mode)
{
    GameObject::move(vec,mode);
}
void Block::move(const VectorF &vec,Controller::MovingMode mode)
{
    GameObject::move(vec,mode);
}
void Block::move(const double &deltaX, const double &deltaY,Controller::MovingMode mode)
{
    GameObject::move(deltaX,deltaY,mode);
}
void Block::moveX(const double &delta,Controller::MovingMode mode)
{
    GameObject::moveX(delta,mode);
}
void Block::moveY(const double &delta,Controller::MovingMode mode)
{
    GameObject::moveY(delta,mode);
}
const Point Block::getPos() const
{
    return GameObject::getPos();
}
const VectorF      &Block::getMovingVector() const
{
    return GameObject::getMovingVector();
}

const PointU &Block::getSize()
{
    return m_size;
}

void Block::setTexturePath(const string &path)
{
    GameObject::setTexturePath(path);
    GameObject::loadTexture();
    GameObject::setTextureOnPainter();


}

void Block::setProperty(const Property::Property &property)
{
    GameObject::setProperty(property);
}
const Property::Property &Block::getProperty() const
{
    return GameObject::getProperty();
}


/*void Block::setup_property()
{

}*/
void Block::setup_collider()
{
  //  GameObject::addHitbox(Rect(m_size.getX(),m_size.getY()));
    Rect boundingBox = Rect::getFrame(m_texture->getRects());
    GameObject::addHitbox(boundingBox);
}

