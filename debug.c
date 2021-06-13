//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	debug.c : contient les fonctions majeurs utilsants 
//	l'affichage debug.
//*********************************************************



	#include <pspdebug.h>
	#include "debug.h"

 
 void Printf(char *PrintBuffer, int x, int y, u32 color){
	pspDebugScreenSetXY(x,y);				// position du texte
	pspDebugScreenSetTextColor(color);		// couleur du texte
	pspDebugScreenPrintf(PrintBuffer);		// on affiche
}
void Printfset(int x, int y, u32 color){
	pspDebugScreenSetXY(x,y);				// position du texte
	pspDebugScreenSetTextColor(color);		// couleur du texte
}
