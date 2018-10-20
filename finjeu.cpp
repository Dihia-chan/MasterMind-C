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





void fin( SDL_Surface *ecran ,int S ,int cpt  ,int pl ,FILE* fichier , clock_t t1  )
{

    SDL_Surface  *menu=NULL ;
    //TTF
    SDL_Surface  *texte = NULL, *textej = NULL , *temps=NULL,*tempstext=NULL , *retour = NULL , *retour2 = NULL , *textet = NULL;
    SDL_Rect position1, position3 ,position4 ,position5   , position2 , positionts , positemps , posi ;
    TTF_Font *police = NULL , *policetemps = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleur = {163, 75, 164};
    char chaine[5] , time[10];
    int continuer = 1  ;

    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    clock_t t2 ;
    t2= clock() ;
    ecran = SDL_SetVideoMode(750, 750, 32, SDL_FULLSCREEN);

    SDL_WM_SetCaption("Master Mind", NULL);

   if (pl==4)
   {
         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        //SDL_Flip(ecran);

       menu = IMG_Load("ganier2.png");
        position2.x = 0;
        position2.y = 20;
        SDL_BlitSurface(menu, NULL, ecran, &position2);
        police = TTF_OpenFont("JOKERMAN.ttf", 70);
        textej = TTF_RenderText_Blended(police, " Vous avez GAGNE!! " , couleurNoire);

       sprintf( chaine , "%d" , S ) ;
       textet = TTF_RenderText_Blended(police, chaine , couleurNoire);

       policetemps = TTF_OpenFont("JOKERMAN.ttf", 30);
       sprintf( time , " Vous avez mis : %.1lf sec " , (double)(t2-t1)/CLOCKS_PER_SEC ) ;
       temps = TTF_RenderText_Blended(policetemps, time , couleur);


   }

    if ((cpt == 10) && (pl != 4))
    {

       SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 68, 183, 210));


        menu = IMG_Load("pokemon.jpg");
        position2.x = 26;
        position2.y = 50;
        SDL_BlitSurface(menu, NULL, ecran, &position2);
        police = TTF_OpenFont("JOKERMAN.ttf", 70 );
        textej = TTF_RenderText_Blended(police, " Vous avez perdu :P " , couleurNoire);


        sprintf( chaine , "  %d " , S ) ;
        textet = TTF_RenderText_Blended(police, chaine , couleurNoire);

        policetemps = TTF_OpenFont("JOKERMAN.ttf", 30);
        sprintf( time , " Vous avez mis : %.1lf sec " , (double)(t2-t1)/CLOCKS_PER_SEC ) ;
        temps = TTF_RenderText_Blended(policetemps, time , couleur);


    }


    texte = TTF_RenderText_Blended(policetemps, " Votre score est:" , couleurNoire);
    retour = TTF_RenderText_Blended(policetemps, " Cliquez sur ENTER si vous voulez reprendre " , couleurNoire);
    retour2 = TTF_RenderText_Blended(policetemps, " une nouvelle partie ^_^ sinon sur ESCAPE " , couleurNoire);

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





        position1.x = 40;
        position1.y = 50;
        SDL_BlitSurface(textej, NULL, ecran, &position1);

        position3.x = 120;
        position3.y = 330;
        SDL_BlitSurface(texte, NULL, ecran, &position3); /* Blit du texte */

        SDL_BlitSurface(textet, NULL, ecran, &positionts);
        positionts.x = 145;
        positionts.y = 380;

        SDL_BlitSurface(temps, NULL, ecran, &positemps);
        positemps.x = 90 ;
        positemps.y = 220;

        SDL_BlitSurface(retour, NULL, ecran, &position4 );
        position4.x = 50;
        position4.y = 600;

        position5.x = 50;
        position5.y = 650;
        SDL_BlitSurface(retour2, NULL, ecran, &position5 );

        SDL_Flip(ecran);


    }


    TTF_CloseFont(police);

    SDL_FreeSurface(texte);
    SDL_FreeSurface(temps);
    SDL_FreeSurface(textej);
    SDL_FreeSurface(retour2);
    SDL_FreeSurface(retour);
    TTF_Quit();

}
