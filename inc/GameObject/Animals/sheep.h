#ifndef SHEEP_H
#define SHEEP_H
#include "gameobject.h"
#include "rectSensor.h"
#include "keyController.h"
#include "animatedTexture.h"
#include "texturePaths.h"
#include "timer.h"
#include "texturePainter.h"
#include "textPainter.h"

#include "objectTree.h"
//#define USE_ANIMATED_TEXTURE

class Sheep     : public GameObject
{
    public:
        Sheep();
        Sheep(const Sheep &other);
        virtual ~Sheep();

        void setup();

        virtual void checkEvent();
        //virtual void preTick();
        //virtual void tick(const Vector2i&direction);
        virtual void postTick();
        virtual void preDraw();
        virtual unsigned int checkCollision(const vector<GameObject*> &other);
        //virtual void draw(PixelDisplay &display);

        virtual void setTexturePathList(const vector<string> &pathList);
        virtual void setKeyBinding(const int &UP_KEY,
                                   const int &LEFT_KEY,
                                   const int &DOWN_KEY,
                                   const int &RIGHT_KEY,
                                   const int &EAT_KEY,
                                   const int &DISPLAY_PROPERTY_KEY,
                                   const int &DISPLAY_COLLIDER_KEY,
                                   const int &DISPLAY_CHUNK_KEY);

        virtual void event_hasCollision(vector<GameObject *> other);

        virtual void rotate(const float &deg);

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
        RectSensor      *m_sensor;
        KeyController   *m_controller;


        Event           *m_eventLEFT;   // Rotate Left
        Event           *m_eventRIGHT;  // Rotate right
        Event           *m_event_EAT;   // Eat with key "E"
        Event           *m_eventToggleStats; // Q
        Event           *m_eventToggleColliderVisibility; // C
        Event           *m_eventToggleChunkVisibility; // M

        Timer           m_debugTimer;

        TextPainter     *m_propertyText;
        Vector2f         m_propertyTextRelativePos;
    private:

        Timer           m_slowTimer;
        float           m_cameraZoom;

        ObjectTree      *m_tree;
        VertexPathPainter *m_treePainter;

};
#endif
