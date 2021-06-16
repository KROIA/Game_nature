#include <QCoreApplication>
#include "pixelengine.h"
#include "grass.h"
#include "player.h"

#include "QDebug"

PixelEngine     *engine;
Grass           *obj_grass;
Player          *obj_player;

void setup_level();
void clear_level();

void user_tick_loop(double interval,unsigned long long tick);
void user_draw_loop(double interval,unsigned long long tick);

int main(int argc, char *argv[])
{
    setup_level();

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
    return 1;
}
void setup_level()
{
    unsigned int mapWidth = 300;

    RECT dispaySize;
    GetWindowRect(GetDesktopWindow(), &dispaySize);
    PointU windowSize(dispaySize.right,dispaySize.bottom-20);
    engine = new PixelEngine (PointU(mapWidth,double(mapWidth)*double(windowSize.getY())/double(windowSize.getX())),windowSize);
    engine->set_setting_checkEventInterval(1.0f/30.0f);
    engine->set_setting_gameTickInterval(1.0f/120.0f);
    engine->set_setting_displayInterval(1.0f/60.0f);

    engine->setUserTickLoop(user_tick_loop);
    engine->setUserDisplayLoop(user_draw_loop);

 //   engine->display_stats(true);

    //GameObjects
    obj_grass = new Grass();
    engine->addGameObject(obj_grass);

    obj_player = new Player();
    obj_player->setColor(Color(0,255,0));
    obj_player->setStartPos(Point(50,50));
    obj_player->setKeyBinding(KEYBOARD_KEY_W, KEYBOARD_KEY_A,
                              KEYBOARD_KEY_S, KEYBOARD_KEY_D);
    obj_player->buildPlayer();

    engine->addGameObject(obj_player);



}
void clear_level()
{

    delete engine;
}

void user_tick_loop(double interval,unsigned long long tick)
{

}
void user_draw_loop(double interval,unsigned long long tick)
{

}
