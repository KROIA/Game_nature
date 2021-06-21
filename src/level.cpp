#include "level.h"

// Engine object
PixelEngine         *Level::m_engine;
bool                 Level::m_levelBuilt;
PointU               Level::m_windowSize;
unsigned int         Level::m_mapWidth;

//========================================================
// Put your GameObject declarations here:
//ManagedGameObjectGroup      Level::m_objectList;

// Toggle stats on and off
Event               *Level::m_keyEvent_P;

// Toggle Hitbox of all objects in the list: hitboxObjectList
Event               *Level::m_keyEvent_H;
ManagedGameObjectGroup     *Level::m_terainGroup;
ManagedGameObjectGroup     *Level::m_hitboxObjectList;
bool                 Level::m_hitboxIsVisible;
Timer                Level::m_timer1;
Sheep               *Level::m_sheep;
Point                Level::m_windowMidlePoint;

ManagedGameObjectGroup     *Level::m_grassList;
unsigned int         Level::m_maxGrassAmount;

Level::Level(PointU windowSize, unsigned int mapWidth)
{
    m_windowSize    = windowSize;
    m_mapWidth      = mapWidth;
    m_levelBuilt    = false;
    setup();
}
Level::~Level()
{
    delete m_keyEvent_P;
    delete m_keyEvent_H;
    delete m_engine;
}

// Basic Functions for creating and deleting the level
void Level::setup()
{
    if(m_levelBuilt)
        return;
    setup_engine();
    setup_level();
    setup_keyEvent();
    m_levelBuilt = true;
}
// Setup for the engine
void Level::setup_engine()
{
    m_engine = new PixelEngine (PointU(m_mapWidth,double(m_mapWidth)*double(m_windowSize.getY())/double(m_windowSize.getX())),m_windowSize);

    m_engine->set_setting_checkEventInterval(1.0f/30.0f);
    m_engine->set_setting_gameTickInterval(1.0f/240.0f);
    m_engine->set_setting_displayInterval(1.0f/30.0f);

    m_engine->setUserTickLoop(Level::userTickLoop);
    m_engine->setUserDisplayLoop(Level::userDrawLoop);
    m_engine->setUserCheckEventLoop(Level::userEventLoop);
}
// Build all GameObjects and configures them
void Level::setup_level()
{

    // Generate random Blocks on Position ( 10 | 10 ) with the size of ( 5 x 4 ) blocks
    m_terainGroup = factory_terain(RectU(PointU(8,8),PointU(0,0)));

    m_windowMidlePoint= Point(m_engine->getMapSize().getX()/2,m_engine->getMapSize().getY()/2);
    m_sheep = new Sheep();
    m_sheep->setPos(m_windowMidlePoint);


    // Generate Grass
    m_maxGrassAmount    = m_terainGroup->size()*1.5;
    m_grassList         = new ManagedGameObjectGroup();
    regenerateGrassField();

    m_hitboxObjectList = new ManagedGameObjectGroup();
    m_hitboxObjectList->add(m_terainGroup);
    m_hitboxObjectList->add(m_sheep);
    m_hitboxObjectList->add(m_grassList);


    m_engine->addGameObject(m_sheep);
    m_engine->addGroup(m_grassList);
    m_engine->addGroup(m_terainGroup);
    m_engine->addGroup(m_hitboxObjectList);

    m_engine->setCollisionSingleInteraction(m_sheep,m_terainGroup);
    m_engine->setCollisionSingleInteraction(m_sheep,m_grassList);

    m_engine->setRenderLayer_BOTTOM(m_terainGroup);
    m_engine->setRenderLayer_TOP(m_sheep);


}
// Setup the keybindings for special keyEvents
void Level::setup_keyEvent()
{
    m_keyEvent_P = new Event(KEYBOARD_KEY_P);
    m_keyEvent_H = new Event(KEYBOARD_KEY_H);
}
void Level::cleanup()
{

}

// Mainloop for the engine
void Level::run()
{
    EASY_FUNCTION(profiler::colors::Green);
    m_engine->checkEvent();
    m_engine->tick();
    m_engine->display();
}
// Is used to chech if the window was closed
bool Level::engineIsActive()
{
    return m_engine->running();
}

// These functions will later be called from the engine
 // userEventLoop: Here you can handle your Events (KeyEvents).
void Level::userEventLoop(double tickInterval,unsigned long long tick)
{
    // Check for keyEvents
    m_keyEvent_P->checkEvent();
    m_keyEvent_H->checkEvent();

    if(m_keyEvent_P->isSinking())
    {
        // Toggle stats visualisation
        m_engine->display_stats(!m_engine->display_stats(),Color(0,0,0),Point(m_engine->getMapSize().getX()-16*22,5));
    }

    if(m_keyEvent_H->isSinking())
    {
        // Toggle hitbox visualisation
        m_hitboxIsVisible = !m_hitboxIsVisible;
        m_hitboxObjectList->setHitboxVisibility(m_hitboxIsVisible);
    }

    regenerateGrassField();
}

 // userTickLoop: Here you can manipulate the game.
void Level::userTickLoop(double tickInterval,unsigned long long tick)
{
    VectorF movingVec = VectorF(m_windowMidlePoint.getX(),m_windowMidlePoint.getY()) - VectorF(m_sheep->getPos().getX(),m_sheep->getPos().getY());
    if(movingVec.getLength() > 0)
    {
        m_sheep->setPos(m_windowMidlePoint);
        m_terainGroup->move(movingVec);
        m_grassList->move(movingVec);
    }
}

 // userDrawLoop: If you want to change something on the graphics, do it here.
 // You also can do this stuff in the userTickLoop but you may run the tickLoop faster
 // than you draw stuff, so you will waste performance.
void Level::userDrawLoop(double tickInterval,unsigned long long tick)
{
    if(m_timer1.start(0.1))
    {

    }
}


ManagedGameObjectGroup *Level::factory_terain(RectU area)
{
    Texture texture;
    texture.setOriginType(Texture::Origin::topLeft);
    texture.loadTexture(TexturePath::tearainMap);

   /* vector<vector<int>  >map
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,3,3,4,4,4,4,2},
        {1,1,1,1,1,1,1,1,1,1,0,0,4,4,4,2,2,2,2},
        {1,1,1,1,1,1,2,1,1,0,4,4,4,3,1,2,2,2,2},
        {1,1,1,1,1,2,2,2,1,4,4,0,0,0,1,1,0,0,0},
        {1,1,1,1,2,2,2,2,4,4,0,2,2,2,1,1,1,0,0},
        {1,1,1,1,1,1,2,2,4,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,2,2,4,4,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,2,2,4,4,4,4,2,1,1,1,1,1,1,1,1},
        {1,1,1,1,2,4,4,4,4,4,4,2,1,1,1,1,1,1,1},
        {1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };*/
    //qDebug() << "map: x: "<<map.size()<< " y: "<<map[0].size();
    PointU randomPos;
    if(area.getSize().getX() == 0 && area.getSize().getY() == 0)
    {
        randomPos.set(0,0);
        area.setSize(texture.getSize());
    }
    else if(texture.getSize().getY() < area.getSize().getY() || texture.getSize().getX() < area.getSize().getX())
    {
        area.setSize(texture.getSize().getX(),texture.getSize().getY());
        randomPos.set(0,0);
    }
    else
    {
        randomPos = PointU(PixelEngine::random(0,texture.getSize().getX()    - area.getSize().getX()),
                           PixelEngine::random(0,texture.getSize().getY()    - area.getSize().getY()));
    }

    ManagedGameObjectGroup *group = new ManagedGameObjectGroup();
    for(unsigned int x=0; x<area.getSize().getX(); x++)
    {
        for(unsigned int y=0; y<area.getSize().getY(); y++)
        {
            Block *block;
            Color color = texture.getColor(Point(randomPos.getX() + x,randomPos.getY() + y));

            if(colorInRange(color, Color(0,255,0,255)))
            {
                block = new GrassBlock();
            }else if(colorInRange(color, Color(127,127,127,255)))
            {
                block = new StoneBlock();
            }else if(colorInRange(color, Color(180 ,100, 75,255)))
            {
                block = new DirtBlock();
            }else if(colorInRange(color, Color(230,200,110,255))) // sand
            {
                block = new SandBlock();
            }else if(colorInRange(color, Color(0,0,255,255)))
            {
                block = new WaterBlock();
            }else
            {
                qDebug() << "not defined field on Map: "<<randomPos.getX() + x<< " "<<randomPos.getY() + y;
                block = new GrassBlock();
            }
          /*  switch()
            {
                case 0: block = new DirtBlock(); break;
                case 1: block = new GrassBlock(); break;
                case 2: block = new SandBlock(); break;
                case 3: block = new StoneBlock(); break;
                case 4: block = new WaterBlock(); break;
            }*/
            block->setPos(area.getPos().getX() + x*block->getSize().getX() ,area.getPos().getY() + y*block->getSize().getY() );
            group->add(block);
        }
    }
    return group;
}
void Level::regenerateGrassField()
{
    while(m_grassList->size() < m_maxGrassAmount)
    {
        //Grass *grass = new Grass();
        //Point randomPos(PixelEngine::random(0,200),PixelEngine::random(0,200));
        //bool grassGodToPlant = false;
        GameObjectGroup grassBlockGroup;
        for(size_t i=0; i<m_terainGroup->size(); i++)
        {
            if((*m_terainGroup)[i]->getProperty().getBody().material == Property::Material::Grass)
            {
                grassBlockGroup.add((*m_terainGroup)[i]);
            }
        }
        size_t randBlock = PixelEngine::random(0,grassBlockGroup.size()-1);

        // Get random generated Plant
        GameObject *plant;
        int randPlant = PixelEngine::random(0,100);
        if(randPlant > 80)
        {
            plant = new Flower(PixelEngine::random(0,TexturePath::Plant::flower.size()-1));
        }
        else
        {
            plant = new Grass(PixelEngine::random(0,TexturePath::Plant::grass.size()-1));
        }
        plant->setPos(grassBlockGroup[randBlock]->getPos());


        m_grassList->add(plant);
        //m_engine->
        //m_engine->setCollisionSingleInteraction(m_sheep,grass);
    }
}
bool Level::colorInRange(const Color &col1,const Color &col2,unsigned int range)
{
    int r1 = col1.r;
    int g1 = col1.g;
    int b1 = col1.b;
    int a1 = col1.a;

    int r2 = col2.r;
    int g2 = col2.g;
    int b2 = col2.b;
    int a2 = col2.a;

    if(abs(r1 - r2) <= range &&
       abs(g1 - g2) <= range &&
       abs(b1 - b2) <= range &&
       abs(a1 - a2) <= range)
        return true;
    return false;

}
