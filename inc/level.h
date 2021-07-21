#ifndef LEVEL_H
#define LEVEL_H

// Include the Engineframework
#include "pixelengine.h"

//========================================================
// Include your costum GameObjects here:
#include "Blocks/dirtblock.h"
#include "Blocks/grassblock.h"
#include "Blocks/sandblock.h"
#include "Blocks/stoneblock.h"
#include "Blocks/waterblock.h"

#include "Animals/sheep.h"

#include "Plants/grass.h"
#include "Plants/flower.h"


// Create a class, called "Level".
// You can run the Engine also in the main loop
class Level
{
    public:
        Level(Vector2u  windowSize, unsigned int mapWidth);
        ~Level();

        // Basic Functions for creating and deleting the level
        static void setup();
        static void cleanup();

        // Mainloop for the engine
        static void run();
        // Is used to chech if the window was closed
        static bool engineIsActive();

        // These functions will later be called from the engine
         // userEventLoop: Here you can handle your Events (KeyEvents).
        static void userEventLoop(float tickInterval,unsigned long long tick,const vector<sf::Event> &eventLsit);
         // userTickLoop: Here you can manipulate the game.
        static void userTickLoop(float tickInterval,unsigned long long tick);
         // userDrawLoop: If you want to change something on the graphics, do it here.
         // You also can do this stuff in the userTickLoop but you may run the tickLoop faster
         // than you draw stuff, so you will waste performance.
        static void userDrawLoop(float tickInterval,unsigned long long tick,PixelDisplay &display);

//========================================================
        // Put your public function declarations here:


    private:
        // Setup for the engine
        static void setup_engine();
        // Build all GameObjects and configures them
        static void setup_level();
        // Setup the keybindings for special keyEvents
        static void setup_keyEvent();

//========================================================
        // Put your private function declarations here:
        static GameObjectGroup *factory_terain(RectU area);
        static void chunkLoader();
        static void terainGenerator(PixelEngine *engine,RectI area);
        static GameObject* generateBlock(int x,int y);
        static GameObject *generatePlant();
        static void regenerateGrassField();
        static bool colorInRange(const Color &col1,const Color &col2,unsigned int range=20);

        // Engine object
        static PixelEngine         *m_engine;
        static bool                 m_levelBuilt;
        static Vector2u                m_windowSize;
        static unsigned int         m_mapWidth;

//========================================================
        // Put your GameObject declarations here:
        //static ManagedGameObjectGroup      m_objectList;

        // Toggle stats on and off
        static Event               *m_keyEvent_P;

        // Toggle Hitbox of all objects in the list: hitboxObjectList
        static Event               *m_keyEvent_H;
        static GameObjectGroup     *m_terainGroup;
        static GameObjectGroup     *m_hitboxObjectList;
        static bool                 m_visibility_collider_hitbox;
        static Timer                m_timer1;
        static Sheep               *m_sheep;
        static Vector2i               m_windowMidlePoint;

        static GameObjectGroup     *m_grassList;
        static unsigned int         m_maxGrassAmount;

        // TESTS
        static PixelPainter *m_pixPainter;
        static GameObject   *m_testObj;

        struct hash_pair {
            template <class T1, class T2>
            size_t operator()(const std::pair<T1, T2>& p) const
            {
                auto hash1 = std::hash<T1>{}(p.first);
                auto hash2 = std::hash<T2>{}(p.second);
                return hash1 ^ hash2;
            }
        };
        static std::unordered_map<std::pair<int, int>, bool, hash_pair> m_generatedMap;
        static RectI m_generatedMapRect;
        static int m_mapGeneratorX;
        static int m_mapGeneratorY;
        static Timer m_chunkGenTimer;
        static FastNoiseLite noise;

};
#endif // LEVEL_H
