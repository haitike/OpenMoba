#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "Champion.h"
#include "Timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 20;
const int CHAMPION_WIDTH = 23;
const int CHAMPION_HEIGHT = 38;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

SDL_Surface *champion = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Event event;
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "OpenMoba", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the dot image
    champion = load_image( "img/champion.png" );

    //Load the background
    background = load_image( "img/bg.png" );

    //If there was a problem in loading the dot
    if( champion == NULL )
    {
        return false;
    }

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( champion );
    SDL_FreeSurface( background );

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //The dot
    Champion mychamp(CHAMPION_WIDTH,CHAMPION_HEIGHT);

    //The frame rate regulator
    Timer fps;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the dot
            mychamp.handle_input(event);

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //Move the dot
        mychamp.move();

        //Set the camera
        mychamp.set_camera(camera,LEVEL_HEIGHT,LEVEL_WIDTH);

        //Show the background
        apply_surface( 0, 0, background, screen, &camera );

        //Show the dot on the scrSDL_Rect& *cameraeen
        mychamp.show(camera, champion, screen);

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }
    clean_up();

    return 0;
}
