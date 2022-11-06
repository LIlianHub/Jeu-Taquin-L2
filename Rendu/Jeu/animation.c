#include "tableau.h"
#include "mouvement.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define DIM_FENETRE 800

void retrace(int ** tab, SDL_Surface * ecran, int dim, TTF_Font * police)
{
    /*OUtil pour Tableau universelle (taille n * n)*/

    int DimCase = (int)(DIM_FENETRE / dim); //DIM_FENETRE etant la taille de notre fenetre

    /*Creation d'une surface pour dessiner*/

    SDL_Surface * rectangle = NULL;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,DimCase,DimCase,32,0,0,0,0);
    SDL_Rect position;
    position.x=0;
    position.y=0;

    /*Creation d'une surface pour ecrire*/

    SDL_Surface * texte = NULL;
    SDL_Rect positionTexte;
    positionTexte.x= DimCase/4; //pour centrer la police
    positionTexte.y= DimCase/4;
    SDL_Color textColor; //couleur pour la police
    textColor.r = 0;
    textColor.g = 0;
    textColor.b = 0;

    char OutilTexte[5];

    /*On Trace le tableau voulu*/

    int change = 0; //permet de faire un damier

    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            if(change == 0) //soit une case gris foncé
            {
                SDL_FillRect(rectangle, NULL,SDL_MapRGB(rectangle->format,200,200,200));
                change = 1;
            }
            
            else //soit une case gris clair
            {
                SDL_FillRect(rectangle, NULL,SDL_MapRGB(rectangle->format,220,220,220));
                change = 0;
            }

            SDL_BlitSurface(rectangle,NULL,ecran,&position);
            position.x += DimCase;

            if(tab[i][j] != 0) //si l'element du tableau n'est pas la case vide alors on l'affiche dans la fenetre
            {
                sprintf(OutilTexte,"%d",tab[i][j]); //cast int vers str
                texte = TTF_RenderText_Blended(police, OutilTexte, textColor);
                SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
            }
            positionTexte.x += DimCase;
        }

        if(dim%2 == 0)
        {
            if(change == 0)
                change = 1;
            else
                change = 0;
        }
        position.y += DimCase;
        position.x = 0;
        positionTexte.x = DimCase/4;
        positionTexte.y += DimCase;
    }
    
    SDL_Flip(ecran); //on refresh les changements
    SDL_FreeSurface(rectangle);
    SDL_FreeSurface(texte);
}

void EcranWin()
{
    /*On crée une nouvelle fenetre pour l'écran de victoire*/

    SDL_Surface * ecran_victoire = NULL;
    if((ecran_victoire = SDL_SetVideoMode(600,400,32,SDL_HWSURFACE)) == NULL)
    {
        fprintf(stderr,"\nErreur Ecran Interface graphique victoire : %s\n",SDL_GetError());
        exit(EXIT_FAILURE) ;
    }
    SDL_WM_SetCaption("Victoire !",NULL);

    /* On charge l'image de même dimension que la fenetre pour un meilleur rendu*/
    SDL_Surface * Image = NULL ;
    Image = SDL_LoadBMP("victoire.bmp");
    SDL_BlitSurface(Image,NULL,ecran_victoire,NULL);
    SDL_Flip(ecran_victoire);

    /*On fait tourner le programme tant que le joueur a pas fermé la fenetre*/
    int Programme_tourne = 1;
    SDL_Event event;
    while(Programme_tourne)
    {
        SDL_WaitEvent(&event) ;
        switch(event.type)
        {
            case SDL_QUIT:
                Programme_tourne = 0;
                break;
            
            default:
                Programme_tourne = 1;
        }
    }

    SDL_FreeSurface(ecran_victoire);
} 


int pause(int ** tab, int dim, SDL_Surface * ecran, TTF_Font * police)
{
    /*C'est ici qu'on va recuperer les entrées clavier*/
    int Programme_tourne = 1 ;
    SDL_Event event;
    while(Programme_tourne)
    {
        SDL_WaitEvent(&event) ;
        switch(event.type)
        {
            case SDL_QUIT: //si on ferme la fenetre
                Programme_tourne = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_RIGHT: //pression sur la touche fleche de droite
                        if (MouvDroite(tab,dim))//si le mouvement a pu être effectué
                        {
                            retrace(tab,ecran,dim,police); //on actualise la grille et la fenetre
                            if(CompareTab(tab,dim)) //si la grille est l'identité
                            {
                                return 1; //alors il a fini le jeu
                            }
                        }
                        break;
                    
                    case SDLK_LEFT: 
                        if (MouvGauche(tab,dim))
                        {
                            retrace(tab,ecran,dim,police);
                            if(CompareTab(tab,dim))
                            {
                                return 1;
                            }
                        }
                        break;
                    
                    case SDLK_UP: 
                        if (MouvHaut(tab,dim))
                        {
                            retrace(tab,ecran,dim,police);
                            if(CompareTab(tab,dim))
                            {
                                return 1;
                            }
                        }
                        break;
                    
                    case SDLK_DOWN:
                        if (MouvBas(tab,dim))
                        {
                            retrace(tab,ecran,dim,police);
                            if(CompareTab(tab,dim))
                            {
                                return 1;
                            }
                        }
                        break;
                    
                    default:
                        break;
                }
                break;

            default :
                Programme_tourne = 1 ;
        }
    }

    return 0; //si la fenetre est fermé avec la croix
}

int Acceuil()
{
    printf("Bienvenue sur le jeu de Taquin de Lilian et Maxime:\n[Ce jeu se joue avec les flèches directionnelles]\nSouhaitez-vous :\n1- Charger une grille déjà mélangée\n2- Générer une grille de manière aléatoire\n3- Quitter le Jeu");
    printf("\nSéléctionnez votre choix (1, 2 ou 3): ");
    int choix = 0;
    scanf("%d",&choix);

    while ((choix != 1) && (choix != 2) && (choix != 3)) //si mauvaise entrée
    {
        printf("Séléctionnez une entrée valide (1, 2 ou 3): ");
        scanf("%d",&choix);
    }
    
    if(choix == 3)
        exit(-1);
    else
        return choix;
}
