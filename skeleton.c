#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "SDL.h"
#include <time.h>


SDL_Surface *screen;
int sizeX, sizeY, mode;

void putpixel(int x, int y, int color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = y * (screen->pitch / 4);
  ptr[lineoffset + x] = color;
}

int main( int argc, char* args[] )
{

  printf("Enter Number of Horizontal Pizels: \n");
  scanf("%d", &sizeX);

  printf("Enter Number of Vertical Pizels: \n");
  scanf("%d", &sizeY);

  printf("Enter (1) for picture & (2) for zoom: \n");
  scanf("%d", &mode);

  int zoom = 1;

  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  atexit(SDL_Quit);
    
  screen = SDL_SetVideoMode(sizeX, sizeY, 32, SDL_SWSURFACE);
  
  if ( screen == NULL ) 
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }

     while (1)  
    {
    render(zoom);
    if (mode == 2)
      zoom++;

    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
      switch (event.type) 
      {
      case SDL_KEYDOWN:
        break;
      case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_ESCAPE)
          return 0;
        break;
      case SDL_QUIT:
        return(0);
      }
    }
  }
    return 0;
}



void render(int zoom)
{   
  
  if (SDL_MUSTLOCK(screen)) 
    if (SDL_LockSurface(screen) < 0) 
      return;


/*
Step 1) We define some variables and constants.
Step 2) We loop through each pixel and zoom in to a predefined point for the absolute value of Z less than 2.
Step 3) We define the rgb colors and convert the to hexadecimals and use putpixel to assign each pixel with a color.
*/

  int row, col, max = 1000, iteration, r, g, b;
  double cr, ci, zr, zi, zr_new, zi_new, k, hex;
  double re_point_zoom = 0.9223327810370947027656057193752719757635;
  double im_point_zoom = 0.3102598350874576432708737495917724836010;

  for (row=0; row<sizeY; row++) {
    for (col=0; col<sizeX; col++) {
      zr = 0;
      zi = 0;
      iteration = 0;
      cr = (col*4.0/sizeX-2.0)/(zoom*zoom) - re_point_zoom;
      ci = (row*4.0/sizeY-2.0)/(zoom*zoom) + im_point_zoom;
      while (zr*zr + zi*zi <= 4 && iteration < max) {
        zr_new = zr*zr - zi*zi + cr;
        zi_new = 2*zr*zi +ci;
        zr = zr_new;
        zi = zi_new;
        iteration++;
      }
      k = (iteration * 255 / max);
      r = round(sin(0.24*k+0)*127 + 128);
      g = round(sin(0.24*k+2)*127 + 128);
      b = round(sin(0.24*k+4)*127 + 128);
      hex = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
      if (iteration < max) putpixel(col, row, hex); 
      else putpixel(col, row, 0x000000);
    }
  }
  


  if (SDL_MUSTLOCK(screen)) 
      SDL_UnlockSurface(screen);
  SDL_UpdateRect(screen, 0, 0, sizeX, sizeY);    
  
}


