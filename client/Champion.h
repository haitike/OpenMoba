#ifndef CHAMPION_H
#define CHAMPION_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Champion
{
    public:
        Champion(int height_ , int width_);
        virtual ~Champion();
        void handle_input(SDL_Event event);
        void move(int level_height, int level_width);
        void show(SDL_Rect& camera, SDL_Surface* champion, SDL_Surface* screen);
        void set_camera(SDL_Rect& camera, int level_height, int level_width, int screen_height, int screen_width);
    protected:
    private:
        int x, y;
        int xVel, yVel;
        int height, width;

};

#endif // CHAMPION_H
