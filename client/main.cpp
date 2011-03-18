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

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "Champion.h"
#include "Timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 20;
const int CHAMPION_WIDTH = 35;
const int CHAMPION_HEIGHT = 23;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

SDL_Surface *champion = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Event event;
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

SDL_Surface *load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );
    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        SDL_FreeSurface( loadedImage );
        if( optimizedImage != NULL )
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
    }
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    if( screen == NULL )
        return false;
    SDL_WM_SetCaption( "OpenMoba", NULL );

    return true;
}

bool load_files()
{
    champion = load_image( "img/champion.png" );
    background = load_image( "img/bg.png" );

    if( champion == NULL )
        return false;

    if( background == NULL )
        return false;
    return true;
}

void clean_up()
{
    SDL_FreeSurface( champion );
    SDL_FreeSurface( background );
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    bool quit = false;
    Champion mychamp(CHAMPION_WIDTH,CHAMPION_HEIGHT);
    Timer fps;

    if( init() == false )
        return 1;

    if( load_files() == false )
        return 1;

    while( quit == false )
    {
        fps.start();
        while( SDL_PollEvent( &event ) )
        {
            mychamp.handle_input(event);
            if( event.type == SDL_QUIT )
                quit = true;
        }
        mychamp.move(LEVEL_HEIGHT,LEVEL_WIDTH);
        mychamp.set_camera(camera,LEVEL_HEIGHT,LEVEL_WIDTH,SCREEN_HEIGHT,SCREEN_WIDTH);
        apply_surface( 0, 0, background, screen, &camera );
        mychamp.show(camera, champion, screen);

        if( SDL_Flip( screen ) == -1 )
            return 1;

        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
    }
    clean_up();

    return 0;
}
