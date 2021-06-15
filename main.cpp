#include <QCoreApplication>
#include "pixelengine.h"

PixelEngine     *engine;

void setup_level();
void clear_level();

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

    engine->display_stats(true);
}
void clear_level()
{

    delete engine;
}
