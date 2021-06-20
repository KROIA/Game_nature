#include "sheep.h"

Sheep::Sheep()
    :   GameObject()
{
    m_animatedTexture   = new AnimatedTexture();
    m_sensor            = new Sensor();
    m_controller        = new KeyController();

    m_eventLEFT         = new Event();
    m_eventRIGHT        = new Event();
    m_event_EAT         = new Event();
    m_eventToggleStats  = new Event();

    m_propertyText         = new DisplayText();

    GameObject::setTexture(m_animatedTexture);
    GameObject::addController(m_controller);

    m_propertyText->setVisibility(false);
    m_propertyText->setString("");
    m_propertyText->setCharacterSize(40); // in pixels, not points!
    m_propertyText->setColor(Color(255,255,255,255)); // Transparent white
    m_propertyTextRelativePos.set(16,-90);
    m_propertyText->setPos(m_propertyTextRelativePos);

    GameObject::addText(m_propertyText);

    setTexturePathList(TexturePath::Animal::sheep);
    setKeyBinding(KEYBOARD_KEY_W, KEYBOARD_KEY_A,
                  KEYBOARD_KEY_S, KEYBOARD_KEY_D,
                  KEYBOARD_KEY_E, KEYBOARD_KEY_Q);

    m_sensor->setOwner(this);
    Collider *sensorCollider = new Collider();
    sensorCollider->addHitbox(Rect(-4,-19,8,6));
    sensorCollider->updateBoundingBox();
    m_sensor->setSensorCollider(sensorCollider);
    setupProperty();
}
Sheep::Sheep(const Sheep &other)
    :   GameObject(other)
{
    m_animatedTexture   = new AnimatedTexture();
    m_sensor            = new Sensor();
    m_controller        = new KeyController();

    m_eventLEFT         = new Event();
    m_eventRIGHT        = new Event();
    m_event_EAT         = new Event();
    m_eventToggleStats  = new Event();

    m_propertyText         = new DisplayText();

    *this->m_animatedTexture    = *other.m_animatedTexture;
    *this->m_sensor             = *other.m_sensor;
    *this->m_controller         = *other.m_controller;
    *this->m_eventLEFT          = *other.m_eventLEFT;
    *this->m_eventRIGHT         = *other.m_eventRIGHT;
    *this->m_event_EAT          = *other.m_event_EAT;
    *this->m_eventToggleStats   = *other.m_eventToggleStats;
    *this->m_propertyText          = *other.m_propertyText;

    GameObject::setTexture(m_animatedTexture);
    GameObject::clearController();
    GameObject::addController(m_controller);
    GameObject::addText(m_propertyText);
}
Sheep::~Sheep()
{
    GameObject::removeText(m_propertyText);

    delete m_propertyText;
    delete m_sensor;
    delete m_eventLEFT;
    delete m_eventRIGHT;
    delete m_event_EAT;
    delete m_eventToggleStats;
}

void Sheep::checkEvent()
{
    GameObject::checkEvent();
    m_eventLEFT->checkEvent();
    m_eventRIGHT->checkEvent();
    m_event_EAT->checkEvent();
    m_eventToggleStats->checkEvent();

    if(m_controller->getMovingVector().getLength() > 0)
    {
        //qDebug() << "Moving";
        if(m_property.getBody().stamina > 0)
            m_property.setBody_stamina(m_property.getBody().stamina - 1);

        if(m_property.getBody().stamina < 10)
        {
            m_property.setBody_health(m_property.getBody().health - 2);

        }
        if(m_property.getBody().health <= 0)
        {
            GameObject::removeText(m_propertyText);
            GameObject::removeMeFromEngine();
            return;
        }
    }

    if(m_eventLEFT->isSinking())
    {
        m_controller->setRotation(m_controller->getRotation()-45);
        m_animatedTexture->selectBackward();
        m_sensor->setRotation(m_controller->getRotation());
    }
    if(m_eventRIGHT->isSinking())
    {
        m_controller->setRotation(m_controller->getRotation()+45);
        m_animatedTexture->selectForward();
        m_sensor->setRotation(m_controller->getRotation());
    }

    if(m_event_EAT->isSinking())
    {

        vector<GameObject*>detectedObjList  = m_sensor->getDetectedObjects();
        if(detectedObjList.size()>0)
        {
            qDebug()<<"Sheep sensor detects "<<detectedObjList.size()<<" objects";
            for(size_t i=0; i<detectedObjList.size(); i++)
            {
                Property::Property p = detectedObjList[i]->getProperty();
                if(p.getBody().material == Property::Material::Grass &&
                   p.getFood().isEatable &&
                   p.getFood().foodAmount > 0)
                {
                    // Eat some grass
                    Property::Property sheepProperty = getProperty();
                    double availableFood = p.getFood().foodAmount;
                    double deltaFood = 0.5;
                    if(availableFood < deltaFood)
                        deltaFood = availableFood;

                    sheepProperty.setBody_stamina(sheepProperty.getBody().stamina + deltaFood*3);
                    sheepProperty.setBody_strength(sheepProperty.getBody().strength + deltaFood*2);
                    sheepProperty.setMood_stresslevel(sheepProperty.getMood().stresslevel * 0.8);
                    sheepProperty.setMood_angrylevel(sheepProperty.getMood().angrylevel * 0.9);
                    sheepProperty.setBody_weight(sheepProperty.getBody().weight + deltaFood * 0.1);
                    sheepProperty.setBody_health(sheepProperty.getBody().health + deltaFood * 0.5);

                    p.setFood_foodAmout(availableFood - deltaFood);
                    this->setProperty(sheepProperty);
                    detectedObjList[i]->setProperty(p);

                    if(p.getFood().foodAmount < 0.01)
                        detectedObjList[i]->deleteMeFromEngine();

                    //qDebug() << sheepProperty.toString().c_str();
                    //qDebug() << p.toString().c_str();
                }
               /* else if(p.getBody().material == Property::Material::Grass)
                {
                    detectedObjList[i]->deleteMeFromEngine();
                    m_propertyText->setString("Grass Essen");
                }*/

            }

        }
    }

    if(m_eventToggleStats->isSinking())
    {
        m_propertyText->setVisibility(!m_propertyText->isVisible());
    }
}

/*void Sheep::tick(const Point &direction)
{
    GameObject::tick(direction);
}*/
unsigned int Sheep::checkCollision(const vector<GameObject*> &other)
{
    unsigned int collisionAmount = GameObject::checkCollision(other);
    m_sensor->checkCollision(other);
    return collisionAmount;
}
void Sheep::draw(PixelDisplay &display)
{
    if(m_slowTimer.start(0.5))
    {
        updatePropertyText();
        //m_property.setMood_stresslevel(100-m_property.getBody().health);
    }
    GameObject::draw(display);
    m_sensor->draw(display);
    if(m_propertyText->isVisible())
        m_propertyText->setPos(Vector(m_layerItem.getPos()) + m_propertyTextRelativePos);
   // if(m_debugTimer.start)
}

void Sheep::setTexturePathList(const vector<string> &pathList)
{
    m_animatedTexture->setOrigin(Point(8,8));
    for(const string &path : pathList)
    {
        m_animatedTexture->addTexture(path);
    }
    m_animatedTexture->loadTexture();

    GameObject::setTextureOnPainter();
    GameObject::setHitboxFromTexture();

}
void Sheep::setKeyBinding(const int &UP_KEY,
                          const int &LEFT_KEY,
                          const int &DOWN_KEY,
                          const int &RIGHT_KEY,
                          const int &EAT_KEY,
                          const int &DISPLAY_PROPERTY_KEY)
{
    m_controller->setKey_forMove_UP(UP_KEY);
   // m_controller->setKey_forMove_LEFT(m_keyLEFT);
   // m_controller->setKey_forMove_RIGHT(m_keyRIGHT);
    m_controller->setKey_forMove_DOWN(DOWN_KEY);

    m_eventLEFT->setKey(LEFT_KEY);
    m_eventRIGHT->setKey(RIGHT_KEY);
    m_event_EAT->setKey(EAT_KEY);
    m_eventToggleStats->setKey(DISPLAY_PROPERTY_KEY);
}
void Sheep::event_hasCollision(vector<GameObject *> other)
{
    // Ignore collision with objects
    for(GameObject* &otherObj : other)
    {
        // The sheep can't swim
        if(otherObj->getProperty().getBody().material == Property::Material::Water)
            GameObject::event_hasCollision(other);
    }

}
void Sheep::setupProperty()
{
    Property::Property p;
    p.setType_description(Property::Description::player);
    Property::Body body;
    Property::Food food;
    Property::Mood mood;

    body.fat = 10;
    body.nutritionalValue = 15;
    body.stamina    = 100;
    body.health     = 100;
    body.strength   = 100;
    body.weight     = 30;
    body.density    = 0.8;
    body.material   = Property::Material::Flesh;

    food.isEatable  = true;
    food.foodAmount = 10;
    food.taste.push_back(Property::Food::Taste::sweet);
    food.healthyLevel   = 10;

    mood.stresslevel = 0;
    mood.angrylevel  = 0;
    mood.inLove      = 0;
    mood.druglevel   = 0;

    p.setBody(body);
    p.setFood(food);
    p.setMood(mood);
    this->setProperty(p);
}
void Sheep::updatePropertyText()
{
    /*string text =
           "body.fat:              "
           "body.nutritionalValue: "
           "body.stamina:          "
           "body.health:           "
           "body.strength:         "
           "body.weight:           "
           "body.density:          "

           "food.isEatable:        "
           "food.foodAmount:       "
           "food.healthyLevel:     "

*/
    string str = m_property.toString();
    m_propertyText->setText(str);


}
