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

#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "champion.h"
#include "timer.h"

int main( int argc, char* args[] )
{
    bool quit = false;
    Champion mychamp;
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
            mychamp.handle_input();
            if( event.type == SDL_QUIT )
                quit = true;
        }
        mychamp.move();
        mychamp.set_camera();
        apply_surface( 0, 0, background, screen, &camera );
        mychamp.show();

        if( SDL_Flip( screen ) == -1 )
            return 1;

        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
    }
    clean_up();

    return 0;
}
