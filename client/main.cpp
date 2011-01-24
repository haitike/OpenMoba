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
    //Initialize. Caption, Screen Image, Width, height and BPP.
    if( init("OpenMoba", screen, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP ) == false )
    {
        return 1;
    }

    //Load the image
    image = load_image( "img/nexus.png" );

    //If there was a problem in loading the image
    if( image == NULL )
    {
        return 1;
    }

    //Apply the surface to the screen
    apply_surface( 0, 0, image, screen );

    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    //Wait 2 seconds
    SDL_Delay( 2000 );

    //Free the surface and quit SDL
    clean_up();

    return 0;
}
