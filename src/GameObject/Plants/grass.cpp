#include "grass.h"

Grass::Grass()
    :   GameObject()
{
    GameObject::setTexturePath(TexturePath::Plant::grass);
    GameObject::loadTexture();
    GameObject::setTextureOnPainter();
    GameObject::setHitboxFromTexture();

    m_property.setBody_material(Property::Material::Grass);
}

Grass::~Grass()
{

}
