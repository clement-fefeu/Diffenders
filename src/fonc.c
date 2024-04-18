#include "../lib/fonc.h"

/**
 * @brief Teste si un point est à l'intérieur d'un rectangle.
 * 
 * @param point Le point à tester.
 * @param rect Le rectangle dans lequel tester le point.
 * @return SDL_bool Retourne SDL_TRUE si le point est à l'intérieur du rectangle, sinon SDL_FALSE.
 */
SDL_bool test(SDL_Point point, SDL_Rect rect){
    if(point.x >= rect.x && point.x <= (rect.x + rect.w) &&
        point.y >= rect.y && point.y <= (rect.y + rect.h))
        return SDL_TRUE;
    else
        return SDL_FALSE;
}

/**
 * @brief Change la couleur de la fenêtre.
 * 
 * @param renderer Le renderer SDL.
 * @param color La couleur à appliquer.
 * @return int Retourne 0 en cas de réussite, -1 en cas d'échec.
 */
int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;
}

/**
 * @brief Initialise la fenêtre et le renderer SDL.
 * 
 * @param window Pointeur vers la fenêtre SDL.
 * @param renderer Pointeur vers le renderer SDL.
 * @param w La largeur de la fenêtre.
 * @param h La hauteur de la fenêtre.
 * @return int Retourne 0 en cas de réussite, -1 en cas d'échec.
 */
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, window, renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

/**
 * @brief Charge une image dans une texture SDL.
 * 
 * @param path Le chemin vers l'image à charger.
 * @param renderer Le renderer SDL.
 * @return SDL_Texture* La texture de l'image chargée.
 */
void loadImage(const char path[], SDL_Renderer *renderer,SDL_Texture **texture)
{
    SDL_Surface *tmp = NULL;
    tmp = IMG_Load(path);
    if(!tmp)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
    }
    *texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == *texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
    }
}

/**
 * @brief Crée une texture de dégradé pour le fond.
 * 
 * @param renderer Le renderer SDL.
 * @return SDL_Texture* La texture du dégradé.
 */
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

/**
 * @brief Modifie un pixel dans une surface SDL.
 * 
 * @param surface La surface SDL.
 * @param r La composante rouge du pixel.
 * @param g La composante verte du pixel.
 * @param b La composante bleue du pixel.
 * @param a La composante alpha du pixel.
 * @param x La coordonnée en x du pixel.
 * @param y La coordonnée en y du pixel.
 */
void setPixel(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a, size_t x, size_t y)
{
    Uint32 *pixels = surface->pixels; /* Nos pixels sont sur 32 bits */
    Uint32 couleur = SDL_MapRGBA(surface->format, r, g, b, a);
    pixels[y * surface->w + x] = couleur;
}

/**
 * @brief Crée une surface à partir d'une texture SDL.
 * 
 * @param texture La texture SDL.
 * @return SDL_Surface* La surface créée.
 */
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

/**
 * @brief Met à jour les événements d'entrée utilisateur.
 * 
 * @param input Structure d'entrée utilisateur.
 */
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

/**
 * @brief Initialise l'icône de la fenêtre.
 * 
 * @param window La fenêtre SDL.
 */
void init_icon(SDL_Window *window){
    SDL_Surface *surface = IMG_Load("../img/tower_def.jpg");
    SDL_SetWindowIcon(window, surface);
    SDL_FreeSurface(surface);
}

/**
 * @brief Charge un texte dans une texture SDL.
 * 
 * @param renderer Le renderer SDL.
 * @param text Le texte à afficher.
 * @param taille_text La taille du texte.
 * @return SDL_Texture* La texture du texte chargé.
 */
SDL_Texture *load_text(SDL_Renderer *renderer,char *text,int taille_text){
    SDL_Texture *texture = NULL;

	SDL_Color textColor = { 0, 0, 0 };
	if( TTF_Init() == -1 ) { 
		return 0; 
	}
	TTF_Font *police = NULL;
	police=TTF_OpenFont("../font/Quick_Peach.ttf",taille_text);
	if( police == NULL ) { 
		return 0; 
	}
	SDL_Surface *texte=TTF_RenderText_Blended(police, text, textColor) ;

    texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    TTF_CloseFont(police);
    return texture;
}