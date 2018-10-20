#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "jeu.h"
#include "fichiers.h"
#include <SDL/SDL_image.h>


void aider( SDL_Surface *ecran  )
{

    SDL_Surface  *menu=NULL  , *texte =NULL ;
    SDL_Rect position , positiontext ;
    SDL_Event event;
    int continuer = 1 ;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};

     SDL_Init(SDL_INIT_VIDEO);
      TTF_Init();

    ecran = SDL_SetVideoMode(750, 750, 32, SDL_FULLSCREEN);
    SDL_WM_SetCaption("Master Mind", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_Flip(ecran);

      menu = IMG_Load("aider2.png");
      position.x = -50;
      position.y = 0;

       police = TTF_OpenFont("JOKERMAN.ttf", 25 );
       positiontext.x = 80;
       positiontext.y = 600;
       texte = TTF_RenderText_Blended(police, "Cliquez sur 'ESCAPE' pour retourner au menu " , couleurNoire);
       SDL_BlitSurface(texte, NULL, ecran, &positiontext);

      while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    continuer = 0;
                    default:
                    break;
            }

        }


        SDL_BlitSurface(menu, NULL, ecran, &position);
        SDL_BlitSurface(texte, NULL, ecran, &positiontext);

        SDL_Flip(ecran);


    }


 TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);

}

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu , x , y ;
    SDL_Event event2;
    int continuer = 1;
    FILE* fichier = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("rouge.png"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(750, 750, 32, SDL_FULLSCREEN);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 183, 65, 245));
    SDL_Flip(ecran);
    SDL_WM_SetCaption("MasterMinds", NULL);

    menu = IMG_Load("menu.png");
    positionMenu.x = 20;
    positionMenu.y = 0;


    while (continuer)
    {
        SDL_WaitEvent(&event2);
        switch(event2.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event2.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                        continuer = 0;
                        break;
                    case SDLK_j: // Demande à jouer
                        jouer(ecran , fichier);
                        break;
                    case SDLK_s: // Demande l'éditeur de niveaux
                        meilleurscores(ecran , fichier);
                        default:
                        break;

                 }
                break;
            case SDL_MOUSEBUTTONDOWN:
                        x.x = event2.button.x ;
                        y.y = event2.button.y ;

                        if ( x.x>10 && x.x<200 && y.y > 100 && y.y <250)
                           aider( ecran ) ;


                  default:
                 break ;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 183, 65, 245));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}

