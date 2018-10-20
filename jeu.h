/*
jeu.h



Rôle : prototypes des fonctions du jeu.
*/

#ifndef DEF_JEU
#define DEF_JEU

    void jouer(SDL_Surface* ecran ,FILE* fichier );
    void score_joueur(int pl , int ex , int cpt , int *S);
    void comparaison (int combjour[], int T[], int *ex , int *pl);
    void melanger(int tableau[], int taille);
    int rand_a_b(int a, int b);
    void init_sans_doublons(int resultat[]);


#endif
