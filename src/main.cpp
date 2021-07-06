//#define USE_EASY_PROFILER


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

void user_tick_loop(float tickInterval,unsigned long long tick);
void user_draw_loop(float tickInterval,unsigned long long tick);
void userEventLoop(float tickInterval,unsigned long long tick);*/

#define DELETEPTR(obj) if(obj!=nullptr){delete obj; obj = nullptr;}

void testDisplay();
Sprite *loadImage(const string &image);

int main(int argc, char *argv[])
{

    //testDisplay();

    EASY_PROFILER_ENABLE;
    EASY_MAIN_THREAD;


    EASY_BLOCK("Setup",profiler::colors::Amber);
    unsigned int mapWidth   = 16*20; // Width of the Grid, the hight will be calculated depending of the windowSize
    //unsigned int mapWidth   = 200;
    float displayScale     = 0.9;
    Vector2u  windowSize(1900*displayScale,1000*displayScale);

    Level game(windowSize,mapWidth);
    game.setup();
    EASY_END_BLOCK;
    EASY_BLOCK("while",profiler::colors::Amber100);
    while(game.engineIsActive())
    {
        try {
            game.run();
        }  catch (...) {
            qDebug() << "error occured";
        }

    }
    EASY_END_BLOCK;
    EASY_BLOCK("cleanup");
    game.cleanup();
    EASY_END_BLOCK;
    auto blocks_count = profiler::dumpBlocksToFile("profiler.prof");
    std::cout << "Profiler blocks count: " << blocks_count << std::endl;
    return 1;
}
void testDisplay()
{
    EASY_PROFILER_ENABLE;
    EASY_MAIN_THREAD;
    unsigned int mapWidth   = 16*16; // Width of the Grid, the hight will be calculated depending of the windowSize
    float displayScale     = 0.9;
    Vector2u  windowSize(1900*displayScale,1000*displayScale);
    PixelDisplay display(windowSize,Vector2u (mapWidth,float(mapWidth)*float(windowSize.y)/float(windowSize.x)));

    RectF rect(0,0,2,1);
    rect.rotate(Vector2f(0,0),45);

    display.addVertexLine(rect.getDrawable());
    display.display();


    auto blocks_count = profiler::dumpBlocksToFile("profiler.prof");
    std::cout << "Profiler blocks count: " << blocks_count << std::endl;
    getchar();

}
Sprite *loadImage(const string &image)
{
    //sf::Image   *i = new sf::Image();
    sf::Texture *t = new sf::Texture();
    sf::Sprite  *s = new sf::Sprite();
    //i->loadFromFile(image);
   // qDebug()<<i->getSize().x;
    t->loadFromFile(image);
    s->setTexture(*t);

    s->setPosition(1,1);
    //s->setPosition(PixelEngine::random(0,100),PixelEngine::random(0,100));
    //s->rotate(PixelEngine::random(0,360));
    return s;
}
