#include <stdio.h>
#include <stdlib.h>

/*Cherche la case vide dans le tableau*/
void DetectZero(int ** tab, int dim, int * x, int * y)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if(tab[i][j] == 0)
            {
                *x = j;
                *y = i;
            }
        }
    }
}

/*Essaye de faire un mouvement a droite
Retourne 1 si reussi 0 sinon*/
int MouvDroite(int ** tab, int dim)
{
    int x,y;
    DetectZero(tab,dim,&x,&y);

    if(x - 1 >= 0) //si on a une valeur a gauche du vide
    {
        tab[y][x] = tab[y][x-1];
        tab[y][x-1] = 0;
        return 1;
    } 

    else
        return 0;
}

/*Essaye de faire un mouvement a gauche
Retourne 1 si reussi 0 sinon*/
int MouvGauche(int ** tab, int dim)
{
    int x,y;
    DetectZero(tab,dim,&x,&y);

    if(x + 1 < dim) 
    {
        tab[y][x] = tab[y][x+1];
        tab[y][x+1] = 0;
        return 1;
    } 

    else
        return 0;
}

/*Essaye de faire un mouvement en bas
Retourne 1 si reussi 0 sinon*/
int MouvBas(int ** tab, int dim)
{
    int x,y;
    DetectZero(tab,dim,&x,&y);

    if(y - 1 >= 0) 
    {
        tab[y][x] = tab[y-1][x];
        tab[y-1][x] = 0;
        return 1;
    } 

    else
        return 0;
}

/*Essaye de faire un mouvement en haut
Retourne 1 si reussi 0 sinon*/
int MouvHaut(int ** tab, int dim)
{
    int x,y;
    DetectZero(tab,dim,&x,&y);

    if(y + 1 < dim) 
    {
        tab[y][x] = tab[y+1][x];
        tab[y+1][x] = 0;
        return 1;
    } 

    else
        return 0;
}

