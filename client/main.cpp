/*This source code copyrighted by Lazy Foo' Productions (2004-2011)
and may not be redestributed without written permission.*/

// Project headers
#include "tools.h"

// External headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

//Screen attributes
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *image = NULL;
SDL_Surface *screen = NULL;

int main( int argc, char* args[] )
{
    if( tools::init("OpenMoba", screen, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP ) == false )
    {
        return 1;
    }
    image = load_image( "img/nexus.png" );
    if( image == NULL )
    {
        return 1;
    }
    apply_surface( 0, 0, image, screen );
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }
    SDL_Delay( 2000 );
    clean_up();

    return 0;
}
