//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	debug.h : contient les fonctions majeurs utilsants 
//	l'affichage debug.
//*********************************************************



#ifndef DEBUG__
#define DEBUG__

/**
 * Printf : cette fonction permet d'afficher un texte avec une position et une couleur personalisée.
 * @param : *PrintBuffer : votre texte
 * @param : x : position en x du texte
 * @param : y : position en y du texte
 * @param : color : couleur du texte
 */
void Printf(char *PrintBuffer, int x, int y, u32 color);

/**
 * Printfset : cette fonction définie une position et une couleur précise au texte après. Utile si vous souhaitez ajouter des variables au texte.
 * @param : x : position en x du texte
 * @param : y : position en y du texte
 * @param : color : couleur du texte
 */
void Printfset(int x, int y, u32 color);


#endif
