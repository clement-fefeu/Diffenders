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


SDL_bool test(SDL_Point point, SDL_Rect rect){
    if(point.x >= rect.x && point.x <= (rect.x + rect.w) &&
        point.y >= rect.y && point.y <= (rect.y + rect.h))
        return SDL_TRUE;
    else
        return SDL_FALSE;
}

int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;
}

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load(path);
    if(!tmp)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

SDL_Texture *degrade(SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_PixelFormat *format;

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
                                1, 255); /* Il ne faudra pas oublier les vérifications */
    Uint32 pixels[255] = {0};
    size_t i;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    for(i = 0; i < 255; i++)
        pixels[i] = SDL_MapRGBA(format, i, 0, 0, 255);
    SDL_UpdateTexture(texture, NULL, pixels, sizeof(Uint32) * 1);
    SDL_FreeFormat(format);
    return texture;
}

void setPixel(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a, size_t x, size_t y)
{
    Uint32 *pixels = surface->pixels; /* Nos pixels sont sur 32 bits */
    Uint32 couleur = SDL_MapRGBA(surface->format, r, g, b, a);
    pixels[y * surface->w + x] = couleur;
}

SDL_Surface *createSurfaceFromTexture(SDL_Texture *texture)
{
    Uint32 format_pixels;
    SDL_Surface *surface = NULL;
    void *pixels = NULL;
    int pitch, w, h;

    if (SDL_QueryTexture(texture, &format_pixels, NULL, &w, &h) != 0)
    {
        fprintf(stderr, "SDL_QueryTexture: %s.\n", SDL_GetError());
        goto query_texture_fail;
    }

    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0)
    {
        fprintf(stderr, "SDL_LockTexture: %s.\n", SDL_GetError());
        goto lock_texture_fail;
    }

    surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, 32, w * sizeof(Uint32),format_pixels);
    if(NULL == surface)
        fprintf(stderr, "Erreur SDL_CreateSurfaceFrom : %s.\n", SDL_GetError());

    SDL_UnlockTexture(texture);
lock_texture_fail:
query_texture_fail:
    return surface;
}

void updateEvent(struct Input *input)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            input->quit = SDL_TRUE;
        else if(event.type == SDL_KEYDOWN)
            input->key[event.key.keysym.scancode] = SDL_TRUE;
        else if(event.type == SDL_KEYUP)
            input->key[event.key.keysym.scancode] = SDL_FALSE;
        else if(event.type == SDL_MOUSEMOTION)
        {
            input->x = event.motion.x;
            input->y = event.motion.y;
            input->xrel = event.motion.xrel;
            input->yrel = event.motion.yrel;
        }
        else if(event.type == SDL_MOUSEWHEEL)
        {
            input->xwheel = event.wheel.x;
            input->ywheel = event.wheel.y;
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN)
              input->mouse[event.button.button] = SDL_TRUE;
        else if(event.type == SDL_MOUSEBUTTONUP)
            input->mouse[event.button.button] = SDL_FALSE;

    }
}

void init_icon(SDL_Window *window){
    SDL_Surface *surface = NULL;
    SDL_Rect dst={ 0, 0, 32, 32 };
    surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, &dst, SDL_MapRGBA(surface->format, 0, 0, 255, 255));
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);
}

void aff_img(SDL_Renderer *renderer,SDL_Texture *texture){
    SDL_Rect src={ 0, 0, 100, 100 };
    SDL_Rect dst={ 0, 0, 400, 400 };

    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderCopy(renderer, texture, &src,&dst ); // j'affiche la texture, a partir des coordonné (0, 0) jusqu'a la hauteur et largeur totale soit (100, 100) et je fait pareil sur le rectangle destination, j'affiche sur tel dimension en (0, 0) et de largeur (100, 100)

    SDL_RenderPresent(renderer);
}

int main(int argc, char** argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_PixelFormat *format;
    SDL_Event event;
    SDL_bool continuer = SDL_TRUE;
    SDL_Color noir = {255, 255, 255, 255};
    struct Input in;
    Uint8 *clavier;
    Uint32 boutons;
    SDL_Rect position;
    int statut = EXIT_FAILURE;
    /* Initialisation simple */
    init(&window,&renderer,1024,768);
    init_icon(window);
    texture = loadImage("herbe.jpg",renderer);
    aff_img(renderer,texture);

    if (TTF_Init() < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
        return EXIT_FAILURE;
    }

    TTF_Font* font = TTF_OpenFont("Quick_Peach.ttf", 18);



    SDL_Surface* text = TTF_RenderText_Blended(font, "Hello, World", noir);

    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h); // Récupere la dimension de la texture


    // Libération des resource de la police et de la surface qui contient le texte
    SDL_FreeSurface(text);
    TTF_CloseFont(font);
    while(!in.quit)
    {
        updateEvent(&in);

        SDL_Delay(20);
    }


    statut = EXIT_SUCCESS;
Quit:
    if(NULL != texture)
        SDL_DestroyTexture(texture);
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    SDL_FreeSurface(text);
    TTF_Quit();
    SDL_Quit();
    return statut;
}
