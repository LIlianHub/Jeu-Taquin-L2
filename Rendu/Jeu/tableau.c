#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mouvement.h"

void afficheTab(int ** tab, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if(tab[i][j] != 0)
                printf("%d ",tab[i][j]);
            else
                printf(" "); 
        }
        printf("\n");
    }
}

int ** AlloueTab(int dim)
{
    int ** tab = NULL;
    tab = malloc(dim * sizeof(int*));
    if(tab == NULL)
    {
        printf("\nProbleme allocation tableau\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dim; i++)
    {
        tab[i] = malloc(dim * sizeof(int));
        if(tab[i] == NULL)
        {
            printf("\nProbleme allocation tableau\n");
            exit(EXIT_FAILURE);
        }
    }

    return(tab);
}

void FreeTab(int ** tab, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        free(tab[i]);
    }

    free(tab);
}

/*Test si le tableau donné est l'identité*/
/*Retourne 1 si c'est l'id 0 sinon*/
int CompareTab(int ** tab, int dim)
{
    int valeur = 1;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            //printf("%d - %d\n",valeur,tab[i][j]);
            if(tab[i][j] != valeur)
            {
                if((i != dim-1) || (j != dim-1) || (tab[i][j] != 0))
                    return 0;
            }
            valeur ++;
        }
    }

    return 1;
}

/*Charge un Patern depuis un fichier presetn dans le dossier Patern*/
int ** ChargementPatern(char PaternVoulu[15],int * dim)
{
    FILE * fichier = NULL;

    char Acces[20];
    sprintf(Acces,"Patern/%s",PaternVoulu);
    
    fichier = fopen(Acces,"r");

    if (fichier != NULL) //si le fichier existe
    {
        fscanf(fichier,"%d\n",dim); //premiere ligne correspond au dimension du tableau (voir dans fichier)

        int ** tab = AlloueTab(*dim);

        for (int i = 0; i < *dim; i++)
        {
            for (int j = 0; j < *dim; j++)
            {
                fscanf(fichier,"%d ",&tab[i][j]);
            }
        }

        fclose(fichier);
        return(tab);
    }
    else
    {
        printf("\nErreur Chargement Patern ! Patern Inconnu ou erreur de lecture\n");
        exit(EXIT_FAILURE);
    }  
}

/*Genere un tableau identité de dimension voulu*/
int ** GenereId(int dim)
{
    int ** tab = AlloueTab(dim);
    int valeur = 1;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if((i == dim - 1) && (j == dim - 1))
                tab[i][j] = 0;
            else
                tab[i][j] = valeur;
            valeur ++;
        }
    }

    return(tab);
}

/*Melange un tableau identité avec un nombre de mouvement aleatoire*/
int ** GenereTabRandom(int dim)
{
    //Pour le random
    srand(time(NULL));

    int ** tab = GenereId(dim);

    //Nombre de deplacement fait pour mélanger (entre 1000 et 2000)
    int NbCoup = (rand() % (2000 - 1001)) + 1000;

    int RandDirec;
    int MouvFait;

    int compteur = 0;
    while(compteur < NbCoup)
    {
        MouvFait = 0;
        RandDirec = rand() % 4;

        if (RandDirec == 0)
        {
            if(MouvDroite(tab,dim))
                MouvFait = 1;
        }
        else if (RandDirec == 1)
        {
            if(MouvGauche(tab,dim))
                MouvFait = 1;
        }
        else if (RandDirec == 2)
        {
            if(MouvHaut(tab,dim))
                MouvFait = 1;
        }
        else
        {
            if(MouvBas(tab,dim))
                MouvFait = 1;
        }

        if(MouvFait) //si le mouvement a été possible !
            compteur++;
    }

    return tab;
}

