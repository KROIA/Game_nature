#include "sheep.h"

Sheep::Sheep()
    :   GameObject()
{
    m_tree              = new ObjectTree(AABB({0,0},{256,256}),1,10,0);
    m_tree->setAsRoot(true);

    m_treePainter       = new VertexPathPainter();
    m_texturePainter    = new TexturePainter();
#ifdef USE_ANIMATED_TEXTURE
    m_animatedTexture   = new AnimatedTexture();
    m_animatedTexture->setOriginType(Origin::center);
    setTexturePathList(TexturePath::Animal::sheep);
    m_texturePainter->setTexture(m_animatedTexture);
    GameObject::setHitboxFromTexture(*m_animatedTexture);
#else
    m_texture           = new Texture();
    m_collider          = new Collider();
    m_texture->setOriginType(Origin::center);
    setTexturePathList(TexturePath::Animal::sheep);

    m_texturePainter->setTexture(m_texture);
    m_texturePainter->setRenderLayer(RenderLayerIndex::layer_3);

    //m_collider->addHitbox(RectF(-80,5,80,30));
   // m_collider->setHitboxFromTexture(m_texture);
    m_collider->setShape(Shape::rect(20,40,{10,20,}));
#endif


    m_sensor            = new ShapeSensor();
    m_laserSensor       = new LaserSensor();

    m_controller        = new KeyController();
    m_mouseMoveController   = new MouseMoveController();
    m_controller->setActive(false);

    m_eventLEFT         = new KeyEvent();
    m_eventRIGHT        = new KeyEvent();
    m_event_EAT         = new KeyEvent();
    m_eventToggleStats  = new KeyEvent();
    m_eventToggleColliderVisibility = new KeyEvent();
    m_eventToggleChunkVisibility    = new KeyEvent();
    m_event_sprint      = new KeyEvent();
    m_mouseMoveEvent    = new MouseMoveEvent();
    m_mouseButtonEvent  = new MouseButtonEvent();

    m_propertyText         = new TextPainter();
}
Sheep::Sheep(const Sheep &other)
    :   GameObject(other)
{
    m_texturePainter    = new TexturePainter();
#ifdef USE_ANIMATED_TEXTURE
    m_animatedTexture   = new AnimatedTexture();
    *this->m_animatedTexture    = *other.m_animatedTexture;
    m_texturePainter->setTexture(m_animatedTexture);
    GameObject::setHitboxFromTexture(*m_animatedTexture);
#else
    m_texture           = new Texture();
    m_collider          = new Collider();
    *this->m_texture    = *other.m_texture;
    m_texturePainter->setTexture(m_texture);
    m_texturePainter->setRenderLayer(RenderLayerIndex::layer_3);

    m_collider->setHitboxFromTexture(m_texture);
#endif
    m_sensor            = new ShapeSensor();
    m_controller        = new KeyController();

    m_eventLEFT         = new KeyEvent();
    m_eventRIGHT        = new KeyEvent();
    m_event_EAT         = new KeyEvent();
    m_eventToggleStats  = new KeyEvent();
    m_eventToggleColliderVisibility = new KeyEvent();
    m_eventToggleChunkVisibility    = new KeyEvent();
    m_event_sprint      = new KeyEvent();

    m_propertyText      = new TextPainter();


    *this->m_sensor             = *other.m_sensor;
    *this->m_controller         = *other.m_controller;
    *this->m_eventLEFT          = *other.m_eventLEFT;
    *this->m_eventRIGHT         = *other.m_eventRIGHT;
    *this->m_event_EAT          = *other.m_event_EAT;
    *this->m_eventToggleStats   = *other.m_eventToggleStats;
    *this->m_propertyText       = *other.m_propertyText;
}
Sheep::~Sheep()
{
    GameObject::removePainter(m_propertyText);

    delete m_propertyText;
    delete m_sensor;
    delete m_eventLEFT;
    delete m_eventRIGHT;
    delete m_event_EAT;
    delete m_eventToggleStats;
    delete m_eventToggleColliderVisibility;
    delete m_event_sprint;
}

void Sheep::setup()
{
    m_propertyText->setVisibility(false);
    m_propertyText->setString("");
    m_propertyText->setCharacterSize(30);
    m_propertyText->setColor(Color(255,255,255,255)); // Transparent white
    m_propertyTextRelativePos = Vector2f(-160,500);
    //m_propertyTextRelativePos = Vector2f(10,0);
    m_propertyText->setOrigin(m_propertyTextRelativePos);



    setKeyBinding(KEYBOARD_KEY_W, KEYBOARD_KEY_A,
                  KEYBOARD_KEY_S, KEYBOARD_KEY_D,  KEYBOARD_KEY_SHIFT,
                  KEYBOARD_KEY_E, KEYBOARD_KEY_Q,
                  KEYBOARD_KEY_C, KEYBOARD_KEY_M);
    m_mouseButtonEvent->setButton(sf::Mouse::Button::Left);

    //m_sensor->setOwner(this);
    Shape sens = Shape::rect(8,8);
    sens.setOrigin({0,-16});
    m_sensor->setShape(sens);
    m_sensor->setVisibility(true);
    m_sensor->setVisibility_detectedObjects(true);

    m_laserSensor->addLaser(Vector2f(0, -16),25,-90);
    //m_laserSensor->addLaser(Vector2f(-1,-16),20,-135);
    //m_laserSensor->addLaser(Vector2f(1, -16),20,-45);

    setupProperty();
    m_cameraZoom = 0.2;

    m_controller->setStepSize(100);
    m_mouseMoveController->setStepSize(1);
    //m_mouseMoveController->setClipToCoursor(true);

    GameObject::addPainter(m_texturePainter);
    GameObject::addPainter(m_propertyText);
    //GameObject::addPainter(m_treePainter);
    //GameObject::addController(m_controller);
    GameObject::addController(m_mouseMoveController);
    GameObject::setCollider(m_collider);


    GameObject::addSensor(m_sensor);
    GameObject::addSensor(m_laserSensor);

    GameObject::addEvent(m_eventLEFT);
    GameObject::addEvent(m_eventRIGHT);
    GameObject::addEvent(m_event_EAT);
    GameObject::addEvent(m_eventToggleStats);
    GameObject::addEvent(m_eventToggleColliderVisibility);
    GameObject::addEvent(m_eventToggleChunkVisibility);
    GameObject::addEvent(m_event_sprint);
    GameObject::addEvent(m_mouseMoveEvent);
    GameObject::addEvent(m_mouseButtonEvent);
   // m_tree->insert(this);

}
void Sheep::checkEvent(float deltaTime)
{
    //this->setPos(m_mouseMoveEvent->getPos());
    if(Vector::length(GameObject::getMovingVector()) > 0)
    {
        //qDebug() << "Moving";
        float length = Vector::length(GameObject::getMovingVector());
        if(m_property.getBody().stamina > 0)
            m_property.setBody_stamina(m_property.getBody().stamina - 0.1*length);

        if(m_property.getBody().stamina < 10)
        {
            m_property.setBody_health(m_property.getBody().health - 0.1*length);

        }
       /* if(m_property.getBody().health <= 0)
        {
            GameObject::removeText(m_propertyText);
            GameObject::removeMeFromEngine();
            return;
        }*/
    }

    float deltaDeg = 360 * GameObject::getEngine_deltaTime();
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

                    qDebug()<<p.getFood().foodAmount;
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
        bool isVisible = !GameObject::getColliderPainter()->isVisible_boundingBox();
        GameObject::getColliderPainter()->setVisibility_hitBox(isVisible);
        GameObject::getColliderPainter()->setVisibility_boundingBox(isVisible);
        GameObject::getColliderPainter()->setVisibility_collisionData(isVisible);
        GameObject::getColliderPainter()->setVisibility_collidedObjects_boundingBox(isVisible);
        GameObject::getColliderPainter()->setVisibility_collidedObjects_hitBox(isVisible);
        GameObject::setVisibility_colliderSearchRect(isVisible);
       // m_sensor->setVisibility_collider_boundingBox(isVisible);
    }

    if(m_eventToggleChunkVisibility->isSinking())
    {
        GameObject::setVisibility_objectTree(!GameObject::isVisible_objectTree());
        m_treePainter->setVisibility(!m_treePainter->isVisible());
    }
    if(m_event_sprint->isSinking())
    {
        m_controller->setStepSize(m_controller->getStepSize()*2);
    }
    if(m_event_sprint->isRising())
    {
        m_controller->setStepSize(m_controller->getStepSize()/2);
    }
}

/*void Sheep::tick(const Vector2i&direction)
{
    GameObject::tick(direction);
}*/
void Sheep::postTick()
{
    if(m_slowTimer.start(0.5))
    {
        updatePropertyText();
    }
    if(m_propertyText->isVisible())
        m_propertyText->setPos(Vector2f(m_pos) + m_propertyTextRelativePos);

    GameObject::display_setCameraPos(m_pos);
   // m_cameraZoom = (0.98*m_cameraZoom) + 0.02 * (Vector::length(m_movingVector)*1+0.2);
   // GameObject::display_setCameraZoom(m_cameraZoom);
}
void Sheep::preDraw()
{
    //m_treePainter->clear();
    //vector<VertexPath*> list;
    //m_tree->getDrawable(list);
    //m_treePainter->addPath(list);
    //qDebug() << "delta T:"<<GameObject::getEngine_deltaTime();
}
/*unsigned int Sheep::checkCollision(const vector<GameObject*> &other)
{
    unsigned int collisionAmount = GameObject::checkCollision(other);
   // m_sensor->detectObjects(other);
    return collisionAmount;
}*/
/*void Sheep::draw(PixelDisplay &display)
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
}*/

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
        m_texturePainter->setOriginType(SpritePainter::Origin::center);
        //m_texture->setOriginType(Texture::Origin::center);
    }

    GameObject::setTextureOnPainter();
    GameObject::setHitboxFromTexture();*/


}
void Sheep::setKeyBinding(const int &UP_KEY,
                          const int &LEFT_KEY,
                          const int &DOWN_KEY,
                          const int &RIGHT_KEY,
                          const int &SPRINT_KEY,
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
    m_event_sprint->setKey(SPRINT_KEY);
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
