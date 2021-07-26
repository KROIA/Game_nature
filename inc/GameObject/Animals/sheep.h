#ifndef SHEEP_H
#define SHEEP_H
#include "gameobject.h"
#include "shapeSensor.h"
#include "laserSensor.h"
#include "keyController.h"
#include "animatedTexture.h"
#include "texturePaths.h"
#include "timer.h"
#include "texturePainter.h"
#include "textPainter.h"
#include "mouseMoveEvent.h"
#include "mouseButtonEvent.h"
#include "mouseMoveController.h"

#include "objectTree.h"
//#define USE_ANIMATED_TEXTURE

class Sheep     : public GameObject
{
    public:
        Sheep();
        Sheep(const Sheep &other);
        virtual ~Sheep();

        void setup();

        virtual void checkEvent(float deltaTime);
        //virtual void preTick();
        //virtual void tick(const Vector2i&direction);
        virtual void postTick();
        virtual void preDraw();
        //virtual unsigned int checkCollision(const vector<GameObject*> &other);
        //virtual void draw(PixelDisplay &display);

        virtual void setTexturePathList(const vector<string> &pathList);
        virtual void setKeyBinding(const int &UP_KEY,
                                   const int &LEFT_KEY,
                                   const int &DOWN_KEY,
                                   const int &RIGHT_KEY,
                                   const int &SPRINT_KEY,
                                   const int &EAT_KEY,
                                   const int &DISPLAY_PROPERTY_KEY,
                                   const int &DISPLAY_COLLIDER_KEY,
                                   const int &DISPLAY_CHUNK_KEY);

        virtual void event_hasCollision(vector<GameObject *> other);
    protected:
        virtual void setupProperty();
        virtual void updatePropertyText();

#ifdef USE_ANIMATED_TEXTURE
        AnimatedTexture *m_animatedTexture;
#else
        Texture         *m_texture;
#endif
        TexturePainter  *m_texturePainter;
        Collider        *m_collider;
        KeyController   *m_controller;
        MouseMoveController *m_mouseMoveController;

        ShapeSensor      *m_sensor;
        LaserSensor     *m_laserSensor;


        KeyEvent           *m_eventLEFT;   // Rotate Left
        KeyEvent           *m_eventRIGHT;  // Rotate right
        KeyEvent           *m_event_EAT;   // Eat with key "E"
        KeyEvent           *m_eventToggleStats; // Q
        KeyEvent           *m_eventToggleColliderVisibility; // C
        KeyEvent           *m_eventToggleChunkVisibility; // M
        KeyEvent           *m_event_sprint;    //ShiftKey

        Timer           m_debugTimer;

        TextPainter     *m_propertyText;
        Vector2f         m_propertyTextRelativePos;
    private:

        Timer           m_slowTimer;
        float           m_cameraZoom;

        ObjectTree      *m_tree;
        VertexPathPainter *m_treePainter;
        MouseMoveEvent  *m_mouseMoveEvent;
        MouseButtonEvent*m_mouseButtonEvent;

};
#endif
