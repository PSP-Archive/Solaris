//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	file.c : contient les fonctions majeurs qui opèrent 
//	sur les fichiers
//*********************************************************



	#include <string.h>
	#include <pspdebug.h> 
	#include <pspkernel.h>
	#include <stdio.h>
	#include <string.h>
	#include <sys/types.h>
	#include <sys/unistd.h>
	
	#include "file.h"
	

int fsize(char *fn){

	FILE * pFile;
	int lSize;
	
	pFile = fopen (fn , "rb");					// Ouverture du fichier
	if (pFile==NULL){return -1;}				// Vérification que le fichier existe
	fseek (pFile , 0 , SEEK_END);				// On lit le fichier
	lSize = ftell (pFile);
	rewind (pFile);
	fclose(pFile);								// On a terminé, on ferme le fichier
	return lSize;								// On retourne la taille
}
void VerificationFichiers(char *CheminFichier){

	char buf[MAXPATHLEN];
	char chemin[500];
	
	strcpy(chemin, getcwd(buf, MAXPATHLEN));	// On recupère le dossier de lancement de l'EBOOT
	strcat(chemin, CheminFichier);				// On ajoute le chemin du fichier à vérifier
	sceKernelDelayThread(1000*25);				// Courte pause

	if(fsize(chemin) < 0)						// Si le fichier n'existe pas
	{
		pspDebugScreenInit();					// On initialise l'affichage en debug
		pspDebugScreenClear();					// On efface l'écran
		pspDebugScreenSetTextColor(0x000000ff);	// Couleur du texte (rouge)
		pspDebugScreenPrintf("\nErreur : %s\nUn fichier est manquant!", chemin);
		sceKernelDelayThread(1000*1000*4);		// Courte pause
		sceKernelExitGame();					// On quitte
	}
}
void CheckUp(void){
	VerificationFichiers("/data/objs/ciel.obj");	// On vérifie l'existance du fichier
	VerificationFichiers("/data/objs/soleil.obj");
	VerificationFichiers("/data/objs/mercure.obj");
	VerificationFichiers("/data/objs/venus.obj");
	VerificationFichiers("/data/objs/terre.obj");
	VerificationFichiers("/data/objs/lune.obj");
	VerificationFichiers("/data/objs/mars.obj");
	VerificationFichiers("/data/objs/jupiter.obj");
	VerificationFichiers("/data/objs/saturne.obj");
	VerificationFichiers("/data/objs/titan.obj");
	VerificationFichiers("/data/objs/uranus.obj");
	VerificationFichiers("/data/objs/neptune.obj");
	VerificationFichiers("/data/objs/pluton.obj");
	
	VerificationFichiers("/data/textures/ciel.png");
	VerificationFichiers("/data/textures/soleil.png");
	VerificationFichiers("/data/textures/mercure.png");
	VerificationFichiers("/data/textures/venus.png");
	VerificationFichiers("/data/textures/terre.png");
	VerificationFichiers("/data/textures/lune.png");
	VerificationFichiers("/data/textures/mars.png");
	VerificationFichiers("/data/textures/jupiter.png");
	VerificationFichiers("/data/textures/saturne.png");
	VerificationFichiers("/data/textures/titan.png");
	VerificationFichiers("/data/textures/uranus.png");
	VerificationFichiers("/data/textures/neptune.png");
	VerificationFichiers("/data/textures/pluton.png");
	
	VerificationFichiers("/data/images/xtreamlua.png");
	VerificationFichiers("/data/images/decompte.png");
	VerificationFichiers("/data/images/end.png");
	VerificationFichiers("/data/images/fondu2.png");
	VerificationFichiers("/data/images/solaris.png");
	
	VerificationFichiers("/data/sounds/decompte.wav");
}
