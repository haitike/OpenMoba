/////////////////////////////////////////////////////////////////////////////
// This file is part of the OpenMoba Project.
//
// OpenMoba is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OpenMoba is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OpenMoba. If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////////

#include "champion.h"
#include "constants.h"
#include "globals.h"
#include "functions.h"

Champion::~Champion()
{
    //dectructor
}

Champion::Champion()
{
    x = 0;
    y = 0;

    xVel = 0;
    yVel = 0;
}

void Champion::handle_input()
{
    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= CHAMPION_HEIGHT / 2; break;
            case SDLK_DOWN: yVel += CHAMPION_HEIGHT / 2; break;
            case SDLK_LEFT: xVel -= CHAMPION_WIDTH / 2; break;
            case SDLK_RIGHT: xVel += CHAMPION_WIDTH / 2; break;
        }
    }

    else if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += CHAMPION_HEIGHT / 2; break;
            case SDLK_DOWN: yVel -= CHAMPION_HEIGHT / 2; break;
            case SDLK_LEFT: xVel += CHAMPION_WIDTH / 2; break;
            case SDLK_RIGHT: xVel -= CHAMPION_WIDTH / 2; break;
        }
    }
}

void Champion::move()
{
    x += xVel;

    if( ( x < 0 ) || ( x + CHAMPION_WIDTH > LEVEL_WIDTH ) )
        x -= xVel;

    y += yVel;

    if( ( y < 0 ) || ( y + CHAMPION_HEIGHT > LEVEL_HEIGHT ) )
        y -= yVel;
}

void Champion::show()
{
    apply_surface( x - camera.x, y - camera.y, champion, screen );
}

void Champion::set_camera()
{
    camera.x = ( x + CHAMPION_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( y + CHAMPION_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    if( camera.x < 0 )
        camera.x = 0;
    if( camera.y < 0 )
        camera.y = 0;
    if( camera.x > LEVEL_WIDTH - camera.w )
        camera.x = LEVEL_WIDTH - camera.w;
    if( camera.y > LEVEL_HEIGHT - camera.h )
        camera.y = LEVEL_HEIGHT - camera.h;
}
