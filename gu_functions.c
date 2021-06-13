//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	gu_fonctions.c : contient les fonctions majeurs liées
//	au Gu
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
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <png.h>
	#include <string.h>

	#include "defines.h"
	#include "sdl_functions.h"
	#include "gu_functions.h"
	#include "font.c"
	#include "graphics.h"
	

void GuInit(void){

	sceGuInit();												// Initialisation du Gu, puis paramétrage du Gu
	gumInit();
	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,(void*)0,512);
	sceGuDispBuffer(480,272,(void*)0x88000,512);
	sceGuDepthBuffer((void*)0x110000,512);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(0xc350,0x2710);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	//sceGuEnable(GU_CULL_FACE);
	//sceGuEnable(GU_CLIP_PLANES);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_LIGHTING);
	sceGuEnable(GU_LIGHT0);
	//sceGuEnable(GU_LIGHT1);
	
	sceGuFinish();
	sceGuSync(0,0);
	sceGuDisplay(GU_TRUE);
	
	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(75.0f,16.0f/9.0f,1.0f,18000.0f);	// Valeur très grande, obligatoire pour ne pas avoir de bug (plan xyz utilisé très grand)
}
void GuClearScreen(void){

	sceGuClearColor(0x000000);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
}
void GuRefresh(void){

	sceGuFinish();
	sceGuSync(0,0);
	sceGuSwapBuffers();
}
void GuPositionInit(void){

	ciel.x= 0.0;		// Position du modèle ciel en x
	ciel.y= 0.0;		// Position du modèle ciel en y
	ciel.z= -8000.0;	// Position du modèle ciel en z
	ciel.alpha= 0.0;	// Angle du modèle ciel en alpha
	ciel.beta = 0.0;	// Angle du modèle ciel en beta
	ciel.gamma= 0.0;	// Angle du modèle ciel en gamma
	
	soleil.x= 0.0;
	soleil.y= 0.0;
	soleil.z= 6000.0;
	soleil.alpha= 0.0;
	soleil.beta = 0.0;
	soleil.gamma= 0.0;
	
	mercure.x= 0.0;
	mercure.y= 0.0;
	mercure.z= DISTANCE_MERCURE;
	mercure.alpha= 0.0;
	mercure.beta = 0.0;
	mercure.gamma= 0.0;
	
	venus.x=0;
	venus.y=0;
	venus.z= DISTANCE_VENUS;
	venus.alpha= 0.0;
	venus.beta = 0.0;
	venus.gamma= 0.0;
	
	terre.x=0;
	terre.y=0;
	terre.z= DISTANCE_TERRE;
	terre.alpha= 0.0;
	terre.beta = -1.0;
	terre.gamma= 0.0;
	
	lune.x= 30.0;
	lune.y= 5.0;
	lune.z= DISTANCE_TERRE_LUNE;
	lune.alpha= 0.0;
	lune.beta = 0.0;
	lune.gamma= 0.0;
	
	mars.x=-350.0;
	mars.y=0;
	mars.z= DISTANCE_MARS;
	mars.alpha= 0.0;
	mars.beta = 0.0;
	mars.gamma= 0.0;
	
	jupiter.x=0;
	jupiter.y=0;
	jupiter.z= DISTANCE_JUPITER;
	jupiter.alpha= 0.0;
	jupiter.beta = 0.0;
	jupiter.gamma= 0.0;
	
	anneaux_jupiter.x= 0.0;
	anneaux_jupiter.y= 0.0;
	anneaux_jupiter.z= DISTANCE_JUPITER;
	anneaux_jupiter.alpha= 0.0;
	anneaux_jupiter.beta = 0.0;
	anneaux_jupiter.gamma= 0.0;
	
	saturne.x=0;
	saturne.y=0;
	saturne.z= DISTANCE_SATURNE;
	saturne.alpha= 0.0;
	saturne.beta = 0.0;
	saturne.gamma= 0.0;
	
	anneaux_saturne.x= 0.0;
	anneaux_saturne.y= 0.0;
	anneaux_saturne.z= DISTANCE_SATURNE;
	anneaux_saturne.alpha= 0.0;
	anneaux_saturne.beta = 0.0;
	anneaux_saturne.gamma= 0.0;
	
	uranus.x=100;
	uranus.y=0;
	uranus.z= DISTANCE_URANUS;
	uranus.alpha= 0.0;
	uranus.beta = 0.0;
	uranus.gamma= 0.0;
	
	neptune.x=200;
	neptune.y=0;
	neptune.z= DISTANCE_NEPTUNE;
	neptune.alpha= 0.0;
	neptune.beta = 0.0;
	neptune.gamma= 0.0;

	camera.x= -501.4;
	camera.y= 0.0;
	camera.z= 1418.2;
	camera.alpha= 0.0;
	camera.beta= -0.34;
	camera.gamma=18.9;
   
}
void GuLoadModel(void){
	
	/* Ciel */
	ReadOBJModel ("data/objs/ciel.obj", &obj_ciel);			// Chargement du modèle
	texture_ciel = loadImage("data/textures/ciel.png");		// Puis de sa texture
	
	/* Soleil */
	ReadOBJModel ("data/objs/soleil.obj", &obj_soleil);
	texture_soleil = loadImage("data/textures/soleil.png");
	
	/* Mercure */
	ReadOBJModel ("data/objs/mercure.obj", &obj_mercure);
	texture_mercure = loadImage("data/textures/mercure.png");
	
	/* Vénus */
	ReadOBJModel ("data/objs/venus.obj", &obj_venus);
	texture_venus = loadImage("data/textures/venus.png");
	
	/* Terre */
	ReadOBJModel ("data/objs/terre.obj", &obj_terre);
	texture_terre = loadImage("data/textures/terre.png");
	
	/* Lune */
	ReadOBJModel ("data/objs/lune.obj", &obj_lune);
	texture_lune = loadImage("data/textures/lune.png");
	
	/* Mars */
	ReadOBJModel("data/objs/mars.obj", &obj_mars);
	texture_mars = loadImage("data/textures/mars.png");
	
	/* Jupiter */
	ReadOBJModel ("data/objs/jupiter.obj", &obj_jupiter);
	texture_jupiter = loadImage("data/textures/jupiter.png");
	
	/* Anneaux_Jupiter */
	ReadOBJModel ("data/objs/anneaux_jupiter.obj", &obj_anneaux_jupiter);
	texture_anneaux_jupiter = loadImage("data/textures/anneaux_jupiter.png");
	
	/* Saturne */
	ReadOBJModel ("data/objs/saturne.obj", &obj_saturne);
	texture_saturne = loadImage("data/textures/saturne.png");
	
	/* Anneaux_Saturne */
	ReadOBJModel ("data/objs/anneaux_saturne.obj", &obj_anneaux_saturne);
	texture_anneaux_saturne = loadImage("data/textures/anneaux_saturne.png");
	
	/* Uranus */
	ReadOBJModel ("data/objs/uranus.obj", &obj_uranus);
	texture_uranus = loadImage("data/textures/uranus.png");
	
	/* Neptune */
	ReadOBJModel ("data/objs/neptune.obj", &obj_neptune);
	texture_neptune = loadImage("data/textures/neptune.png");
}
void GuPrintModel(struct obj_model_t obj_model,Image *texture,position model){

	sceGumMatrixMode(GU_MODEL);											// Paramétrage du GU
	sceGumLoadIdentity();
	sceGuTexMode(GU_PSM_8888, 0 ,0 ,0);
	sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGB);
	sceGuTexFilter(GU_LINEAR, GU_LINEAR);
	sceGuTexScale(1.0f, -1.0f);
	
	sceGuTexImage(0,texture->textureWidth,texture->textureHeight,texture->textureWidth,texture->data);	// texture
	
	ScePspFVector3 pos_model = {model.x,model.y,model.z};				// Position du modèle (une mise à jours sera apportée à cette partie après le concours)
	ScePspFVector3 rot_model = {model.alpha,model.beta,model.gamma};	// Rotation du modèle
		sceGumTranslate(&pos_model);
		sceGumRotateXYZ(&rot_model);
	
	RenderOBJModel(&obj_model);											// Affichage du modèle
}
void GuPrintf(const char* text, int x, int y, unsigned int color, int fw){

	sceGuDisable(GU_DEPTH_TEST);	// Paramétrage du GU
	sceGuEnable(GU_BLEND);
	sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuTexMode(GU_PSM_8888, 0, 0, 0);
	sceGuTexImage(0, 256, 128, 256, font);
	sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
	sceGuTexEnvColor(0x0);
	sceGuTexOffset(0.0f, 0.0f);
	sceGuTexScale(1.0f / 256.0f, 1.0f / 128.0f);
	sceGuTexWrap(GU_REPEAT, GU_REPEAT);
	sceGuTexFilter(GU_NEAREST, GU_NEAREST);
	
	int len = (int)strlen(text);
	if(!len)
	{return;}

	typedef struct {
		float s, t;
		unsigned int c;
		float x, y, z;
	} VERT2;

	VERT2* v = sceGuGetMemory(sizeof(VERT2) * 2 * len);

	int i;
	for(i = 0; i < len; i++)	// Découpe de la font pour extraire le caractère
	{
		unsigned char c = (unsigned char)text[i];
		if(c < 32)
		{
			c = 0;
		}
		else if(c >= 128)
		{
			c = 0;
		}
		
		int tx = (c & 0x0F) << 4;
		int ty = (c & 0xF0);
		
		VERT2* v0 = &v[i*2+0];
		VERT2* v1 = &v[i*2+1];
		
		v0->s = (float)(tx + (fw ? ((16 - fw) >> 1) : ((16 - fontwidthtab[c]) >> 1)));
		v0->t = (float)(ty);
		v0->c = color;
		v0->x = (float)(x);
		v0->y = (float)(y);
		v0->z = 0.0f;
		
		v1->s = (float)(tx + 16 - (fw ? ((16 - fw) >> 1) : ((16 - fontwidthtab[c]) >> 1)));
		v1->t = (float)(ty + 16);
		v1->c = color;
		v1->x = (float)(x + (fw ? fw : fontwidthtab[c]));
		v1->y = (float)(y + 16);
		v1->z = 0.0f;
		
		x += (fw ? fw : fontwidthtab[c]);
	}

	// Affichage du caractère
	sceGumDrawArray(GU_SPRITES, GU_TEXTURE_32BITF | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D,	len * 2, 0, v);
	sceGuEnable(GU_DEPTH_TEST);
}
void ScreenShot(void){

	saveImage("data/end.png", getVramDisplayBuffer(),SCREEN_WIDTH,SCREEN_HEIGHT,PSP_LINE_SIZE,0);	// Recupération du Buffer video
	sceKernelDelayThread(1000*1000*2); // Petite pause pour ne pas faire planter le programme
}
void Introduction(void){
	
	int i;			// Variable d'incrémentation
	int etape=1;
	int ty=272;		// Coordonée en y du texte
	int ty2;		// Coordonée en y du texte (pour effectuer des calculs)
	couleur=T8;		// Couleur initiale du texte
	
	
	/* les textes */
	strcpy(text[1].s,"        Voyager 1 & 2...");	// On copie le texte en mémoire
	strcpy(text[2].s," a la decouverte de l'espace...");
	strcpy(text[3].s,"      Voyager 1 et 2 sont des sondes spatiales");
	strcpy(text[4].s," ayant realisees depuis 1977 de nombreuses decouvertes ");
	strcpy(text[5].s,"      sur Jupiter, Saturne, Uranus et Neptune.");
	strcpy(text[6].s,"  Aujourd'hui, Toujours en etat de fonctionnement,");
	strcpy(text[7].s,"   ces 2 sondes sont plus eloignees de la Terre");
	strcpy(text[8].s,"      que tous autres engin jamais lances par ");
	strcpy(text[9].s,"       l'Homme dans l'espace, et continues ");
	strcpy(text[10].s,"   de s'eloigner a la vitesse de 17 km/seconde");
	strcpy(text[11].s,"          vers l'espace interstellaire, ");
	strcpy(text[12].s,"             transportant chaqu'une,");
	strcpy(text[13].s,"    un disque de cuivre plaque or contennant");
	strcpy(text[14].s,"       des informations sur l'humanite...");
	strcpy(text[15].s," ");
	strcpy(text[16].s," ");
	strcpy(text[17].s," ");
	strcpy(text[18].s,"          Nous sommes le 20 aout 1977, ");
	strcpy(text[19].s,"        au Kennedy Space Center en Floride,");
	strcpy(text[20].s,"         abort du lanceur Titan-Centaur,");
	strcpy(text[21].s,"quelques minutes avant le lancement de Voyager2 ...");
	
	while(1)								// Boucle d'affichage en dégradé du texte avec le Gu
	{
		sceGuStart(GU_DIRECT,list);			// On démarre le Gu
		GuClearScreen();					// On efface l'écran
		
		if(etape==1)	// Affichage du titre et sujet de Solaris
		{
			if(ty>120)	// Si on est en bas de l'écran
			{
				if((ty<=272) && (ty>267)){couleur= T14;}		// On défini la couleur de dégradé du texte compris entre les 2 valeurs du if
				else if((ty<=267) && (ty>262)){couleur= T13;}	// De même mais pour une couleur/position du texte differente
				else if((ty<=262) && (ty>257)){couleur= T12;}	// ...
				else if((ty<=257) && (ty>252)){couleur= T11;}
				else if((ty<=252) && (ty>247)){couleur= T10;}
				else if((ty<=247) && (ty>242)){couleur= T9;}
				else if((ty<=242) && (ty>237)){couleur= T8;}
				else if((ty<=237) && (ty>232)){couleur= T7;}
				else if((ty<=232) && (ty>227)){couleur= T6;}
				else if((ty<=227) && (ty>222)){couleur= T5;}
				else if((ty<=222) && (ty>217)){couleur= T4;}
				else if((ty<=217) && (ty>212)){couleur= T3;}
				else if((ty<=212) && (ty>207)){couleur= T2;}
				else if((ty<=207) && (ty>202)){couleur= T1;}
				else{couleur= T0;}
			}
			else		// Sinon, si on est en haut de l'écran
			{			
				if((ty<=5) && (ty>0)){couleur= T14;}			// On défini la couleur de dégradé du texte compris entre les 2 valeurs du if
				else if((ty<=10) && (ty>5)){couleur= T13;}		// De même mais pour une couleur/position du texte differente
				else if((ty<=15) && (ty>10)){couleur= T12;}		// ...
				else if((ty<=20) && (ty>15)){couleur= T11;}		
				else if((ty<=25) && (ty>20)){couleur= T10;}
				else if((ty<=30) && (ty>25)){couleur= T9;}
				else if((ty<=35) && (ty>30)){couleur= T8;}
				else if((ty<=40) && (ty>35)){couleur= T7;}
				else if((ty<=45) && (ty>40)){couleur= T6;}
				else if((ty<=50) && (ty>45)){couleur= T5;}
				else if((ty<=55) && (ty>50)){couleur= T4;}
				else if((ty<=60) && (ty>55)){couleur= T3;}
				else if((ty<=65) && (ty>60)){couleur= T2;}
				else if((ty<=70) && (ty>65)){couleur= T1;}
				else{couleur= T0;}
			}
			
			GuPrintf(text[1].s,10,ty,couleur,14);				// Affichage du sujet de Solaris
			GuPrintf(text[2].s,10,ty+40,couleur,14);			// Le tout sur 2 lignes^^
			GuRefresh();										// On met à jour l'écran
			
			sceKernelDelayThread(1000*15);						// Une petite pause qui temporise le défilement du texte
			if(ty==120){sceKernelDelayThread(1000*1000*3);}		// Une petite pause qui stop le texte au milieu de l'écran
			ty--;												// On fait défiler le texte
			
			if(ty==0){etape=2; ty=190;}							// Si le texte est sortie de l'écran, on passe à la suite
		}
		else	// Affichage de la présentation de Solaris
		{
			for(i=3;i<=21;i++)	// On a 21-2 phrases en stock à afficher (que se soit de dans ou hors de l'écran)
			{
				ty2=ty+30*i;	// On doit adapter la position du texte en fonction du [i] (pour ne pas attendre 1min que la première phrase arrive à l'écran)
				
				if(ty2>267){couleur= T14;}						// On défini la couleur de dégradé du texte compris entre les 2 valeurs du if
				else if((ty2<=267) && (ty2>262)){couleur= T13;}	// De même mais pour une couleur/position du texte differente
				else if((ty2<=262) && (ty2>257)){couleur= T12;}	// ...
				else if((ty2<=257) && (ty2>252)){couleur= T11;}
				else if((ty2<=252) && (ty2>247)){couleur= T10;}
				else if((ty2<=247) && (ty2>242)){couleur= T9;}
				else if((ty2<=242) && (ty2>237)){couleur= T8;}
				else if((ty2<=237) && (ty2>232)){couleur= T7;}
				else if((ty2<=232) && (ty2>227)){couleur= T6;}
				else if((ty2<=227) && (ty2>222)){couleur= T5;}
				else if((ty2<=222) && (ty2>217)){couleur= T4;}
				else if((ty2<=217) && (ty2>212)){couleur= T3;}
				else if((ty2<=212) && (ty2>207)){couleur= T2;}
				else if((ty2<=207) && (ty2>202)){couleur= T1;}
				else if((ty2<=202) && (ty2>70)){couleur= T0;}
				
				else if(ty2<=5){couleur= T14;}					// La même chose mais pour le haut de l'écran
				else if((ty2<=10) && (ty2>5)){couleur= T13;}	
				else if((ty2<=15) && (ty2>10)){couleur= T12;}
				else if((ty2<=20) && (ty2>15)){couleur= T11;}
				else if((ty2<=25) && (ty2>20)){couleur= T10;}
				else if((ty2<=30) && (ty2>25)){couleur= T9;}
				else if((ty2<=35) && (ty2>30)){couleur= T8;}
				else if((ty2<=40) && (ty2>35)){couleur= T7;}
				else if((ty2<=45) && (ty2>40)){couleur= T6;}
				else if((ty2<=50) && (ty2>45)){couleur= T5;}
				else if((ty2<=55) && (ty2>50)){couleur= T4;}
				else if((ty2<=60) && (ty2>55)){couleur= T3;}
				else if((ty2<=65) && (ty2>60)){couleur= T2;}
				else if((ty2<=70) && (ty2>65)){couleur= T1;}
				else{couleur= T0;}
				
				GuPrintf(text[i].s,10,ty2,couleur,9);	// On affiche la ligne de texte [i]
			}
			GuRefresh();								// On met à jour l'écran
			
			sceKernelDelayThread(1000*70);				// Une petite pause qui temporise le défilement du texte
			ty--;										// On fait défiler le texte
		}
		
		if(ty==-475){break;}			// Si ty arrive à -475, on quitte cette fonction
	}

}
void Exit(void){

	int i;			// Variable d'incrémentation
	int ty=272;		// Coordonée en y du texte
	int ty2;		// Coordonée en y du texte (pour effectuer des calculs)
	couleur=T8;		// Couleur initiale du texte
	
	/* les textes */
	strcpy(text[22].s,"  Selon les estimations des ingenieurs de la NASA,");	// On copie le texte en mémoire
	strcpy(text[23].s,"       Voyager 1&2 ont encore assez d'energie");
	strcpy(text[24].s,"          pour fonctionner jusqu'en 2020.");
	strcpy(text[25].s,"     A cette date, elle seront respectivement");
	strcpy(text[26].s,"  a 20 et 16,8 milliards de kilometres du soleil!");
	strcpy(text[27].s," Des distances impensables, mais encore suffisantes");
	strcpy(text[28].s,"pour permettre aux 2 sondes de realiser des mesures");
	strcpy(text[29].s," la ou seul la pense humaine a pu aller a ce jour...");
	strcpy(text[30].s,"");
	strcpy(text[31].s,"");
	strcpy(text[32].s,"");
	strcpy(text[33].s,"");
	strcpy(text[34].s,"");
	strcpy(text[35].s,"");
	strcpy(text[36].s,"");
	strcpy(text[37].s,"                   Solaris v1.1");
	strcpy(text[38].s,"                      by PEB");
	strcpy(text[39].s,"                    XtRa Prod.");
	strcpy(text[40].s,"");
	strcpy(text[41].s,"");
	strcpy(text[42].s,"                 http://pebdev.eu");
	strcpy(text[43].s,"                   xtreamlua.com");

	while(1)						// Boucle d'affichage en dégradé du texte avec le Gu
	{
		sceGuStart(GU_DIRECT,list);	// On démarre le Gu
		GuClearScreen();			// On efface l'écran
		
		for(i=22;i<=43;i++)			// On a 43-21 phrases en stock à afficher (que se soit de dans ou hors de l'écran)
		{
			ty2=((ty+30*i)-645);	// On doit adapter la position du texte en fonction du [i] (pour ne pas attendre 1min que la première phrase arrive à l'écran)
			
			if(ty2>267){couleur= T14;}						// On défini la couleur de dégradé du texte compris entre les 2 valeurs du if
			else if((ty2<=267) && (ty2>262)){couleur= T13;}	// De même mais pour une couleur/position du texte differente
			else if((ty2<=262) && (ty2>257)){couleur= T12;}	// ...
			else if((ty2<=257) && (ty2>252)){couleur= T11;}
			else if((ty2<=252) && (ty2>247)){couleur= T10;}
			else if((ty2<=247) && (ty2>242)){couleur= T9;}
			else if((ty2<=242) && (ty2>237)){couleur= T8;}
			else if((ty2<=237) && (ty2>232)){couleur= T7;}
			else if((ty2<=232) && (ty2>227)){couleur= T6;}
			else if((ty2<=227) && (ty2>222)){couleur= T5;}
			else if((ty2<=222) && (ty2>217)){couleur= T4;}
			else if((ty2<=217) && (ty2>212)){couleur= T3;}
			else if((ty2<=212) && (ty2>207)){couleur= T2;}
			else if((ty2<=207) && (ty2>202)){couleur= T1;}
			else if((ty2<=202) && (ty2>70)){couleur= T0;}
			
			else if(ty2<=5){couleur= T14;}					// La même chose mais pour le haut de l'écran
			else if((ty2<=10) && (ty2>5)){couleur= T13;}	
			else if((ty2<=15) && (ty2>10)){couleur= T12;}
			else if((ty2<=20) && (ty2>15)){couleur= T11;}
			else if((ty2<=25) && (ty2>20)){couleur= T10;}
			else if((ty2<=30) && (ty2>25)){couleur= T9;}
			else if((ty2<=35) && (ty2>30)){couleur= T8;}
			else if((ty2<=40) && (ty2>35)){couleur= T7;}
			else if((ty2<=45) && (ty2>40)){couleur= T6;}
			else if((ty2<=50) && (ty2>45)){couleur= T5;}
			else if((ty2<=55) && (ty2>50)){couleur= T4;}
			else if((ty2<=60) && (ty2>55)){couleur= T3;}
			else if((ty2<=65) && (ty2>60)){couleur= T2;}
			else if((ty2<=70) && (ty2>65)){couleur= T1;}
			else{couleur= T0;}
			
			GuPrintf(text[i].s,10,ty2,couleur,9);	// On affiche la ligne de texte [i]
		}
		GuRefresh();								// On met à jour l'écran
		
		sceKernelDelayThread(1000*70);				// Une petite pause qui temporise le défilement du texte
		ty--;										// On fait défiler le texte
		
		if(ty==-620){break;}						// Si ty arrive à -475, on quitte cette fonction
	}
	
	sceGuTerm();									// On ferme le Gu
}
int GuAnimation(float animation){

	SceCtrlData pad;		// Déclaration de pad (pour l'utilisation des touches)
	int phaseAnimation=0;	// Défini la phase de l'animation
	int decalageTexteX=170;	// Décalage en x du texte à l'écran
	
	/* Pour simplifier le code, je commence par découper l'animation en differentes phases que je pourrais appeler facilement par la suite */
	if((animation>=0) && (animation<300)){phaseAnimation=1;}		// Recule camera Terre (z-)
	if((animation>=300) && (animation<420)){phaseAnimation=2;}		// Recule camera Terre (x-,z-)
	if((animation>=420) && (animation<600)){phaseAnimation=3;}		// Recule camera Terre (x-,z-) changement vitesse
	if((animation>=600) && (animation<601)){phaseAnimation=4;}		// Affichage description Terre, lancement de Voyager2
	if((animation>=601) && (animation<900)){phaseAnimation=5;}		// En route vers Jupiter (z+)
	if((animation>=800) && (animation<1000)){phaseAnimation=6;}		// Passage proche de Mars
	if((animation>=1000) && (animation<2100)){phaseAnimation=7;}	// En route vers Jupiter (z+)
	if((animation>=2100) && (animation<2101)){phaseAnimation=8;}	// Affichage description Jupiter
	if((animation>=2101) && (animation<2600)){phaseAnimation=9;}	// On part de Jupiter en l'évitant (z+)
	if((animation>=2600) && (animation<3700)){phaseAnimation=10;}	// En route vers Saturne (z+)
	if((animation>=3700) && (animation<3701)){phaseAnimation=11;}	// Affichage description Saturne
	if((animation>=3701) && (animation<4100)){phaseAnimation=12;}	// On part de Saturne en l'évitant (z+)
	if((animation>=4100) && (animation<5100)){phaseAnimation=13;}	// En route vers Unranus
	if((animation>=5100) && (animation<5500)){phaseAnimation=14;}	// On ralentit
	if((animation>=5500) && (animation<5501)){phaseAnimation=15;}	// Affichage description d'Uranus
	if((animation>=5501) && (animation<5900)){phaseAnimation=16;}	// En route vers Neptune
	if((animation>=5900) && (animation<6000)){phaseAnimation=17;}	// On ralentit
	if((animation>=6000) && (animation<6001)){phaseAnimation=18;}	// Affichage description de Neptune
	if((animation>=6001) && (animation<6250)){phaseAnimation=19;}	// Direction Pluton
	if((animation>=6250) && (animation<6400)){phaseAnimation=20;}	// Affichage de Pluton trop loin
	if((animation>=6400) && (animation<6600)){phaseAnimation=21;}	// En route vers l'infini^^
	if((animation>=6600) && (animation<6601)){phaseAnimation=22;}	// Affichage description de l'infini
	if((animation>=6601) && (animation<6602)){phaseAnimation=23;}	// On quitte
	
	
	/* Animation de la camera avec gestion de l'affichage des descriptifs */
	if(phaseAnimation==1){
		
		camera.z=camera.z-0.05;	// On avance, décalage en z
	}
	if(phaseAnimation==2){
		
		camera.x=camera.x-0.02;	// l'axe x défini le deplacement "de coté"
		camera.z=camera.z-0.03;
	}
	if(phaseAnimation==3){
		
		camera.x=camera.x-0.05;
	}
	if(phaseAnimation==4){
		
		GuPrintf("NOM: Terre",decalageTexteX+80,5, VERT,8);				// On affiche notre texte à l'écran grace au Gu
		GuPrintf("DIAMETRE: 64 000 km",decalageTexteX+80,20, VERT,8);
		GuPrintf("DISTANCE/SOLEIL: 120 090 km",decalageTexteX+80,35, VERT,8);
		
		GuPrintf("Depart de la Terre",decalageTexteX+90,70, BLEU,8);
		GuPrintf("le 20 aout 1977 pour",decalageTexteX+100,80, BLEU,8);
		GuPrintf("Voyager 2.",decalageTexteX+100,90, BLEU,8);
		
		GuPrintf("Cette date n'est pas",decalageTexteX+100,110, BLEU,8);
		GuPrintf("anodine, il se trouve",decalageTexteX+105,120, BLEU,8);
		GuPrintf("que Voyager2 a profitee",decalageTexteX+110,130, BLEU,8);
		GuPrintf("d'un alignement astral",decalageTexteX+110,140, BLEU,8);		
		GuPrintf("exceptionnel survenant",decalageTexteX+110,150, BLEU,8);
		GuPrintf("une fois tous les 175 ans!",decalageTexteX+100,160, BLEU,8);
		GuPrintf("(Jupiter, Saturne, Uranus",decalageTexteX+98,170, BLEU,8);
		GuPrintf("et Neptune), ceci",decalageTexteX+100,180, BLEU,8);
		GuPrintf("permettant une depense",decalageTexteX+90,190, BLEU,8);
		GuPrintf("minimale de temps et",decalageTexteX+80,200, BLEU,8);
		GuPrintf("de carburant...",decalageTexteX+70,210, BLEU,8);
		
		GuPrintf("Appuyez sur X pour continuer...",decalageTexteX-60,253, ROUGE,8);
		GuRefresh();	// On met à jour l'écran
		
		#ifdef DEBUG4
			sceKernelDelayThread(1000*1000*2);
		#else
			while(1)	// Boucle d'attente d'appui sur X
			{
				sceCtrlReadBufferPositive(&pad, 1);
				if(pad.Buttons & PSP_CTRL_CROSS)
				{sceKernelDelayThread(1000*500);break;}
			}
		#endif
		
	}
	if(phaseAnimation==5){
		
		if(animation==601)
		{SdlPlaySound(2);}	// On joue le bruit de passage proche d'une planète
		
		camera.x=camera.x-0.1;
		camera.z=camera.z+0.5;
	}
	if(phaseAnimation==6){
		
		camera.x=camera.x+0.03;
		camera.z=camera.z+0.3;
		camera.y=camera.y+0.05;	// Déplacement en Y = variation de la hauteur
		
		GuPrintf("<= Mars...",decalageTexteX-65,135, VERT,8);
		GuPrintf("trop loin pour une observation",decalageTexteX-25,150, BLEU,8);
		GuPrintf("au lancement de Voyager2",decalageTexteX-25,160, BLEU,8);
		sceKernelDelayThread(1000*10);
	}
	if(phaseAnimation==7){
		
		GuPrintf("En Route vers Jupiter...",decalageTexteX-100,150, VERT,8);
		GuPrintf("vitesse acceleree...",decalageTexteX-40,165, BLEU,8);
		sceKernelDelayThread(1000*10);
		
		camera.x=camera.x-0.35;
		camera.z=camera.z+1.3;
	}
	if(phaseAnimation==8){
		
		decalageTexteX=5;		
		
		GuPrintf("NOM: Jupiter",decalageTexteX,5, VERT,8);
		GuPrintf("DIAMETRE: 144 000 km",decalageTexteX,20, VERT,8);
		GuPrintf("DISTANCE/SOLEIL: 778 000 000 km",decalageTexteX,35, VERT,8);
		
		GuPrintf("1er objectif pour les 2 sondes, Jupiter!",decalageTexteX,70, BLEU,8);
		GuPrintf("Le 5 mars 1979, Voyager 1 survolait",decalageTexteX,80, BLEU,8);
		GuPrintf("Jupiter. Le 9 juillet 1979 ce fut ",decalageTexteX,90, BLEU,8);
		GuPrintf("au tour de Voyager2.",decalageTexteX,100, BLEU,8);	
		GuPrintf("Les deux sondes permirent notamment",decalageTexteX,110, BLEU,8);
		GuPrintf("la decouverte de nouveaux satellites",decalageTexteX,120, BLEU,8);
		GuPrintf("joviens, d'un anneau autour de",decalageTexteX,130, BLEU,8);
		GuPrintf("Jupiter et d'un volcanisme actif",decalageTexteX,140, BLEU,8);
		GuPrintf("sur le satellite Io.",decalageTexteX,150, BLEU,8);		
		GuPrintf("Les mesures enregistrees par",decalageTexteX,160, BLEU,8);
		GuPrintf("les instruments, notamment sur",decalageTexteX,170, BLEU,8);
		GuPrintf("l'atmosphere tourmentee de la",decalageTexteX,180, BLEU,8);
		GuPrintf("geante gazeuse, ont permis aux",decalageTexteX,190, BLEU,8);
		GuPrintf("scientifiques de mieux comprendre",decalageTexteX,200, BLEU,8);
		GuPrintf("les processus physiques a l'oeuvre sur Jupiter.",decalageTexteX,210, BLEU,8);
		
		GuPrintf("Appuyez sur X pour continuer...",decalageTexteX+100,253, ROUGE,8);
		GuRefresh();
		
		#ifdef DEBUG4
			sceKernelDelayThread(1000*1000*2);
		#else
			while(1)
			{
				sceCtrlReadBufferPositive(&pad, 1);
				if(pad.Buttons & PSP_CTRL_CROSS)
				{sceKernelDelayThread(1000*500);break;}
			}
		#endif
	}
	if(phaseAnimation==9){
		
		if(animation==2200)
		{SdlPlaySound(2);}	// On joue le bruit de passage proche d'une planète
		
		camera.y=camera.y-0.3;
		camera.z=camera.z+1.2;
	}
	if(phaseAnimation==10){
		
		GuPrintf("On prend un peu plus de vitesse...",decalageTexteX-160,130, VERT,8);
		GuPrintf("Direction Saturne...",decalageTexteX-100,145, BLEU,8);
		sceKernelDelayThread(1000*10);
		camera.x=camera.x-0.6;
		camera.y=camera.y+0.25;
		camera.z=camera.z+1.2;
	}
	if(phaseAnimation==11){
	
		decalageTexteX=5;
		
		GuPrintf("NOM: Saturne",decalageTexteX,5, VERT,8);
		GuPrintf("DIAMETRE: 120 000 km",decalageTexteX,20, VERT,8);
		GuPrintf("DISTANCE/SOLEIL: 1 400 000 000 km",decalageTexteX,35, VERT,8);
		
		GuPrintf("Apres Jupiter, les deux sondes se ",decalageTexteX,65, BLEU,8);
		GuPrintf("dirigerent vers Saturne...",decalageTexteX,75, BLEU,8);
		GuPrintf("Le 12 novembre 1980, Voyager 1",decalageTexteX,85, BLEU,8);
		GuPrintf("survolait Saturne. Le 25 aout 1981",decalageTexteX,95, BLEU,8);
		GuPrintf("ce fut au tour de Voyager2. La",decalageTexteX,105, BLEU,8);
		GuPrintf("trajectoire de Voyager 1, concue pour",decalageTexteX,115, BLEU,8);
		GuPrintf("faire passer la sonde a proximite de Titan",decalageTexteX,125, BLEU,8);
		GuPrintf("(le plus gros satellite de Saturne), la fit ensuite sortir",decalageTexteX,135, BLEU,8);
		GuPrintf("du plan ecliptique... en direction de l'espace",decalageTexteX,145, BLEU,8);
		GuPrintf("interstellaire! Le survole de cette sonde au dessus de",decalageTexteX,155, BLEU,8);		
		GuPrintf("Saturne permit de decouvrire une atmosphere tres epaisse",decalageTexteX,165, BLEU,8);
		GuPrintf("et tres dense autour de Titan...",decalageTexteX,175, BLEU,8);	
		
		GuPrintf("Voyager 2, par contre, devait passer par un point ou la",decalageTexteX,190, BLEU,8);
		GuPrintf("gravite de Saturne la devierait automatiquement vers",decalageTexteX,200, BLEU,8);
		GuPrintf("Uranus. De nouveaux satellites de Saturne furent decouverts",decalageTexteX,210, BLEU,8);
		GuPrintf("grace a ces 2 sondes.",decalageTexteX,220, BLEU,8);
		
		GuPrintf("Appuyez sur X pour continuer...",decalageTexteX+120,253, ROUGE,8);
		GuRefresh();
		
		#ifdef DEBUG4
			sceKernelDelayThread(1000*1000*2);
		#else
			while(1)
			{
				sceCtrlReadBufferPositive(&pad, 1);
				if(pad.Buttons & PSP_CTRL_CROSS)
				{sceKernelDelayThread(1000*500);break;}
			}
		#endif
		
	}
	if(phaseAnimation==12){
		
		if(animation==3900)
		{SdlPlaySound(2);}	// On joue le bruit de passage proche d'une planète
		
		camera.x=camera.x-0.3;
		camera.y=camera.y-0.5;
		camera.z=camera.z+1.3;
	}
	if(phaseAnimation==13){
		
		camera.x=camera.x-1.5;
		camera.y=camera.y+0.06;
		camera.z=camera.z+2.2;
	}
	if(phaseAnimation==14){
		
		camera.x=camera.x+0.2;
		camera.z=camera.z+1.4;
	}
	if(phaseAnimation==15){
		
		decalageTexteX=170;
		
		GuPrintf("NOM: Uranus",decalageTexteX,5, VERT,8);
		GuPrintf("DIAMETRE: 52 000 km",decalageTexteX,20, VERT,8);
		GuPrintf("DISTANCE/SOLEIL: 2 900 000 000 km",decalageTexteX,35, VERT,8);
		
		GuPrintf("Il fut decide de proceder au survol",decalageTexteX+20,65, BLEU,8);
		GuPrintf("de cette planete et meme de",decalageTexteX+25,75, BLEU,8);
		GuPrintf("poursuivre ensuite la mission",decalageTexteX+30,85, BLEU,8);
		GuPrintf("vers Neptune. Alors que Saturne",decalageTexteX+35,95, BLEU,8);
		GuPrintf("fut la derniere planete",decalageTexteX+35,105, BLEU,8);
		GuPrintf("survolee par Voyager 1,",decalageTexteX+40,115, BLEU,8);
		GuPrintf("sa soeur jumelle en rencontra,",decalageTexteX+40,125, BLEU,8);
		GuPrintf("donc encore deux autres par la",decalageTexteX+40,135, BLEU,8);
		GuPrintf("suite. Le 24 janvier 1986,",decalageTexteX+40,145, BLEU,8);
		GuPrintf("Voyager 2 passait a 81.500 km du",decalageTexteX+35,155, BLEU,8);
		GuPrintf("sommet des nuages d'Uranus,",decalageTexteX+35,165, BLEU,8);
		GuPrintf("devenant la premiere sonde (et la",decalageTexteX+30,175, BLEU,8);
		GuPrintf("seule a ce jour) a survoler cette",decalageTexteX+25,185, BLEU,8);
		GuPrintf("planete. Voyager2 permit la decouverte",decalageTexteX+6,195, BLEU,8);
		GuPrintf("de plusieurs satellites d'Uranus ainsi",decalageTexteX+2,205, BLEU,8);
		GuPrintf("que d'un champ magnetique autour de",decalageTexteX-5,215, BLEU,8);
		GuPrintf("cette planete.",decalageTexteX-13,225, BLEU,8);
		
		GuPrintf("Appuyez sur X pour continuer...",decalageTexteX-50,253, ROUGE,8);
		GuRefresh();
		
		#ifdef DEBUG4
			sceKernelDelayThread(1000*1000*2);
		#else
			while(1)
			{
				sceCtrlReadBufferPositive(&pad, 1);
				if(pad.Buttons & PSP_CTRL_CROSS)
				{sceKernelDelayThread(1000*500);break;}
			}
		#endif
		
	}
	if(phaseAnimation==16){
		
		if(animation==5501)
		{SdlPlaySound(2);}	// On joue le bruit de passage proche d'une planète
		
		camera.x=camera.x-1.8;
		camera.z=camera.z+4.5;
	}
	if(phaseAnimation==17){
		
		camera.x=camera.x-0.7;
		camera.y=camera.y+0.1;
		camera.z=camera.z+1.7;
	}
	if(phaseAnimation==18){
		
		decalageTexteX=180;		
		
		GuPrintf("NOM: Neptune",decalageTexteX,5, VERT,8);
		GuPrintf("DIAMETRE: 50 000 km",decalageTexteX+12,20, VERT,8);
		GuPrintf("DISTANCE/SOLEIL: 4 500 000 000 km",decalageTexteX+20,35, VERT,8);
		
		GuPrintf("Le dernier survol planetaire ",decalageTexteX+40,65, BLEU,8);
		GuPrintf("effectue par une sonde Voyager",decalageTexteX+45,75, BLEU,8);
		GuPrintf("fut celui de Neptune par",decalageTexteX+45,85, BLEU,8);
		GuPrintf("Voyager2, le 25 aout 1989",decalageTexteX+45,95, BLEU,8);		
		GuPrintf("(12 ans apres son lancement).",decalageTexteX+45,105, BLEU,8);
		GuPrintf("Tout comme pour Uranus, Voyager2",decalageTexteX+45,115, BLEU,8);
		GuPrintf("reste, a l'heure actuelle, la",decalageTexteX+45,125, BLEU,8);
		GuPrintf("seule sonde a avoir survole",decalageTexteX+40,135, BLEU,8);
		GuPrintf("Neptune. En la survolant a une",decalageTexteX+35,145, BLEU,8);
		GuPrintf("distance de 5000 km! Voyager2",decalageTexteX+30,155, BLEU,8);
		GuPrintf("permit la decouverte de plusieurs",decalageTexteX+25,165, BLEU,8);	
		GuPrintf("satellites de Neptune.",decalageTexteX+15,175, BLEU,8);	
		
		GuPrintf("Appuyez sur X pour continuer...",decalageTexteX-50,253, ROUGE,8);
		GuRefresh();
		
		#ifdef DEBUG4
			sceKernelDelayThread(1000*1000*2);
		#else
			while(1)
			{
				sceCtrlReadBufferPositive(&pad, 1);
				if(pad.Buttons & PSP_CTRL_CROSS)
				{sceKernelDelayThread(1000*500);break;}
			}
		#endif
		
	}
	if(phaseAnimation==19){
		
		if(animation==6001)
		{SdlPlaySound(2);}	// On joue le bruit de passage proche d'une planète
		
		camera.x=camera.x-0.2;
		camera.z=camera.z+1.5;
	}
	if(phaseAnimation==20){
		
		decalageTexteX=170;
		
		camera.x=camera.x-0.2;
		camera.z=camera.z+2.0;
		
		GuPrintf("Pluton... =>",decalageTexteX-65,135, VERT,8);
		GuPrintf("trop loin pour une observation",decalageTexteX-25,150, BLEU,8);
		sceKernelDelayThread(1000*10);
	}
	if(phaseAnimation==21){
		
		camera.x=camera.x-0.2;
		camera.z=camera.z+1.5;
	}
	if(phaseAnimation==22){
		
		decalageTexteX=5;		
		
		GuPrintf("Mission interstellaire",decalageTexteX,5, VERT,8);
		GuPrintf("DISTANCE/SOLEIL: infinie",decalageTexteX,20, VERT,8);
		
		GuPrintf("  Apres son survol de Neptune, Voyager 2 fut a son tour,",decalageTexteX,120, BLEU,8);
		GuPrintf(" deviee hors du plan ecliptique. Les deux sondes quittent",decalageTexteX,130, BLEU,8);
		GuPrintf("      a present progressivement le Systeme Solaire.",decalageTexteX,140, BLEU,8);
		GuPrintf(" L'une comme l'autre nous envoient encore des informations",decalageTexteX,150, BLEU,8);
		GuPrintf("  sur l'espace interplanetaire (en etudiant notamment le",decalageTexteX,160, BLEU,8);
		GuPrintf("       champ magnetique et les vents solaires).",decalageTexteX,170, BLEU,8);
		
		GuPrintf("Appuyez sur X pour continuer...",decalageTexteX+100,253, ROUGE,8);
		GuRefresh();
		
		#ifdef DEBUG4
			sceKernelDelayThread(1000*1000*2);
		#else
			while(1)
			{
				sceCtrlReadBufferPositive(&pad, 1);
				if(pad.Buttons & PSP_CTRL_CROSS)
				{sceKernelDelayThread(1000*500);break;}
			}
		#endif
		
	}
	if(phaseAnimation==23){
		
		return 0;	// On a finit l'animation, on retourne 0 pour dire au main de quitter
	}

	return 1;		// On retourne 1, l'animation n'est donc pas fini
}


