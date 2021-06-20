#ifndef SHEEP_H
#define SHEEP_H
#include "gameobject.h"
#include "sensor.h"
#include "keyController.h"
#include "animatedTexture.h"
#include "texturePaths.h"
#include "timer.h"

class Sheep     : public GameObject
{
    public:
        Sheep();
        Sheep(const Sheep &other);
        virtual ~Sheep();

        virtual void checkEvent();
        //virtual void tick(const Point &direction);
        virtual unsigned int checkCollision(const vector<GameObject*> &other);
        virtual void draw(PixelDisplay &display);

        virtual void setTexturePathList(const vector<string> &pathList);
        virtual void setKeyBinding(const int &UP_KEY,
                                   const int &LEFT_KEY,
                                   const int &DOWN_KEY,
                                   const int &RIGHT_KEY,
                                   const int &EAT_KEY,
                                   const int &DISPLAY_PROPERTY_KEY);

        virtual void event_hasCollision(vector<GameObject *> other);


    protected:
        virtual void setupProperty();
        virtual void updatePropertyText();

        AnimatedTexture *m_animatedTexture;
        Sensor          *m_sensor;
        KeyController   *m_controller;


        Event           *m_eventLEFT;   // Rotate Left
        Event           *m_eventRIGHT;  // Rotate right
        Event           *m_event_EAT;   // Eat with key "E"
        Event           *m_eventToggleStats; // Q

        Timer           m_debugTimer;

        DisplayText    *m_propertyText;
        Vector          m_propertyTextRelativePos;
    private:

        Timer           m_slowTimer;

};
#endif
