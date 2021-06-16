#ifndef GRASS_H
#define GRASS_H
#include "pixelengine.h"
#include "gameobject.h"



class Grass : public GameObject
{
    public:
        Grass();
        Grass(const Grass &other);
      /*  Grass(Controller *controller,
              Collider   *collider,
              Painter    *painter);*/

        virtual ~Grass();
        virtual const Grass &operator=(const Grass &other);

        virtual void checkEvent();
        virtual void tick(const Point &direction);
        virtual void draw(PixelDisplay &display);

    protected:
        virtual void setup();

    private:


        Painter  *m_painter;
        Collider *m_collider;

        Timer m_grassChangeTimer;
};
#endif
