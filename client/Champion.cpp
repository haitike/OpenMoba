#include "Champion.h"

Champion::~Champion()
{
    //dectructor
}

Champion::Champion(int height_ , int width_)
{
    x = 0;
    y = 0;

    xVel = 0;
    yVel = 0;

    height = height_;
    width = width_;
}

void Champion::handle_input(SDL_Event event)
{
    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= height / 2; break;
            case SDLK_DOWN: yVel += height / 2; break;
            case SDLK_LEFT: xVel -= width / 2; break;
            case SDLK_RIGHT: xVel += width / 2; break;
        }
    }

    else if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += height / 2; break;
            case SDLK_DOWN: yVel -= height / 2; break;
            case SDLK_LEFT: xVel += width / 2; break;
            case SDLK_RIGHT: xVel -= width / 2; break;
        }
    }
}

void Champion::move()
{
    x += xVel;

    if( ( x < 0 ) || ( x + width > width ) )
        x -= xVel;

    y += yVel;

    if( ( y < 0 ) || ( y + height > height ) )
        y -= yVel;
}

void Champion::show(SDL_Rect& camera, SDL_Surface* champion, SDL_Surface* screen)
{

    // Temporal
    SDL_Rect offset;
    offset.x = x - camera.x;
    offset.y = y - camera.y;
    SDL_BlitSurface( champion, NULL, screen, &offset );

    // Real
    //apply_surface( x - camera.x, y - camera.y, champion, screen );
}

void Champion::set_camera(SDL_Rect& camera, int level_height, int level_width)
{
    camera.x = ( x + width / 2 ) - width / 2;
    camera.y = ( y + height / 2 ) - height / 2;

    if( camera.x < 0 )
        camera.x = 0;
    if( camera.y < 0 )
        camera.y = 0;
    if( camera.x > level_width - camera.w )
        camera.x = level_width - camera.w;
    if( camera.y > level_height - camera.h )
        camera.y = level_height - camera.h;
}