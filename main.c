//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	main.c : partie principale du programme
//*********************************************************


	#include <pspctrl.h>
	#include <pspdebug.h>
	#include <pspdisplay.h>
	#include <pspgu.h>
	#include <pspgum.h>
	#include <pspkernel.h>
	#include <psppower.h>
	#include <pspmoduleinfo.h>
	#include <psprtc.h>
	#include <pspthreadman.h>
	#include <psptypes.h>
	#include <pspuser.h>
	#include <ObjLoader.h>

	#include <png.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <string.h>

	#include <SDL/SDL.h>
	#include <SDL/SDL_image.h>
	#include <SDL/SDL_ttf.h>
	#include <SDL/SDL_rotozoom.h>
	#include <SDL/SDL_mixer.h>

	#include "callbacks.h"
	#include "defines.h"
	#include "graphics.h"
	#include "main.h"

	#include "gu_functions.h"
	#include "sdl_functions.h"
	#include "file.h"
	#include "debug.h"


PSP_MODULE_INFO("Solaris", 0, 1, 1);	// Info sur le programme
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);	// thread

int main(int argc, char* argv[]){

	scePowerSetClockFrequency(333, 333, 166);			// On défini la frequence du CPU/GPU à 333Mhz et le Bus à 166Mhz
	
	SetupCallbacks();									// Callback
	pspDebugScreenInit();								// Initialisation du debug
	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);			// Initialisation SDL
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);	// initialisation de l'audio avec la SDL
	
	SdlLoading();										// Ecran de chargement avec présentation de l'HB
	
	GuInit();											// RE-Initialisation du Gu (du a un conflit entre la SDL et le Gu)
	initGraphics();										// Initialisation du mode graphique (graphics.h)
	
	#ifdef DEBUG6
		SceUID thid;		// Déclaration de la varaiable du Thread des touches durant l'animation (utile lors du debug)
		// Création d'un thread pour permettre de changer de vue, de quitter durant l'execution de l'anim (debug)
		thid = sceKernelCreateThread("touches_thread", touches_thread, 0x18, 0x10000, PSP_THREAD_ATTR_USER, NULL);
		if(thid < 0){printf("Error lors de la creation du thread de changement de vue!\n");sceKernelSleepThread();}
		sceKernelStartThread(thid, 0, NULL);				// Lancement du thread
	#else
		//RIEN (release)
	#endif
	
	
	
	boucle=ACTIVE;
	while(boucle==ACTIVE)						// Boucle principale de l'execution Gu. Reste dans la boucle si ACTIVE quitte si DESACTIVE
	{
		sceGuStart(GU_DIRECT,list);				// Lancement du Gu
		GuClearScreen();						// On efface l'ecran (Gu)
		
		
		/* Gestion de la lumière */
		ScePspFVector3 pos_light0 = {2100.0f,0.0f,0.0f};
		sceGuLight(0,GU_POINTLIGHT,GU_DIFFUSE_AND_SPECULAR,&pos_light0);	//paramètre lumière source un point, diffusion
		sceGuLightColor(0,GU_DIFFUSE_AND_SPECULAR,LIGHT_COLOR);				//couleur de la lumière
		sceGuLightColor(0,GU_SPECULAR,0xffffffff);		
		//sceGuLightAtt(0,1.0f,1.0f,1.0f);		//attenuation de la lumière
		sceGuLightAtt(0,0.0f,1.0f,0.0f);
		sceGuSpecular(4100.0f);
		sceGuAmbient(0xff00000F);
		
		
		/* Gestion de la caméra */
		sceGumMatrixMode(GU_VIEW);
		{
			ScePspFVector3 pos_camera = {camera.x,camera.y,camera.z};				// Position
			ScePspFVector3 rot_camera = {camera.alpha,camera.beta,camera.gamma};	// Angle
			sceGumLoadIdentity();
			sceGumTranslate(&pos_camera);	// Position
			sceGumRotateXYZ(&rot_camera);	// Angle
		}
		
		/* les trajectoire si dessous sont des trajectoires que je voulais garder, ne pas en tenir compte ;) */
		//ScePspFVector3 pos = { cosf((GU_PI/2) + maj * (GU_PI/180)) * LIGHT_DISTANCE, 0, sinf((GU_PI/2) + maj * (GU_PI/180)) * LIGHT_DISTANCE };
		//ScePspFVector3 rot = {maj * 0.79f * (GU_PI/180.0f), maj * 0.98f * (GU_PI/180.0f), maj * 1.32f * (GU_PI/180.0f)};
		
		/* Affichage des modèles 3D*/
		GuPrintModel(obj_soleil,texture_soleil,soleil);								// Soleil
		GuPrintModel(obj_ciel,texture_ciel,ciel);									//ciel
		GuPrintModel(obj_mercure,texture_mercure,mercure);							// Mercure
		GuPrintModel(obj_venus	,texture_venus	,venus);							// Venus
		GuPrintModel(obj_terre	,texture_terre	,terre);							// Terre
		GuPrintModel(obj_lune	,texture_lune	,lune);								// Lune
		GuPrintModel(obj_mars	,texture_mars	,mars);								// Mars
		GuPrintModel(obj_jupiter,texture_jupiter,jupiter);							// Jupiter
		GuPrintModel(obj_anneaux_jupiter,texture_anneaux_jupiter,anneaux_jupiter);	// Anneaux Jupiter
		GuPrintModel(obj_saturne,texture_saturne,saturne);							// Saturne
		GuPrintModel(obj_anneaux_saturne,texture_anneaux_saturne,anneaux_saturne);	// Anneaux Saturne
		//GuPrintModel(obj_titan	,texture_titan	,titan);							// Titan Enlevé car trop petite, rendu de petite tache sur Saturne :S
		GuPrintModel(obj_uranus	,texture_uranus	,uranus);							// Uranus
		GuPrintModel(obj_neptune,texture_neptune,neptune);							// Neptune
		//GuPrintModel(obj_pluton	,texture_neptune,pluton);											// Pluton
		
		boucle=GuAnimation(animation);	// On execute la finction qui gère l'animation de Solaris
		GuRefresh();					// On met à jours l'écran
		
		/*  Mise à jour des informations globale de l'animation (rotation des planètes, mise à jour de la phase de l'animation,...)  */
		animation=animation+coef_animation;
		ciel.beta=ciel.beta+0.0005;
		soleil.beta=soleil.beta+0.005;
		mercure.beta=mercure.beta+0.005;
		venus.beta=venus.beta+0.005;
		lune.beta=lune.beta+0.005;
		mars.beta=mars.beta+0.005;
		jupiter.beta=jupiter.beta+0.005;
		//anneaux_jupiter.beta=anneaux_jupiter.beta+0.005;
		saturne.beta=saturne.beta+0.005;
		//anneaux_saturne.beta=anneaux_saturne.beta+0.005;
		//titan.beta=titan.beta+0.005;
		uranus.beta=uranus.beta+0.005;
		neptune.beta=neptune.beta+0.005;
		//pluton.beta=pluton.beta+0.005;
		
		
		//if(boucle==DESACTIVE)	// Dans une 1er version beta, je permettais de quitter n'importe quand avec un style fondu. Le sujet du concour ayant était précisé, j'ai du enlever cette option
		//{ScreenShot();}// On prend un screen du dernière écran pour faire un fondu
	}
	
	#ifdef DEBUG3
		SDL_Quit();											// On ferme la SDL
		Mix_CloseAudio();									// On ferme la partie audio de la SDL
	#else
		SDL_Quit();										// On ferme la SDL (un bug SDL/Gu oblige à fermer la SDL avant de pouvoir réaficher une image après avoir utilisé le Gu)
		Mix_CloseAudio();								// De même avec la partie audio de la SDL
		
		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);			// Ré-initialisation de la SDL
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);	// Ré-initialisation de l'audio avec la SDL
		GuInit();											// RE-Initialisation du Gu (du a un conflit entre la SDL et le Gu)
		SdlQuitting();										// On lance la procédure de cloture de l'HB (texte de fin)
		SDL_Quit();											// On ferme la SDL
		Mix_CloseAudio();									// On ferme la partie audio de la SDL
		disableGraphics();									// Désactive le graphics
		sceGuFinish();										// Fermeture du Gu
	#endif
	
	
	/*  Vidage de la ram : Objets  */
	FreeModel(&obj_ciel);
	FreeModel(&obj_soleil);
	FreeModel(&obj_mercure);
	FreeModel(&obj_venus);
	FreeModel(&obj_terre);
	FreeModel(&obj_lune);
	FreeModel(&obj_mars);
	FreeModel(&obj_jupiter);
	FreeModel(&obj_saturne);
	//FreeModel(&obj_titan);
	FreeModel(&obj_uranus);
	FreeModel(&obj_neptune);
	//FreeModel(&obj_pluton);
	
	/*  Vidage de la ram : image avec libpng  */
	freeImage(texture_ciel);
	freeImage(texture_soleil);
	freeImage(texture_mercure);
	freeImage(texture_venus);
	freeImage(texture_terre);
	freeImage(texture_lune);
	freeImage(texture_mars);
	freeImage(texture_jupiter);
	freeImage(texture_saturne);
	//freeImage(texture_titan);
	freeImage(texture_uranus);
	freeImage(texture_neptune);
	//freeImage(texture_pluton);
	
	sceKernelExitGame();	// On quitte Solaris, snif^^
	return 0;
}


void Pause(int temp){
sceKernelDelayThread(1000*1000*temp);	// Pause perso en seconde
}

int touches_thread(SceSize args, void *argp){

	// Cette fonction n'apparait pas dans la release, ne pas en tenir compte ;)
	// Juste pour info cette fonction m'a permis de debuguer Solaris, par l'affichage de variables et par des tests de positions de la camera
	
	oldtouch=YES;
	while(1)
	{
		Printfset(1,1,VERT);
		printf2("phase : %f",animation);
		
		Printfset(1,2,VERT);
		printf2("camera : %f  %f  %f",camera.x,camera.y,camera.z);
		
		Printfset(1,3,VERT);
		printf2("ciel : %f  %f  %f",ciel.x,ciel.y,ciel.z);
		
		
		//Printfset(1,3,VERT);
		//printf2("abg : %f  %f  %f",camera.alpha,camera.beta,camera.gamma);
		
		
		#ifdef DEBUG5
			SceCtrlData pad;
			sceCtrlReadBufferPositive(&pad, 1);
			if(pad.Buttons & PSP_CTRL_START)
			{
				boucle=DESACTIVE;
				break;
			}
			if(pad.Buttons & PSP_CTRL_UP)
			{
				camera.z=camera.z+2.8;
				oldtouch=NO;
			}
			if(pad.Buttons & PSP_CTRL_DOWN)
			{
				camera.z=camera.z-2.8;
				oldtouch=NO;
			}
			if(pad.Buttons & PSP_CTRL_LEFT)
			{
				camera.x=camera.x+2.8;
				oldtouch=NO;
			}
			if(pad.Buttons & PSP_CTRL_RIGHT)
			{
				camera.x=camera.x-2.8;
				oldtouch=NO;
			}
			if(pad.Buttons & PSP_CTRL_LTRIGGER)
			{
				camera.beta=camera.beta-0.02;
				oldtouch=NO;
			}
			if(pad.Buttons & PSP_CTRL_RTRIGGER)
			{
				camera.beta=camera.beta+0.02;
				oldtouch=NO;
			}
			if(pad.Buttons & PSP_CTRL_CROSS)
			{
				camera.alpha=camera.alpha+0.02;
				oldtouch=NO;
			}
			if(pad.Buttons & PSP_CTRL_TRIANGLE)
			{
				camera.alpha=camera.alpha-0.02;
				oldtouch=NO;
			}
			if(pad.Buttons & PSP_CTRL_SQUARE)
			{
				camera.gamma=camera.gamma+0.02;
				oldtouch=NO;
			}
			if(pad.Buttons & PSP_CTRL_CIRCLE)
			{
				camera.gamma=camera.gamma-0.02;
				oldtouch=NO;
			}
			
			
			if(oldtouch==NO)
			{
				//sceKernelDelayThread(1000*500);
				oldtouch=YES;
			}
		#else
			sceKernelDelayThread(1000);
		#endif
	}
	
	sceKernelExitDeleteThread(0);
	return 1;
}
