#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

extern DECLSPEC int SDLCALL TTF_Init(void);

#define WIDTH 255
#define HEIGHT 255
#define SDL_BUTTON_LEFT     1
#define SDL_BUTTON_MIDDLE   2
#define SDL_BUTTON_RIGHT    3
#define SDL_BUTTON_X1       4
#define SDL_BUTTON_X2       5
#define TTF_GetError    SDL_GetError


struct carre {
   SDL_Rect rect;
   Uint32 couleur;
};

struct Input
{
    SDL_bool key[SDL_NUM_SCANCODES];
    SDL_bool quit;
    int x, y, xrel, yrel;
    int xwheel, ywheel;
    SDL_bool mouse[6];
};

SDL_Rect position;

SDL_bool test(SDL_Point point, SDL_Rect rect);
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
SDL_Texture *degrade(SDL_Renderer *renderer);
void setPixel(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a, size_t x, size_t y);
SDL_Surface *createSurfaceFromTexture(SDL_Texture *texture);
void updateEvent(struct Input *input);
void init_icon(SDL_Window *window);
int menu();
int jeu(SDL_Renderer *renderer);