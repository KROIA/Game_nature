#include "block.h"

vector<Texture*> Block::m_textureList;
Block::Block(const Vector2u  &size)
    :   GameObject()
{
    loadTextures();
    m_size = size;
    m_texturePainter    = new TexturePainter();
    m_texture           = new Texture();

    m_texturePainter->setTexture(m_texture);
    GameObject::setPainter(m_texturePainter);
    //this->setup_collider();
}
Block::Block(const Vector2u  &size,
             const string &texturePath,
             const Property::Property &property)
    :   GameObject()
{
    loadTextures();
    m_size = size;
    m_texturePainter = new TexturePainter();
    m_texture        = new Texture();
    GameObject::setPainter(m_texturePainter);
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

void Block::setPos(int x, int y)
{
    GameObject::setPos(x,y);
}
void Block::setPos(const Vector2i&pos)
{
    GameObject::setPos(pos);
}

void Block::setX(int x)
{
    GameObject::setX(x);
}
void Block::setY(int y)
{
    GameObject::setY(y);
}

void Block::moveToPos(const Vector2i&destination,Controller::MovingMode mode)
{
    GameObject::moveToPos(destination,mode);
}
void Block::moveToPos(const int &x,const int &y,Controller::MovingMode mode)
{
    GameObject::moveToPos(x,y,mode);
}
void Block::move(const Vector2i&vec,Controller::MovingMode mode)
{
    GameObject::move(vec,mode);
}
void Block::move(const Vector2f &vec,Controller::MovingMode mode)
{
    GameObject::move(vec,mode);
}
void Block::move(const float &deltaX, const float &deltaY,Controller::MovingMode mode)
{
    GameObject::move(deltaX,deltaY,mode);
}
void Block::moveX(const float &delta,Controller::MovingMode mode)
{
    GameObject::moveX(delta,mode);
}
void Block::moveY(const float &delta,Controller::MovingMode mode)
{
    GameObject::moveY(delta,mode);
}
/*Vector2f Block::getPos() const
{
    return GameObject::getPos();
}*/
const Vector2f      &Block::getMovingVector() const
{
    return GameObject::getMovingVector();
}

const Vector2u  &Block::getSize()
{
    return m_size;
}

void Block::setTexturePath(const string &path)
{
    m_texture->loadTexture(path);
   // GameObject::setTexturePath(path);
   // GameObject::loadTexture();
   // GameObject::setTextureOnPainter();


}
void Block::setTexture(Texture *texture)
{
    *m_texture = *texture;
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
  //  GameObject::addHitbox(RectI(m_size.getX(),m_size.getY()));
    RectI boundingBox = RectI::getFrame(m_texture->getRects());
    GameObject::addHitbox(boundingBox);
}
void Block::loadTextures()
{
    if(m_textureList.size() == 0)
    {
        m_textureList.reserve(TexturePath::Block::block.size());
        for(size_t i=0; i<TexturePath::Block::block.size(); i++)
        {
            m_textureList.push_back(new Texture());
            m_textureList[i]->loadTexture(TexturePath::Block::block[i]);
        }
    }
}

