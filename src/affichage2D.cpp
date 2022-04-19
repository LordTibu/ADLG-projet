#include "affichage2D.h"

affichage2D::affichage2D()
{
}

void affichage2D::affichage2DInit(){
    SCREEN_WIDTH = 640;
    SCREEN_HEIGHT = 480;
    //The window we'll be rendering to
    window = NULL;
    
    //The surface contained by the window
    screenSurface = NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cerr << "SDL could not initialize! SDL_Error: \n" << SDL_GetError();
    }else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
         if( window == NULL )
        {
            std::cerr << "Window could not be created! SDL_Error: \n" << SDL_GetError() ;
        }else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Wait two seconds
            SDL_Delay( 2000 );
        }
    }
}

void affichage2D::Close(){
    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
}

affichage2D::~affichage2D()
{
    
}
