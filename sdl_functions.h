//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	fonctions_sdl.c : contient les fonctions majeurs 
//	utilsants la sdl
//*********************************************************



#ifndef SDLF__
#define SDLF__

	#include <pspthreadman.h>
	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
	#include <SDL/SDL_ttf.h>
	#include <SDL/SDL_rotozoom.h>
	#include <SDL/SDL_mixer.h>
	#include <ObjLoader.h>
	
	#include "gu_functions.h"
	#include "defines.h"
	#include "file.h"
	
	
/**
 * SdlLoading : cette fonction execute la présentation.chargement de l'HB
 * @param : aucun paramètre.
 */
void SdlLoading(void);

/**
 * SdlQuitting : cette fonction execute la cloture de l'HB
 * @param : aucun paramètre.
 */
void SdlQuitting(void);

/**
 * SdlPlaySound : cette fonction lit un fichier sonore
 * @param : son : numero du son à jouer
 */
void SdlPlaySound(int son);

/** Fondu : Fait un fondu 
 * @param : utiliser CHARGE ou DEChARGE pour le sens du fondu
 * @param : tempo ne doit pas  dépaser 1000, risque de bug...
 * 	Fondu(DECHARGE,500,35,ecran,chargement,fondu,&P_background);
 *	Fondu(CHARGE,0,35,ecran,menu_e,fondu,&P_background);
 */
void Fondu(int sens, int tempo, int vitesse, SDL_Surface *ecran, SDL_Surface *image, SDL_Surface *fondu, SDL_Rect *P_background);


#endif
