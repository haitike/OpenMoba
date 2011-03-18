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
