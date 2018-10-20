/*
fichiers.c
----------

Rôle : fonctions de lecture / écriture de fichiers de score.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "fichiers.h"






void sauvgscores(int S , FILE* fichier )
{


    fichier = fopen("scores.txt", "a");
    fprintf( fichier , "%d \n" ,  S   );

    fclose(fichier);

}
void triTableau(int tab[],int taille)
{
    int i,j,k,maxe,temp;
    for(i=0;i<taille;i++)
    {
        maxe=tab[i];
        k=i;
        for(j=i+1;j<taille;j++)
        {
            if(tab[j]>maxe)
            {
                maxe=tab[j];
                k=j;
            }
        }
        if(k!=j)
        {
            temp=tab[i];
            tab[i]=maxe;
            tab[k]=temp;
        }
    }
}




void meilleurscores(SDL_Surface *ecran , FILE* fichier  )
{

   SDL_Surface *score[5] = {NULL}, *fond = NULL , *texte = NULL ;
    SDL_Rect position1 ,position2 ,position3 ,position   ;
    SDL_Rect posi ;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurVert = {0, 100, 10};
    SDL_Color couleurNoire = {0, 0 , 0};
    int continuer = 1 , S[20] , val ,i=0 ;
    char chaine1[3] , chaine2[3] , chaine3[3] ;


    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(750, 750, 32, SDL_FULLSCREEN);
    SDL_WM_SetCaption("Meilleur Scores", NULL);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 223, 228, 222));

     SDL_Flip(ecran);

    fond = IMG_Load("fleche.bmp");
    posi.x = 100;
    posi.y = 0;
    SDL_BlitSurface(fond, NULL, ecran, &posi);


    police = TTF_OpenFont("JOKERMAN.ttf", 50);

    texte = TTF_RenderText_Blended(police, "Les 3 meilleurs scores", couleurVert);

    fichier=fopen("scores.txt","r");
    while(!feof(fichier))
    {
        fscanf(fichier,"%d",&val);
        fgetc(fichier);
        S[i]=val;
        i++;
    }

    i--;
    fclose(fichier);
    triTableau(S,i);

    sprintf( chaine1 , " Score :%d" , S[1]);
    score[1] = TTF_RenderText_Blended(police, chaine1, couleurNoire);
    sprintf( chaine2 , " Score :%d" , S[2]);
    score[2] = TTF_RenderText_Blended(police, chaine2, couleurNoire);
    sprintf( chaine3 , " Score :%d" , S[3]);
    score[3] = TTF_RenderText_Blended(police, chaine3, couleurNoire);



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
                case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                    continuer = 0;
                    default:
                 break;
            }
        }

        position.x = 110;
        position.y = 40;
        SDL_BlitSurface(texte, NULL, ecran, &position );


        SDL_BlitSurface(score[1], NULL, ecran, &position1);
        position1.x = 160;
        position1.y = 200;



       position2.x = 160;
        position2.y = 260;
        SDL_BlitSurface(score[2], NULL, ecran, &position2);

        position3.x = 160;
        position3.y = 310;
        SDL_BlitSurface(score[3], NULL, ecran, &position3);


        SDL_Flip(ecran);
    }

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);

}
