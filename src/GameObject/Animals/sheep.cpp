#include "sheep.h"

Sheep::Sheep()
    :   GameObject()
{
    m_texturePainter    = new TexturePainter();
#ifdef USE_ANIMATED_TEXTURE
    m_animatedTexture   = new AnimatedTexture();
    m_animatedTexture->setOriginType(Origin::middle);
    setTexturePathList(TexturePath::Animal::sheep);
    m_texturePainter->setTexture(m_animatedTexture);
    GameObject::setHitboxFromTexture(*m_animatedTexture);
#else
    m_texture           = new Texture();
    m_texture->setOriginType(Origin::middle);
    setTexturePathList(TexturePath::Animal::sheep);

    m_texturePainter->setTexture(m_texture);

    //m_collider->addHitbox(RectF(-20,-20,40,40));
    GameObject::setHitboxFromTexture(*m_texture);
#endif


    m_sensor            = new Sensor();
    m_controller        = new KeyController();

    m_eventLEFT         = new Event();
    m_eventRIGHT        = new Event();
    m_event_EAT         = new Event();
    m_eventToggleStats  = new Event();
    m_eventToggleColliderVisibility = new Event();
    m_eventToggleChunkVisibility    = new Event();

    m_propertyText         = new DisplayText();



    GameObject::setPainter(m_texturePainter);

    GameObject::addController(m_controller);

    m_propertyText->setVisibility(false);
    m_propertyText->setString("");
    m_propertyText->setCharacterSize(3);
    m_propertyText->setColor(Color(255,255,255,255)); // Transparent white
    m_propertyTextRelativePos = Vector2f(16,-50);
    m_propertyText->setPos(m_propertyTextRelativePos);

    GameObject::addText(m_propertyText);


    setKeyBinding(KEYBOARD_KEY_W, KEYBOARD_KEY_A,
                  KEYBOARD_KEY_S, KEYBOARD_KEY_D,
                  KEYBOARD_KEY_E, KEYBOARD_KEY_Q,
                  KEYBOARD_KEY_C, KEYBOARD_KEY_M);

    m_sensor->setOwner(this);
    Collider *sensorCollider = new Collider();
   // sensorCollider->addHitbox(RectI(-15,-19,30,6));
    sensorCollider->addHitbox(RectI(-4,-19,8,8));
    sensorCollider->updateBoundingBox();
    m_sensor->setSensorCollider(sensorCollider);
    setupProperty();


}
Sheep::Sheep(const Sheep &other)
    :   GameObject(other)
{
#ifdef USE_ANIMATED_TEXTURE
    m_animatedTexture   = new AnimatedTexture();
    *this->m_animatedTexture    = *other.m_animatedTexture;
    m_texturePainter->setTexture(m_animatedTexture);
    GameObject::setHitboxFromTexture(*m_animatedTexture);
#else
    m_texture           = new Texture();
    *this->m_texture    = *other.m_texture;
    m_texturePainter->setTexture(m_texture);
    GameObject::setHitboxFromTexture(*m_texture);
#endif
    m_sensor            = new Sensor();
    m_controller        = new KeyController();

    m_eventLEFT         = new Event();
    m_eventRIGHT        = new Event();
    m_event_EAT         = new Event();
    m_eventToggleStats  = new Event();
    m_eventToggleColliderVisibility = new Event();
    m_eventToggleChunkVisibility    = new Event();

    m_propertyText         = new DisplayText();
    m_texturePainter    = new TexturePainter();

    //

    *this->m_sensor             = *other.m_sensor;
    *this->m_controller         = *other.m_controller;
    *this->m_eventLEFT          = *other.m_eventLEFT;
    *this->m_eventRIGHT         = *other.m_eventRIGHT;
    *this->m_event_EAT          = *other.m_event_EAT;
    *this->m_eventToggleStats   = *other.m_eventToggleStats;
    *this->m_propertyText       = *other.m_propertyText;

    //GameObject::setTexture(m_animatedTexture);
   // GameObject::setTexture(m_texture);



    GameObject::setPainter(m_texturePainter);
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
    delete m_eventToggleColliderVisibility;
}

void Sheep::checkEvent()
{
    GameObject::checkEvent();
    m_eventLEFT->checkEvent();
    m_eventRIGHT->checkEvent();
    m_event_EAT->checkEvent();
    m_eventToggleStats->checkEvent();
    m_eventToggleColliderVisibility->checkEvent();
    m_eventToggleChunkVisibility->checkEvent();

    if(Vector::length(m_controller->getMovingVector()) > 0)
    {
        //qDebug() << "Moving";
        if(m_property.getBody().stamina > 0)
            m_property.setBody_stamina(m_property.getBody().stamina - 1);

        if(m_property.getBody().stamina < 10)
        {
            m_property.setBody_health(m_property.getBody().health - 2);

        }
       /* if(m_property.getBody().health <= 0)
        {
            GameObject::removeText(m_propertyText);
            GameObject::removeMeFromEngine();
            return;
        }*/
    }

    float deltaDeg = 5;
    if(m_eventLEFT->isPressed())
    {

        /*m_controller->setRotation(m_controller->getRotation()-deltaDeg);
#ifdef USE_ANIMATED_TEXTURE
        m_animatedTexture->selectBackward();
        GameObject::setHitboxFromTexture(*m_animatedTexture);
#else
        m_texturePainter->rotate(-deltaDeg);
#endif

        m_sensor->setRotation(m_controller->getRotation());*/
        this->rotate(-deltaDeg);
    }
    if(m_eventRIGHT->isPressed())
    {
        /*m_controller->setRotation(m_controller->getRotation()+deltaDeg);
        //m_texture->rotate(45);
#ifdef USE_ANIMATED_TEXTURE
        m_animatedTexture->selectForward();
        GameObject::setHitboxFromTexture(*m_animatedTexture);
#else
        m_texturePainter->rotate(deltaDeg);
#endif

        m_sensor->setRotation(m_controller->getRotation());*/
        this->rotate(deltaDeg);
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
                    float availableFood = p.getFood().foodAmount;
                    float deltaFood = 0.5;
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
                        detectedObjList[i]->removeMeFromEngine();

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
    if(m_eventToggleColliderVisibility->isSinking())
    {
        bool isVisible = !GameObject::isVisible_collider_hitbox();
        GameObject::setVisibility_collider_hitbox(isVisible);
        GameObject::setVisibility_collider_boundingBox(isVisible);
        GameObject::setVisibility_collider_collisionData(isVisible);
        GameObject::setVisibility_collider_isCollidingWith(isVisible);
        m_sensor->setVisibility_collider_boundingBox(isVisible);
    }


    // Chunk display:
    bool changeChunk = false;
    if(m_chunkIDList.size() != m_lastChunkIDList.size())
        changeChunk = true;
    else
    {
        for(size_t i=0; i<m_chunkIDList.size(); i++)
            if(m_chunkIDList[i] != m_lastChunkIDList[i])
            {
                changeChunk = true;
                break;
            }

    }
    if(changeChunk)
    {
        /*if(m_lastChunkID.isInChunkMap && m_eventToggleChunkVisibility->getCounter_isSinking() == 1)
        {
            GameObject::setVisibility_chunk(m_lastChunkID,false);
            GameObject::setVisibility_chunk(m_chunkID,true);
        }*/
        if(m_eventToggleChunkVisibility->getCounter_isSinking() == 1)
        {
            for(const ChunkID &id : m_lastChunkIDList)
                GameObject::setVisibility_chunk(id,false);
            for(const ChunkID &id : m_chunkIDList)
                GameObject::setVisibility_chunk(id,true);
        }
        m_lastChunkIDList = m_chunkIDList;
    }
    if(m_eventToggleChunkVisibility->isSinking())
    {

        switch(m_eventToggleChunkVisibility->getCounter_isSinking())
        {
            case 1:
                for(const ChunkID &id : m_chunkIDList)
                    GameObject::setVisibility_chunk(id,true);
            break;
            case 2:
                GameObject::setVisibility_chunks(true);
            break;
            case 3:
                GameObject::setVisibility_chunks(false);
                m_eventToggleChunkVisibility->resetCounter_isSinking();
            break;
        }
    }
}

/*void Sheep::tick(const Vector2i&direction)
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
        m_propertyText->setPos(Vector2f(m_layerItem.getPos()) + m_propertyTextRelativePos);
   // if(m_debugTimer.start)
}

void Sheep::setTexturePathList(const vector<string> &pathList)
{
#ifdef USE_ANIMATED_TEXTURE
    //m_animatedTexture->setOrigin(Point(8,8));
    for(const string &path : pathList)
    {
        m_animatedTexture->addTexture(path);
    }
    //m_animatedTexture->loadTexture();
#else
    m_texture->loadTexture(pathList[0]);
#endif
   // m_texturePainter->setTexture(m_animatedTexture);
  /*  if(pathList.size() != 0)
    {
        m_texture->setFilePath(pathList[0]);
        m_texture->loadTexture();
        m_texturePainter->setOriginType(Painter::Origin::middle);
        //m_texture->setOriginType(Texture::Origin::middle);
    }

    GameObject::setTextureOnPainter();
    GameObject::setHitboxFromTexture();*/


}
void Sheep::setKeyBinding(const int &UP_KEY,
                          const int &LEFT_KEY,
                          const int &DOWN_KEY,
                          const int &RIGHT_KEY,
                          const int &EAT_KEY,
                          const int &DISPLAY_PROPERTY_KEY,
                          const int &DISPLAY_COLLIDER_KEY,
                          const int &DISPLAY_CHUNK_KEY)
{
    m_controller->setKey_forMove_UP(UP_KEY);
   // m_controller->setKey_forMove_LEFT(m_keyLEFT);
   // m_controller->setKey_forMove_RIGHT(m_keyRIGHT);
    m_controller->setKey_forMove_DOWN(DOWN_KEY);

    m_eventLEFT->setKey(LEFT_KEY);
    m_eventRIGHT->setKey(RIGHT_KEY);
    m_event_EAT->setKey(EAT_KEY);
    m_eventToggleStats->setKey(DISPLAY_PROPERTY_KEY);
    m_eventToggleColliderVisibility->setKey(DISPLAY_COLLIDER_KEY);
    m_eventToggleChunkVisibility->setKey(DISPLAY_CHUNK_KEY);
}
void Sheep::event_hasCollision(vector<GameObject *> other)
{
    // Ignore collision with objects
    for(GameObject* &otherObj : other)
    {
        // The sheep can't swim
        if(otherObj->getProperty().getBody().material == Property::Material::Water)
            GameObject::event_hasCollision(other);

        if(otherObj->getProperty().getBody().material == Property::Material::Stone)
            GameObject::event_hasCollision(other);
    }

}
void Sheep::rotate(const float &deg)
{
    GameObject::rotate(deg);
    m_sensor->setRotation(GameObject::getRotation());
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
