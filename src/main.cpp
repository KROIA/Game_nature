


#include <QCoreApplication>
/*#include "pixelengine.h"
#include "grass.h"
#include "player.h"
#include "grassblock.h"*/

#include "QDebug"

#include "level.h"

/*PixelEngine     *engine;
Player          *obj_player;

Event *keyEvent_P;
Event *keyEvent_O;

// toggle Hitbox
Event *keyEvent_H;
GameObjectGroup hitboxObjectList;
bool hitboxIsVisible;

void setup_level();
void clear_level();

void user_tick_loop(double tickInterval,unsigned long long tick);
void user_draw_loop(double tickInterval,unsigned long long tick);
void userEventLoop(double tickInterval,unsigned long long tick);*/

int main(int argc, char *argv[])
{
  /*  setup_level();

    while(engine->running())
    {
        engine->checkEvent();
        engine->tick();
        engine->display();
        if(engine->get_setting_displayInterval()  > 0.002 &&
           engine->get_setting_gameTickInterval() > 0.002 &&
           engine->get_setting_eventHandleInterval() > 0.002)
        {
            nanosleep((const struct timespec[]){{0, 500000L}}, NULL);
        }
    }
    clear_level();
    return 1;*/

 /*   int *int1 = new int(10);
    qDebug() <<*int1;
    qDebug() <<"int1" <<int1;

    int *int2 = int1;

    qDebug() <<"int1" <<int1;
    qDebug() <<"int2" <<int2;

    delete int2;
    qDebug() <<"int1" <<int1;
    qDebug() <<"int2" <<int2;
    int2 = nullptr;
    qDebug() <<"int1" <<int1;
    qDebug() <<"int2" <<int2;
    qDebug() <<*int1;

    getchar();*/
    EASY_PROFILER_ENABLE;
    EASY_MAIN_THREAD;
    EASY_BLOCK("Setup");
    unsigned int mapWidth   = 16*40; // Width of the Grid, the hight will be calculated depending of the windowSize
    double displayScale     = 0.9;
    PointU windowSize(1900*displayScale,1000*displayScale);

    Level game(windowSize,mapWidth);
    game.setup();
    EASY_END_BLOCK;
    EASY_BLOCK("while");
    while(game.engineIsActive())
    {
        game.run();
    }
    EASY_END_BLOCK;
    EASY_BLOCK("cleanup");
    game.cleanup();
    EASY_END_BLOCK;
    auto blocks_count = profiler::dumpBlocksToFile("profiler.prof");
    std::cout << "Profiler blocks count: " << blocks_count << std::endl;
    return 1;
}
/*void setup_level()
{
    unsigned int mapWidth = 300;

    //RECT dispaySize;
    //GetWindowRect(GetDesktopWindow(), &dispaySize);
    //PointU windowSize(dispaySize.right,dispaySize.bottom-60);
    double displayScale = 1.8;
    PointU windowSize(1900*displayScale,1000*displayScale);
    engine = new PixelEngine (PointU(mapWidth,double(mapWidth)*double(windowSize.getY())/double(windowSize.getX())),windowSize);
    engine->set_setting_checkEventInterval(1.0f/30.0f);
    engine->set_setting_gameTickInterval(1.0f/120.0f);
    engine->set_setting_displayInterval(1.0f/60.0f);

    engine->setUserTickLoop(user_tick_loop);
    engine->setUserDisplayLoop(user_draw_loop);
    engine->setUserCheckEventLoop(userEventLoop);

 //   engine->display_stats(true);

    //GameObjects

    GameObjectGroup *grassGroup = new GameObjectGroup();
    PointU grassSize(2,2);
    PointU grassArraySize(60,50);

    for(unsigned int x=0; x<grassArraySize.getX(); x++)
    {
        for(unsigned int y=0; y<grassArraySize.getY(); y++)
        {
            Grass* grass = new Grass(grassSize);

            grass->setPos(10+x*grassSize.getX(),10+y*grassSize.getY());
            grassGroup->add(grass);
        }
    }
    //engine->addGroup(grassGroup);

    GrassBlock *grassBlock = new GrassBlock();
    grassBlock->setPos(Point(50,10));
    engine->addGameObject(grassBlock);


    obj_player = new Player();
    obj_player->setColor(Color(0,100,100));
    obj_player->setStartPos(Point(50,50));
    obj_player->setKeyBinding(KEYBOARD_KEY_W, KEYBOARD_KEY_A,
                              KEYBOARD_KEY_S, KEYBOARD_KEY_D);
    obj_player->buildPlayer();

    engine->addGameObject(obj_player);
    engine->setCollisionSingleInteraction(obj_player,grassGroup);

    hitboxObjectList.add(grassGroup);
    hitboxObjectList.add(obj_player);
    hitboxObjectList.add(grassBlock);

    //Key Events
    keyEvent_P = new Event(KEYBOARD_KEY_P);
    keyEvent_O = new Event(KEYBOARD_KEY_O);
    keyEvent_H = new Event(KEYBOARD_KEY_H);

}
void clear_level()
{
    delete keyEvent_P;
    delete keyEvent_O;
    delete keyEvent_H;
    delete engine;
}

void user_tick_loop(double tickInterval,unsigned long long tick)
{

}
void user_draw_loop(double tickInterval,unsigned long long tick)
{

}
void userEventLoop(double tickInterval,unsigned long long tick)
{
    keyEvent_P->checkEvent();
    keyEvent_O->checkEvent();
    keyEvent_H->checkEvent();

    if(keyEvent_P->isSinking())
    {
        //qDebug() << "keyEvent_P Sinking";
        engine->display_stats(!engine->display_stats(),Color(255,200,0),Point(1300,100));
    }
    if(keyEvent_O->isPressed())
    {
        obj_player->rotate_90();
    }

    if(keyEvent_H->isSinking())
    {
        hitboxIsVisible = !hitboxIsVisible;
        hitboxObjectList.setHitboxVisibility(hitboxIsVisible);
    }




}
*/
