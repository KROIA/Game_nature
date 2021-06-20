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
    m_engine->set_setting_gameTickInterval(1.0f/120.0f);
    m_engine->set_setting_displayInterval(1.0f/60.0f);

    m_engine->setUserTickLoop(Level::userTickLoop);
    m_engine->setUserDisplayLoop(Level::userDrawLoop);
    m_engine->setUserCheckEventLoop(Level::userEventLoop);
}
// Build all GameObjects and configures them
void Level::setup_level()
{
    m_sheep = new Sheep();
    m_sheep->setPos(0,0);


    // Generate Grass
    m_maxGrassAmount    = 10;
    m_grassList         = new ManagedGameObjectGroup();
    regenerateGrassField();

    // Generate random Blocks on Position ( 10 | 10 ) with the size of ( 5 x 4 ) blocks
    m_terainGroup = factory_terain(RectU(PointU(10,10),PointU(19,11)));



    m_hitboxObjectList = new ManagedGameObjectGroup();
    m_hitboxObjectList->add(m_terainGroup);
    m_hitboxObjectList->add(m_sheep);
    m_hitboxObjectList->add(m_grassList);


    m_engine->addGameObject(m_sheep);
    m_engine->addGroup(m_grassList);
    m_engine->addGroup(m_terainGroup);
    m_engine->addGroup(m_hitboxObjectList);

    m_engine->setCollisionSingleInteraction(m_sheep,m_grassList);

    m_engine->setRenderLayer_BOTTOM(m_terainGroup);


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
        m_engine->display_stats(!m_engine->display_stats(),Color(255,200,0),Point(m_windowSize.getX()-800,20));

        DirtBlock *block = new DirtBlock();
        block->setPos(PixelEngine::random(0,100),PixelEngine::random(0,100));
        m_terainGroup->add(block);
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
    vector<vector<int>  >map
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
    };
    //qDebug() << "map: x: "<<map.size()<< " y: "<<map[0].size();
    PointU randomPos;
    if(map.size() < area.getSize().getY() || map[0].size() < area.getSize().getX())
    {
        area.setSize(map.size(),map[0].size());
        randomPos.set(0,0);
    }
    else
    {
        randomPos = PointU(PixelEngine::random(0,map.size()    - area.getSize().getY()),
                           PixelEngine::random(0,map[0].size() - area.getSize().getX()));
    }

    ManagedGameObjectGroup *group = new ManagedGameObjectGroup();
    for(unsigned int x=0; x<area.getSize().getX(); x++)
    {
        for(unsigned int y=0; y<area.getSize().getY(); y++)
        {
            Block *block;
            switch(map[randomPos.getY() + y][randomPos.getX() + x])
            {
                case 0: block = new DirtBlock(); break;
                case 1: block = new GrassBlock(); break;
                case 2: block = new SandBlock(); break;
                case 3: block = new StoneBlock(); break;
                case 4: block = new WaterBlock(); break;
            }
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
        Grass *grass = new Grass();
        grass->setPos(PixelEngine::random(0,200),PixelEngine::random(0,200));


        m_grassList->add(grass);
        //m_engine->
        //m_engine->setCollisionSingleInteraction(m_sheep,grass);
    }
}

