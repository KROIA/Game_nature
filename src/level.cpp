#include "level.h"
//#define GLOBALVIEW
//#define CLEAR_LEVEL

// Engine object
PixelEngine         *Level::m_engine;
bool                 Level::m_levelBuilt;
Vector2u                Level::m_windowSize;
unsigned int         Level::m_mapWidth;

//========================================================
// Put your GameObject declarations here:
//ManagedGameObjectGroup      Level::m_objectList;

// Toggle stats on and off
KeyEvent            *Level::m_keyEvent_P;

// Toggle Hitbox of all objects in the list: hitboxObjectList
KeyEvent            *Level::m_keyEvent_H;
GameObjectGroup     *Level::m_terainGroup;
GameObjectGroup     *Level::m_hitboxObjectList;
bool                 Level::m_visibility_collider_hitbox;
Timer                Level::m_timer1;
Sheep               *Level::m_sheep;
Vector2i             Level::m_windowMidlePoint;

GameObjectGroup     *Level::m_grassList;
unsigned int         Level::m_maxGrassAmount;
std::unordered_map<std::pair<int, int>, bool, Level::hash_pair> Level::m_generatedMap;
RectI Level::m_generatedMapRect;
int Level::m_mapGeneratorX = -16*500;
int Level::m_mapGeneratorY = -16*500;
Timer Level::m_chunkGenTimer;
FastNoiseLite Level::noise;


// TESTS
PixelPainter *Level::m_pixPainter;
GameObject   *Level::m_testObj;

Level::Level(Vector2u  windowSize, unsigned int mapWidth)
{
    m_windowSize    = windowSize;
    m_mapWidth      = mapWidth;
    m_levelBuilt    = false;

    PixelEngine::Settings settings = PixelEngine::getSettings();
    settings.display.windowSize = m_windowSize;
    settings.display.pixelMapSize = Vector2u (m_mapWidth,float(m_mapWidth)*float(m_windowSize.y)/float(m_windowSize.x));
    settings.gameObject.objectTree.maxObjects = 128;
    settings.gameObject.objectTree.boundry = AABB({-1,-1},{256,256});
  //  settings.gameObject.objectTree.boundry = RectF(-32,-32,256,256);
    //settings.gameObject.chunkMap.chunk.size = Vector2u(128,128);
    //settings.gameObject.chunkMap.chunkMapSize = settings.gameObject.chunkMap.chunk.size * 16u;
    //settings.gameObject.chunkMap.position = -Vector2i(settings.gameObject.chunkMap.chunk.size) * 8;
    //settings.gameObject.chunkMap.position = -Vector2i(settings.gameObject.chunkMap.chunk.size);
    PixelEngine::setSettings(settings);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);


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
    qDebug() << "setup_engine";
    m_engine = new PixelEngine();

    bool synced = true;

    if(synced)
    {
        m_engine->set_setting_syncEngineInterval(0.02);
        m_engine->set_setting_runInSync(true);
    }
    else
    {
        m_engine->set_setting_checkEventInterval(1.0f/3.0f);
        m_engine->set_setting_gameTickInterval(1.0f/1.0f);
        m_engine->set_setting_displayInterval(1.0f/6.0f);
        m_engine->set_setting_runInSync(false);
    }


    m_engine->setUserTickLoop(Level::userTickLoop);
    m_engine->setUserDisplayLoop(Level::userDrawLoop);
    m_engine->setUserCheckEventLoop(Level::userEventLoop);
    qDebug() << "setup_engine done";
}
// Build all GameObjects and configures them
void Level::setup_level()
{
    qDebug() << "setup_level";
    // TESTS

   /* m_pixPainter = new PixelPainter();
    Color col(255,0,0);
    Vector2u  size(31,31);
    m_pixPainter->resize(size);
    for(unsigned int x=0; x<size.getX(); x++)
    {
        m_pixPainter->addPixel(x,size.getY()/2,col);
        if(x%2==0)
            m_pixPainter->addPixel(x,size.getY()/2+1,col);
        if(x%4==0)
            m_pixPainter->addPixel(x,size.getY()/2+2,col);
        if(x%8==0)
            m_pixPainter->addPixel(x,size.getY()/2+3,col);
    }
    for(unsigned int y=0; y<size.getY(); y++)
    {
        m_pixPainter->addPixel(size.getX()/2,y,col);
        if(y%2==0)
            m_pixPainter->addPixel(size.getX()/2+1,y,col);
        if(y%4==0)
            m_pixPainter->addPixel(size.getX()/2+2,y,col);
        if(y%8==0)
            m_pixPainter->addPixel(size.getX()/2+3,y,col);
    }
    m_pixPainter->addPixel(size.getX()/2,size.getY()/2,Color(100,255,0));
    m_testObj = new GameObject();
    m_pixPainter->setOriginType(SpritePainter::Origin::center);
    m_testObj->setPainter(m_pixPainter);
    m_testObj->setPos(30,30);

    GameObject *m_testObj2 = new GameObject();
    PixelPainter *p2 = new PixelPainter();
    p2 = m_pixPainter;
    p2->setOrigin(Vector2f(0,0));
    m_testObj2->setPainter(p2);*/

   /* */






#ifndef CLEAR_LEVEL
    // Generate random Blocks on Position ( 10 | 10 ) with the size of ( 5 x 4 ) blocks
    //m_terainGroup = factory_terain(RectU(Vector2u (0,0),Vector2u (0,0)));



    m_windowMidlePoint= Vector2i(m_engine->getMapSize().x/2,m_engine->getMapSize().y/2);
    m_sheep = new Sheep();
    m_sheep->setPos(Vector2f(150,50));
#ifdef GLOBALVIEW
    m_sheep->setPos(m_windowMidlePoint);
#endif
    // Generate Grass
    m_maxGrassAmount    = 1;//m_terainGroup->size()*1.5;
    m_terainGroup       = new GameObjectGroup();
    m_grassList         = new GameObjectGroup();
    qDebug() << "regenerateGrassField: size: "<<m_maxGrassAmount;
   // regenerateGrassField();
    qDebug() << "regenerateGrassField done";

    m_hitboxObjectList = new GameObjectGroup();

    terainGenerator(m_engine,RectI(0,0,10*16,10*16));
#else
    m_hitboxObjectList = new GameObjectGroup();
    m_windowMidlePoint= Vector2i(m_engine->getMapSize().x/2,m_engine->getMapSize().y/2);
    m_sheep = new Sheep();
    m_sheep->setPosInitial(Vector2f(150,50));
#ifdef GLOBALVIEW
    m_sheep->setPos(m_windowMidlePoint);
#endif

    GameObject *obsticle = new GameObject();
    TexturePainter *obsticleTexturePainter = new TexturePainter();
    Texture *obsticleTexture = new Texture();
    obsticleTexture->setOriginType(Origin::center);
    obsticleTexture->loadTexture(TexturePath::Block::stone);
    //obsticleTexturePainter->setOriginType(Origin::topLeft);
    obsticleTexturePainter->setTexture(obsticleTexture);

    Collider *obsticleCollider = new Collider();
    Shape hitB = Shape::rect(16,16);
    hitB.setStatic(false);
    obsticleCollider->setShape(hitB);
    obsticleCollider->updateBoundingBox();
    obsticle->setCollider(obsticleCollider);
    obsticle->addPainter(obsticleTexturePainter);
    obsticle->setPosInitial(Vector2f(50,50));
    Property::Property p;
    p.setBody_material(Property::Material::Stone);
    obsticle->setProperty(p);
    obsticle->getColliderPainter()->setVisibility_hitBox(true);

#endif



#ifndef CLEAR_LEVEL
    //m_hitboxObjectList->add(m_terainGroup);
    qDebug() << "add to m_hitboxObjectList";
    m_hitboxObjectList->add(m_grassList);
    //m_hitboxObjectList->add(m_sheep);
#else
    m_hitboxObjectList->add(m_sheep);

#endif


#ifndef CLEAR_LEVEL
    qDebug() << "add to engine";

    m_engine->addGameObject(m_sheep);
    m_engine->addGameObject(m_terainGroup);
    m_engine->addGameObject(m_grassList);
    m_engine->addGameObject(m_hitboxObjectList);

#else
    //m_engine->addGameObject(m_hitboxObjectList);
    // m_engine->addGameObject(m_testObj);
    // m_engine->addGameObject(m_testObj2);
    m_engine->addGameObject(m_sheep);
    m_engine->addGameObject(obsticle);

#endif


    m_engine->setup();

#ifndef CLEAR_LEVEL
  //  m_engine->setCollisionSingleInteraction(m_sheep,m_terainGroup);
    qDebug() << "set interactions";
    m_engine->setCollisionSingleInteraction(Interaction::detection,m_sheep,m_grassList);
    //m_engine->setRenderLayer_BOTTOM(m_terainGroup);
    //m_engine->setRenderLayer_BOTTOM(m_terainGroup);
  //  m_engine->moveRenderLayer_UP(m_grassList);
//    m_engine->moveRenderLayer_UP(m_sheep);

   // m_engine->setLayerVisibility(RenderLayerIndex::vertexPaths,false);
#else
    m_engine->setCollisionSingleInteraction(Interaction::collision,m_sheep,obsticle);
    //m_engine->setRenderLayer_TOP(m_sheep);

#endif

    qDebug() << "setup_level done";
}
// Setup the keybindings for special keyEvents
void Level::setup_keyEvent()
{
    qDebug() << "setup_keyEvent";
    m_keyEvent_P = new KeyEvent(KEYBOARD_KEY_P);
    m_keyEvent_H = new KeyEvent(KEYBOARD_KEY_H);

    m_engine->addEvent(m_keyEvent_P);
    m_engine->addEvent(m_keyEvent_H);
    qDebug() << "setup_keyEvent done";
}
void Level::cleanup()
{
    delete m_engine;
}

// Mainloop for the engine
void Level::run()
{
    LEVEL_FUNCTION(profiler::colors::Amber200);
    m_engine->loop();
#ifdef BUILD_WITH_EASY_PROFILER
    if(m_engine->getTick() == 10)
    {
        m_visibility_collider_hitbox = !m_visibility_collider_hitbox;
        m_hitboxObjectList->setVisibility_collider_hitbox(m_visibility_collider_hitbox);
        m_hitboxObjectList->setVisibility_collider_boundingBox(m_visibility_collider_hitbox);
    }
    if(m_engine->getTick() > 10)
    {
       m_sheep->move(Vector2f(0,-1));
    }
    if(m_engine->getTick() > 30)
       m_engine->stop();
#endif
}
// Is used to chech if the window was closed
bool Level::engineIsActive()
{
    return m_engine->running();
}

// These functions will later be called from the engine
 // userEventLoop: Here you can handle your Events (KeyEvents).
void Level::userEventLoop(float tickInterval,unsigned long long tick,const vector<sf::Event> &eventLsit)
{
   /* if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // left click...
    }
    // get global mouse position
    sf::Vector2i position = sf::Mouse::getPosition();
    qDebug() << "pos: "<<position.x<<" "<<position.y;*/
    // set mouse position relative to a window
  //  sf::Mouse::setPosition(sf::Vector2i(100, 200), window);
    if(m_keyEvent_P->isSinking())
    {
        // Toggle stats visualisation
        m_engine->display_stats(!m_engine->display_stats(),Color(200,200,200),Vector2i(0,0));
    }

    if(m_keyEvent_H->isSinking())
    {
        // Toggle hitbox visualisation

        m_visibility_collider_hitbox = !m_visibility_collider_hitbox;
        //m_sheep->setVisibility_collider_hitbox(m_visibility_collider_hitbox);
        m_hitboxObjectList->setVisibility_collider_hitbox(m_visibility_collider_hitbox);
        m_hitboxObjectList->setVisibility_collider_boundingBox(m_visibility_collider_hitbox);
        //getchar();
    }
#ifndef CLEAR_LEVEL
   // regenerateGrassField();
#endif
}

 // userTickLoop: Here you can manipulate the game.
void Level::userTickLoop(float tickInterval,unsigned long long tick)
{

    /*if(m_chunkGenTimer.start(0.1))
    {
        chunkLoader();
    }*/
#ifndef CLEAR_LEVEL
    RectI generatorRect;
    Vector2i rectSize(16*64,16*64);
    generatorRect.setPos(Vector2i(m_sheep->getPos().x-rectSize.x/2,m_sheep->getPos().y-rectSize.y/2));
    generatorRect.setSize(rectSize);
    terainGenerator(m_engine,generatorRect);
    /*if(m_chunkGenTimer.start(0.1))
    {
        chunkLoader();
    }*/
#ifdef GLOBALVIEW
    Vector2f movingVec = Vector2f(m_windowMidlePoint) - Vector2f(m_sheep->getPos());
    if(Vector::length(movingVec) > 0)
    {
        /*m_sheep->setPos(m_windowMidlePoint);
        m_terainGroup->move(movingVec);
        m_grassList->move(movingVec);*/
        //m_engine->display_moveRenderFrame(-m_sheep->getMovingVector());
        m_engine->display_setRenderFramePosCenter(m_sheep->getPos());
    }
#endif
#endif
}

 // userDrawLoop: If you want to change something on the graphics, do it here.
 // You also can do this stuff in the userTickLoop but you may run the tickLoop faster
 // than you draw stuff, so you will waste performance.
void Level::userDrawLoop(float tickInterval,unsigned long long tick, PixelDisplay &display)
{

    if(m_timer1.start(0.1))
    {

    }
}


GameObjectGroup *Level::factory_terain(RectU area)
{
    qDebug() << "factory_terain";
    Texture texture;
    //texture.setOriginType(Texture::Origin::topLeft);
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
    Vector2u  randomPos;
    if(area.getSize().x == 0 && area.getSize().y == 0)
    {
        randomPos = Vector2u(0,0);
        area.setSize(texture.getSize());
    }
    else if(texture.getSize().x < area.getSize().x || texture.getSize().y < area.getSize().y)
    {
        area.setSize(texture.getSize().x,texture.getSize().y);
        randomPos = Vector2u(0,0);
    }
    else
    {
        randomPos = Vector2u (PixelEngine::random(0,texture.getSize().x    - area.getSize().x),
                              PixelEngine::random(0,texture.getSize().y    - area.getSize().y));
    }
    LEVEL_BLOCK("load map",profiler::colors::Amber);
    GameObjectGroup *group = new GameObjectGroup();
    group->reserve(area.getSize().x * area.getSize().y);
    for(unsigned int x=0; x<area.getSize().x; x++)
    {
        for(unsigned int y=0; y<area.getSize().y; y++)
        {
            Block *block;
            Color color = texture.getColor(Vector2i(randomPos.x + x,randomPos.y + y));

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
                qDebug() << "not defined field on Map: "<<randomPos.x + x<< " "<<randomPos.y + y;
                block = new GrassBlock();
            }
            block->setRenderLayer(RenderLayerIndex::layer_1);
          /*  switch()
            {
                case 0: block = new DirtBlock(); break;
                case 1: block = new GrassBlock(); break;
                case 2: block = new SandBlock(); break;
                case 3: block = new StoneBlock(); break;
                case 4: block = new WaterBlock(); break;
            }*/
            block->setPos(area.getPos().x + x*block->getSize().x ,area.getPos().y + y*block->getSize().y );
            group->add(block);
        }
        qDebug() << x*100/area.getSize().x << " %";
    }
    qDebug() << "factory_terain done";
    return group;
}
void Level::chunkLoader()
{
    if(m_mapGeneratorY>500*16)
        return;
    RectI area(m_mapGeneratorX,m_mapGeneratorY,16*16,16*16);
    terainGenerator(m_engine,area);
    m_mapGeneratorX += area.getSize().x;


    if(m_mapGeneratorX > 16*500)
    {
        m_mapGeneratorX = -500*16;
        m_mapGeneratorY += area.getSize().y;
    }
}
void Level::terainGenerator(PixelEngine *engine,RectI area)
{
    int scale = 16;
    RectI scaledArea(area.getPos()/scale,area.getSize()/scale);

    for(int x=scaledArea.getPos().x; x<scaledArea.getPos().x+scaledArea.getSize().x; x++)
    {
        for(int y=scaledArea.getPos().y; y<scaledArea.getPos().y+scaledArea.getSize().y; y++)
        {
           // qDebug()<<x<<" "<<y<< " "<<;
            std::pair<int,int> pos(x,y);
            if(m_generatedMap[pos] == false)
            {
                GameObject *block = generateBlock(x,y);

                block->setPosInitial(Vector2f(x*scale,y*scale));


                if(block->getProperty().getBody().material == Property::Material::Grass)
                {
                    GameObject *plant = generatePlant();
                    plant->setPosInitial(block->getPos()+Vector2f(PixelEngine::random(-8,8),PixelEngine::random(-8,8)));

                    //m_grassList->reserve(10000);
                    //m_hitboxObjectList->reserve(10000);
                    m_grassList->add(plant);
                    m_hitboxObjectList->add(plant);
                   // engine->addGameObject(plant);
                }


                m_terainGroup->add(block);
               // engine->addGameObject(block);
                m_generatedMap[pos] = true;
            }
        }
    }
}
GameObject* Level::generateBlock(int x,int y)
{
    noise.SetFractalType(FastNoiseLite::FractalType_Ridged);
    float  noiseValue = noise.GetNoise((float)x, (float)y);

    noise.SetFractalType(FastNoiseLite::FractalType_PingPong);
    float waterValue  = noise.GetNoise((float)x, (float)y);

    Block *block;
    if(waterValue<-0.6)
    {
        block = new WaterBlock();
    }
    else
    {
        if(waterValue<-0.5)
        {
            block = new SandBlock();
        }
       else if(noiseValue>0.3)
        {
            block = new GrassBlock();
        }
        else
        {
            block = new DirtBlock();
        }
    }
    block->setRenderLayer(RenderLayerIndex::layer_1);
    return block;

}
GameObject *Level::generatePlant()
{
    int randPlant = PixelEngine::randomL(0,100);
    GameObject *plant;
    if(randPlant > 80)
    {
        plant = new Flower(PixelEngine::random(0,TexturePath::Plant::flower.size()-1));
    }
    else
    {
        plant = new Grass(PixelEngine::random(0,TexturePath::Plant::grass.size()-1));
    }
    plant->setRenderLayer(RenderLayerIndex::layer_2);
    return plant;
}
void Level::regenerateGrassField()
{
    if(m_grassList->size() >= m_maxGrassAmount)
        return;
  //  qDebug() << "regenerateGrassField() "<<m_maxGrassAmount;
    GameObjectGroup grassBlockGroup;
    for(size_t i=0; i<m_terainGroup->size(); i++)
    {
        if((*m_terainGroup)[i]->getProperty().getBody().material == Property::Material::Grass)
        {
            grassBlockGroup.add((*m_terainGroup)[i]);
        }
    }
    m_grassList->reserve(m_maxGrassAmount);
    int percent = 0;
    int lastPercent =0;
    while(m_grassList->size() < m_maxGrassAmount)
    {
        LEVEL_BLOCK("while(m_grassList->size() < m_maxGrassAmount)",profiler::colors::Amber);
        //Grass *grass = new Grass();
        //Point randomPos(PixelEngine::random(0,200),PixelEngine::random(0,200));
        //bool grassGodToPlant = false;

        size_t randBlock = PixelEngine::randomL(0,grassBlockGroup.size()-1);

        // Get random generated Plant
        GameObject *plant;
        int randPlant = PixelEngine::randomL(0,100);
        LEVEL_BLOCK("new OBJ",profiler::colors::Amber100);
        if(randPlant > 80)
        {
           // qDebug() << "Generate Flower";
            plant = new Flower(PixelEngine::random(0,TexturePath::Plant::flower.size()-1));
        }
        else
        {
          //  qDebug() << "Generate Grass";
            plant = new Grass(PixelEngine::random(0,TexturePath::Plant::grass.size()-1));
        }
       // qDebug() << "setPos";
        LEVEL_END_BLOCK;
        plant->setPos(grassBlockGroup[randBlock]->getPos()+Vector2f(PixelEngine::random(-8,8),PixelEngine::random(-8,8)));
        plant->setRenderLayer(RenderLayerIndex::layer_2);

        m_grassList->add(plant);
      // qDebug() << "add plant: "<<m_grassList->size();
        //m_engine->
        //m_engine->setCollisionSingleInteraction(m_sheep,grass);
        percent = m_grassList->size()*10/m_maxGrassAmount;
        if(percent != lastPercent)
        {
            qDebug() << percent*10 <<" %";
            lastPercent = percent;
        }
      //  qDebug() << m_grassList->size()*100/m_maxGrassAmount<< " %";
    }

   // qDebug() << "regenerateGrassField() end";
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
