#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

SDL_Surface *load_image( std::string filename );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
bool init(std::string caption, SDL_Surface* screen, int screen_width, int screen_height, int screen_bpp)
void clean_up();

#endif // TOOLS_H_INCLUDED
