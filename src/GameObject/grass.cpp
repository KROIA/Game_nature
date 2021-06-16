#include "grass.h"


Grass::Grass(const PointU &area)
    :   GameObject()
{
    setup(area);
}
Grass::Grass(const Grass &other)
    :   GameObject(other)
{
    setup(other.m_area);
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
   GameObject::operator=(other);
   return *this;
}

void Grass::checkEvent()
{
    GameObject::checkEvent();
}
void Grass::tick(const Point &direction)
{
    GameObject::tick(direction);
    m_property.setFood_foodAmout(m_property.getFood().foodAmount+0.1);
    if(m_property.getFood().foodAmount > 200)
        m_property.setFood_foodAmout(200);
}
void Grass::draw(PixelDisplay &display)
{
    if(m_grassChangeTimer.start(0.1))
    {
        unsigned int index = 0;
        for(unsigned int x=0; x<m_area.getX(); x++)
        {
            for(unsigned int y=0; y<m_area.getY(); y++)
            {
                Color col = m_painter->getPixel(index);
                double foodAmount = m_property.getFood().foodAmount;
                int delta = 10;

                double minR = col.g - foodAmount;
                double maxR = foodAmount + 50   - col.g;
                if(minR > delta)minR = delta;
                if(maxR > delta)maxR = delta;
                col.g += PixelEngine::random(-minR,maxR);
                //col.g = (sin((double)x/6.f) * cos((double)y/6.f) + 1) * foodAmount/2;
                m_painter->setPixelColor(index,col);



               /* //Color col = Color(0,PixelEngine::random(foodAmount,foodAmount+30),0);
                int newColorGreen = col.g + PixelEngine::random(-1,+1);
                if(newColorGreen < 1)
                    newColorGreen = 1;
                else if(newColorGreen > 255)
                    newColorGreen = 255;
                col.g = newColorGreen * foodAmount/100;
                m_painter->setPixelColor(index,col);*/

                index++;
            }
        }
    }
    GameObject::draw(display);
}

void Grass::setup(const PointU &area)
{
    m_painter   = new Painter();
    m_collider  = new Collider();
    m_area      = area;


    this->setPainter(m_painter);
    this->setCollider(m_collider);

    m_painter->reserve(m_area.getX() * m_area.getY());
    for(unsigned int x=0; x<m_area.getX(); x++)
    {
        for(unsigned int y=0; y<m_area.getY(); y++)
        {
            Pixel pix(Point(x,y),Color(0,PixelEngine::random(100,255),0,255));
            m_painter->addPixel(pix);
        }
    }
    m_collider->addHitbox(Rect(m_area.getX() , m_area.getY()));




    this->m_property.setType(Property::Type{.description = Property::Description::staticObstacle});
    this->m_property.setBody_material(Property::Material::Grass);
    this->m_property.setFood_isEatable(true);
    this->m_property.setFood_foodAmout(PixelEngine::random(100,255));
    this->m_property.setFood_healthyLevel(10);

}
