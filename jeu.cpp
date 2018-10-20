#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "fin.h"
#include "jeu.h"
#include "fichiers.h"
#define x1 100
#define x2 155
#define x3 210
#define x4 265
#define x5 320
#define x6 375
#define sco_pl 50
#define sco_ex 20


void init_sans_doublons(int resultat[])  //random
{
	int a=1;
	int i=0;
	// On remplit le tableau de manière à ce qu'il soit trié
	for(i = 0; i< 6; i++){
		resultat[i]=i+a;
	}
}
int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}
void melanger(int tableau[], int taille)
{
	int i=0;
	int nombre_tire=0;
	int temp=0;

	for(i = 0; i< taille;i++)
     {
		nombre_tire=rand_a_b(0,taille);
		// On échange les contenus des cases i et nombre_tire
		temp = tableau[i];
		tableau[i] = tableau[nombre_tire];
		tableau[nombre_tire]=temp;
	 }
}


void comparaison (int combjour[], int T[], int *ex , int *pl)
{
    int i,j, copie[4];
    *pl = 0;
    *ex=0;
    for (i=0; i<4; i++)
    {
        copie[i]=T[i];
    }

    for (i=0; i<4; i++)
    {
          for (j=0; j<4; j++)
          {
               if (combjour [i] == copie[j] && i==j  )
                 {*pl = *pl +1;
                copie[j]=-1;
                 }
                 else
                 {
                     if (combjour [i] == copie[j] )
                     {
                          *ex = *ex + 1;
                    copie[j]=-1;

                     }
                 }
          }
    }

}

void score_joueur(int pl , int ex , int cpt , int *S)
{
    int  bonus =0 ;
if ( (pl != 0) || (ex != 0))
{
    *S =  *S + (pl * sco_pl +  ex * sco_ex) -20  ;
    bonus = 100/(2*2*2*cpt) ;
    *S = *S + bonus ;
}


}

void jouer(SDL_Surface *ecran , FILE* fichier )
{
       SDL_Surface  *menu=NULL,*fond=NULL,*lose=NULL,  *boule[6]={NULL}, *boule_controle[2]={NULL};
    //TTF
    SDL_Surface  *texte = NULL, *textej = NULL , *textet = NULL;
    SDL_Rect position , positionj, positiont , posirect,posifond;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    char *chaine ;

    SDL_Rect  posiboule1, posiboule2, posiboule3, posiboule4, posiboule5, posiboule6;
    int continuer = 1,i , j ,ex , pl , cpt=0 , S=0 ;
    int combjour[4]  ;
    SDL_Rect x , y  , pox, posi_blanc, posi_noir , posib ;
    double temps ;
    clock_t t1, t2;

    srand(time(NULL));
    int T[4] , t[6] ,a=1 , b=7 ;
    init_sans_doublons(t);
    melanger(t,b-a);
    for(i=0; i<4; i++)
        T[i] = t[i] ;

    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();


    ecran = SDL_SetVideoMode(750, 750, 32, SDL_FULLSCREEN);


   SDL_WM_SetCaption("Master Mind", NULL);
    // Coloration de la surface ecran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 218, 190, 97));
    SDL_Flip(ecran);

     fond = IMG_Load("fond.png");
     posifond.x=3;
     posifond.y=5;
     SDL_BlitSurface(fond, NULL, ecran, &posifond);

     boule[1] = IMG_Load("bleu.png");
     posiboule1.x = x1  ;
     posiboule1.y = 575 ;

     boule[2] = IMG_Load("rouge.png");
     posiboule2.x =  x2;
     posiboule2.y =575;

     boule[3] = IMG_Load("noire.png");
     posiboule3.x = x3  ;
     posiboule3.y = 575 ;

     boule[4] = IMG_Load("jaune.png");
     posiboule4.x = x4  ;
     posiboule4.y = 575 ;

     boule[5] = IMG_Load("blanc.png");
     posiboule5.x = x5  ;
     posiboule5.y = 575 ;

     boule[6] = IMG_Load("vert.png");
     posiboule6.x = x6  ;
     posiboule6.y = 575 ;


     boule_controle[1] = IMG_Load("noire_controle.png");
     boule_controle[2] = IMG_Load("blanc_controle.png");

     posib.x=0;
     pox.x = 150 ;
     pox.y = 70 ;
     i=0;
     j=0;


     t1 = clock();

    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {

        SDL_WaitEvent(&event); /* On attend un événement qu'on récupère dans event */
        switch(event.type) /* On teste le type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement QUITTER */
                continuer = 0; /* On met le booléen à 0, donc la boucle va s'arrêter */
                break;
            case SDL_MOUSEBUTTONUP:

                   x.x = event.button.x;
                   y.y = event.button.y;

                    if ( cpt != 10 && pl != 4 )
                    {
                       if ( x.x>x1 && x.x<x2 && y.y > 565 && y.y <630)
                          {
                               posiboule1.x = pox.x ;
                               posiboule1.y = pox.y ;
                               combjour[i]=1;

                          }
                            else
                              if ( x.x>x2 && x.x<x3 && y.y > 565 && y.y <630)
                               {
                                  posiboule2.x = pox.x ;
                                  posiboule2.y = pox.y;
                                  combjour[i]=2;
                               }
                            else
                                if ( x.x>x3 && x.x<x4 && y.y > 565 && y.y <630)
                          {
                               posiboule3.x = pox.x ;
                               posiboule3.y = pox.y ;
                               combjour[i]=3;


                          }
                            else
                              if ( x.x>x4 && x.x<x5 && y.y > 565 && y.y <630)
                               {
                                  posiboule4.x = pox.x ;
                                  posiboule4.y = pox.y;
                                  combjour[i]=4;                                ;
                               }
                               else
                               if ( x.x>x5 && x.x<x6 && y.y > 565 && y.y <630)
                                 {
                               posiboule5.x = pox.x ;
                               posiboule5.y = pox.y ;
                               combjour[i]=5;


                                 }
                            else
                              if ( x.x>x6 && x.x<445 && y.y > 565 && y.y <630)
                               {
                                  posiboule6.x = pox.x ;
                                  posiboule6.y = pox.y;
                                  combjour[i]=6;                                ;
                               }


                          pox.x=pox.x+60 ;
                          i=i+1;
                          j=j+1 ;

                             if ( j==4 )
                             {
                                 comparaison( combjour , T , &ex ,&pl ) ;


                                 for (i=0 ; i<ex ; i++)
                                 {
                                     posi_noir.x = 500+posib.x;
                                     posi_noir.y =pox.y+15;

                                     posib.x=posib.x+50;
                                     SDL_BlitSurface(boule_controle[1], NULL, ecran, &posi_noir);
                                 }

                                  for (i=0 ; i<pl ; i++)
                                 {
                                     posi_blanc.x = 500+posib.x;
                                     posi_blanc.y =pox.y+15;

                                     posib.x=posib.x+50;
                                     SDL_BlitSurface(boule_controle[2], NULL, ecran, &posi_blanc);
                                 }

                                 j=0;
                                 posib.x=0;
                             }

                             if ( pox.x > 350) // pour sauter la ligne
                             {
                                 pox.x = 150 ;
                                 pox.y=pox.y+50 ;
                                 cpt ++ ;
                                 score_joueur( pl , ex , cpt , &S ) ;

                                 i=0;
                             }
                    if (  (cpt == 10)  || (pl==4) )
                       {

                           t2 = clock();
                            temps = ((t2-t1)/CLOCKS_PER_SEC );
                             SDL_Flip(ecran);
                             police = TTF_OpenFont("JOKERMAN.ttf", 50);
    sauvgscores( S , fichier ) ;
    texte = TTF_RenderText_Blended(police, "cliquer sur espace", couleurNoire);
    textej = TTF_RenderText_Blended(police, "onegaishimasu :-) ", couleurNoire);

                        }

                        }



                break;

               // default:

                case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    continuer = 0;
                    default:
                    break;
                case SDLK_SPACE:
                     fin( ecran , S , cpt , pl ,fichier , t1 );
                   // default:
                    break;
            }
            break;



        }


          SDL_BlitSurface(boule[1], NULL, ecran, &posiboule1);
          SDL_BlitSurface(boule[2], NULL, ecran, &posiboule2);
          SDL_BlitSurface(boule[3], NULL, ecran, &posiboule3);
          SDL_BlitSurface(boule[4], NULL, ecran, &posiboule4);
          SDL_BlitSurface(boule[5], NULL, ecran, &posiboule5);
          SDL_BlitSurface(boule[6], NULL, ecran, &posiboule6);

          SDL_BlitSurface(boule_controle[1], NULL, ecran, &posi_noir);
          SDL_BlitSurface(boule_controle[2], NULL, ecran, &posi_blanc);


        position.x = 135;
        position.y = 200;
        SDL_BlitSurface(texte, NULL, ecran, &position);

        positionj.x = 135;
        positionj.y = 300;
        SDL_BlitSurface(textej, NULL, ecran, &positionj);




          SDL_Flip(ecran);

   }

         TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);


}



