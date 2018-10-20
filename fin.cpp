#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#define x1 100
#define x2 155
#define x3 210
#define x4 265
#define x5 320
#define x6 375
#include "jeu.h"
#include "fin.h"





void fin( SDL_Surface *ecran ,int S ,int cpt  ,int pl ,FILE* fichier   )
{

    SDL_Surface  *menu=NULL,*lose=NULL, *win=NULL,  *boule[6]={NULL} ;
    //TTF
    SDL_Surface  *texte = NULL, *textej = NULL , *retour = NULL , *retour2 = NULL , *textet = NULL;
    SDL_Rect position[4] , position2 , positionts  ;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    char *chaine ;
    int continuer = 1 , x ;

    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();


    ecran = SDL_SetVideoMode(750, 750, 32, SDL_FULLSCREEN);

    SDL_WM_SetCaption("Master Mind", NULL);

   if (pl==4)
   {
         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_Flip(ecran);

       menu = IMG_Load("ganier2.png");
        position2.x = 0;
        position2.y = 20;
        SDL_BlitSurface(menu, NULL, ecran, &position2);
        police = TTF_OpenFont("JOKERMAN.ttf", 70);
        textej = TTF_RenderText_Blended(police, " Tu as GAGNE!! " , couleurNoire);

       sprintf( chaine , "%d" , S ) ;
       textet = TTF_RenderText_Blended(police, chaine , couleurNoire);
       SDL_BlitSurface(textet, NULL, ecran, &positionts);

   }

    if ((cpt == 10) && (pl != 4))
    {

       SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 68, 183, 210));
       SDL_Flip(ecran);

        menu = IMG_Load("pokemon.jpg");
        position2.x = 0;
        position2.y = 50;
        SDL_BlitSurface(menu, NULL, ecran, &position2);
        police = TTF_OpenFont("JOKERMAN.ttf", 70 );
        textej = TTF_RenderText_Blended(police, " Tu as perdu  " , couleurNoire);

         x = S ;
        sprintf( chaine , " Score : %d" , x ) ;
        textet = TTF_RenderText_Blended(police, chaine , couleurNoire);


    }


    police = TTF_OpenFont("JOKERMAN.ttf", 30);
    texte = TTF_RenderText_Blended(police, " Ton score est:" , couleurNoire);
    retour = TTF_RenderText_Blended(police, " Cliquez sur ENTER si vous voulez reprendre " , couleurNoire);
    retour2 = TTF_RenderText_Blended(police, " une nouvelle partie ^_^ sinon sur ESCAPE " , couleurNoire);


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

                case SDLK_RETURN :
                    jouer( ecran , fichier) ;
                    break ;


            }
         }



        position[1].x = 150;
        position[1].y = 250;
        SDL_BlitSurface(texte, NULL, ecran, &position[1]); /* Blit du texte */

        position[2].x = 140;
        position[2].y = 50;
        SDL_BlitSurface(textej, NULL, ecran, &position[2]);


        position[3].x = 50;
        position[3].y = 600;
        SDL_BlitSurface(retour, NULL, ecran, &position[3] );

        position[4].x = 50;
        position[4].y = 650;
        SDL_BlitSurface(retour2, NULL, ecran, &position[4] );

        SDL_BlitSurface(textet, NULL, ecran, &positionts);
        positionts.x = 145;
        positionts.y = 300;

        SDL_Flip(ecran);


    }


    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);


}







