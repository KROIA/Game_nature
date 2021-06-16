#include "grass.h"


Grass::Grass()
    :   GameObject()
{
    setup();
}
Grass::Grass(const Grass &other)
    :   GameObject(other)
{
    setup();
}
/*Grass::Grass( Controller *controller,
              Collider   *collider,
              Painter    *painter)
    :   GameObject(controller, collider, painter)
{

}*/
Grass::~Grass()
{

}
const Grass &Grass::operator=(const Grass &other)
{

}

void Grass::checkEvent()
{

}
void Grass::tick(const Point &direction)
{

}
void Grass::draw(PixelDisplay &display)
{
    if(m_grassChangeTimer.start(0.1))
    {
        unsigned int grassSize = 16;
        unsigned int index = 0;
        for(unsigned int x=0; x<grassSize; x++)
        {
            for(unsigned int y=0; y<grassSize; y++)
            {
                Color col = m_painter->getPixel(index);


                double minR = col.g - 100;
                double maxR = 255   - col.g;
                if(minR > 10)minR = 10;
                if(maxR > 10)maxR = 10;
                col.g += PixelEngine::random(-minR,maxR);
                m_painter->setPixelColor(index,col);
                index++;
            }
        }
    }
    GameObject::draw(display);
}

void Grass::setup()
{
    m_painter   = new Painter();
    m_collider  = new Collider();

    this->setPainter(m_painter);
    this->setCollider(m_collider);

    unsigned int grassSize = 16;

    m_painter->reserve(grassSize);
    for(unsigned int x=0; x<grassSize; x++)
    {
        for(unsigned int y=0; y<grassSize; y++)
        {
            Pixel pix(Point(x,y),Color(0,PixelEngine::random(100,255),0,255));
            m_painter->addPixel(pix);
        }
    }
    m_collider->addHitbox(Rect(grassSize,grassSize));

    this->setPos(100,100);


    this->m_property.setType(Property::Type{.description = Property::Description::staticObstacle});
    this->m_property.setBody_material(Property::Material::Grass);
    this->m_property.setFood_isEatable(true);
    this->m_property.setFood_foodAmout(PixelEngine::random(10,30));
    this->m_property.setFood_healthyLevel(10);

}
