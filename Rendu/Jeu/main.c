#include "tableau.h"
#include "mouvement.h"
#include "animation.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define DIM_FENETRE 800

int main()
{
    /*Chargement Départ*/

    int ChoixDepart = Acceuil();
    int dim;
    int ** tab = NULL;

    if (ChoixDepart == 2)
    {
        printf("Dimension de Grille voulu : ");
        scanf("%d",&dim);
        while(dim < 2)
        {
            printf("La grille doit être au minimum de taille 2 : ");
            scanf("%d",&dim);
        }

        tab = GenereTabRandom(dim);
    }

    else
    {
        char NomPatern[15];
        printf("Nom Patern voulu : ");
        scanf("%s",NomPatern);
        tab = ChargementPatern(NomPatern,&dim);
    }

    //afficheTab(tab,dim);
    
    /*Initialisation vidéo*/

    if(SDL_Init(SDL_INIT_VIDEO)==-1){
        fprintf(stderr,"\nErreur SDL :%s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(TTF_Init() == -1){
        fprintf(stderr,"\nErreur TTF: %s\n",TTF_GetError() );
        exit(EXIT_FAILURE);
    }

    SDL_Surface * ecran = NULL;
    if((ecran = SDL_SetVideoMode(DIM_FENETRE,DIM_FENETRE,32,SDL_HWSURFACE)) == NULL)
    {
        fprintf(stderr,"Erreur ECran Interface graphique: %s\n",SDL_GetError());
        exit(EXIT_FAILURE) ;
    }

    SDL_WM_SetCaption("Jeu taquin",NULL);

    /*Création d'une police pour l'affichage*/

    TTF_Font * police = NULL;
    int Taille_Police = (int) DIM_FENETRE/(dim*2); //DIM_FENETRE etant la dimension de notre fenetre
    police = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf",Taille_Police);
    
    /*On trace le premier tableau*/

    retrace(tab,ecran,dim,police);

    /*On lance la fonction pause qui prendra les commandes*/

    int victoire = pause(tab,dim,ecran,police);

    /*Si la fin du jeu est provoqué par une victoire on lance l'écran de win*/

    if(victoire)
        EcranWin();

    /*Libération Mémoire*/

    SDL_FreeSurface(ecran);
    TTF_CloseFont(police);
    FreeTab(tab,dim);
    TTF_Quit();
    SDL_Quit();

    return 0;
}