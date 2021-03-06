#include "block.h"

vector<Texture*> Block::m_textureList;
Block::Block(const Vector2u  &size)
    :   GameObject()
{
    GAME_OBJECT_BLOCK("Block()",profiler::colors::Gold);
    loadTextures();
    m_size = size;
    m_texturePainter    = new TexturePainter();
    m_collider          = new Collider();
    //m_texture           = new Texture();


    GameObject::addPainter(m_texturePainter);
    GameObject::setCollider(m_collider);
    //m_texturePainter->setOriginType(Origin::topLeft);
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
    m_collider          = new Collider();
    //m_texture        = new Texture();
    GameObject::addPainter(m_texturePainter);
    GameObject::setCollider(m_collider);
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

void Block::setPos(float x, float y)
{
    GameObject::setPos(x,y);
}
void Block::setPos(const Vector2f&pos)
{
    GameObject::setPos(pos);
}

void Block::setX(float x)
{
    GameObject::setX(x);
}
void Block::setY(float y)
{
    GameObject::setY(y);
}
/*
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
}*/
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
    //m_texture->loadTexture(path);
   // GameObject::setTexturePath(path);
   // GameObject::loadTexture();
   // GameObject::setTextureOnPainter();


}
void Block::setTexture(Texture *texture)
{
    m_texture = texture;
    m_texturePainter->setTexture(m_texture);
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
    m_collider->setShape(Shape::rect(boundingBox.getSize().x,boundingBox.getSize().y,Vector2f(boundingBox.getPos())));
   // m_collider->addHitbox(boundingBox);
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
            m_textureList[i]->setOriginType(Origin::topLeft);
        }
    }
}

