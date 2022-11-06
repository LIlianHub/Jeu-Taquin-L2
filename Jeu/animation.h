#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
/*Si on ne met pas ces includes, le fichier .h ne reconnait pas la SDL*/

int Acceuil();
int pause(int ** tab, int dim, SDL_Surface * ecran, TTF_Font * police);
void EcranWin();
void retrace(int ** tab, SDL_Surface * ecran, int dim, TTF_Font * police);

