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



#ifndef GU_FUNCTIONS__
#define GU_FUNCTIONS__

	#include "graphics.h"


static unsigned int __attribute__((aligned(16))) list[262144];	// Gu
static int fontwidthtab[128] = {								// Caractères d'écriture utilsés pour écrire avec le Gu
	10, 10, 10, 10, 
	10, 10, 10, 10,
	10, 10, 10, 10, 
	10, 10, 10, 10,

	10, 10, 10, 10, 
	10, 10, 10, 10,
	10, 10, 10, 10,
	10, 10, 10, 10,

	10,  6,  8, 10, //   ! " #
	10, 10, 10,  6, // $ % & '
	10, 10, 10, 10, // ( ) * +
	 6, 10,  6, 10, // , - . /

	10, 10, 10, 10, // 0 1 2 3
	10, 10, 10, 10, // 6 5 8 7
	10, 10,  6,  6, // 10 9 : ;
	10, 10, 10, 10, // < = > ?

	16, 10, 10, 10, // @ A B C
	10, 10, 10, 10, // D E F G
	10,  6,  8, 10, // H I J K
	 8, 10, 10, 10, // L M N O

	10, 10, 10, 10, // P Q R S
	10, 10, 10, 12, // T U V W
	10, 10, 10, 10, // X Y Z [
	10, 10,  8, 10, // \ ] ^ _

	 6,  8,  8,  8, // ` a b c
	 8,  8,  6,  8, // d e f g
	 8,  6,  6,  8, // h i j k
	 6, 10,  8,  8, // l m n o

	 8,  8,  8,  8, // p q r s
	 8,  8,  8, 12, // t u v w
	 8,  8,  8, 10, // x y z {
	 8, 10,  8, 12  // | } ~  
};


typedef struct{			// Structure qui va permettre de stocker les postions, angles des models
	float x;
	float y;
	float z;
	float alpha;
	float beta;
	float gamma;
}position;

typedef struct{			// structure utilisée pour le stockage des phrases de présentation, description et de fin de l'HB
	char s[100];
}string;


/***  Déclaration des Variables de positions (dans le plan xyz) ***/
position ciel;								// Position du ciel
position camera;							// Position de la camera
position soleil;							// Position du model du Soleil
position mercure;							// Position du model de Mercure
position terre;								// Position du model de Terre
position lune;								// Position du model de Lune
position venus;								// Position du model de Venus
position mars;								// Position du model de Mars
position jupiter;							// Position du model de Jupiter
position anneaux_jupiter;					// Position du model du Anneau de Jupiter
position saturne;							// Position du model de Saturne
position anneaux_saturne;					// Position du model du Anneaux de Saturne
position uranus;							// Position du model de Uranus
position neptune;							// Position du model de Neptune

	
/***  Déclaration des Variables  Objets***/
struct obj_model_t obj_ciel;				// Données stockées par le loader d'obj pour le model Ciel
struct obj_model_t obj_soleil;				// Données stockées par le loader d'obj pour le model Soleil
struct obj_model_t obj_mercure;				// Données stockées par le loader d'obj pour le model Mercure
struct obj_model_t obj_venus;				// Données stockées par le loader d'obj pour le model Venus
struct obj_model_t obj_terre;				// Données stockées par le loader d'obj pour le model Terre
struct obj_model_t obj_lune;				// Données stockées par le loader d'obj pour le model Lune
struct obj_model_t obj_mars;				// Données stockées par le loader d'obj pour le model Mars
struct obj_model_t obj_jupiter;				// Données stockées par le loader d'obj pour le model Jupiter
struct obj_model_t obj_anneaux_jupiter; 	// Données stockées par le loader d'obj pour le model Anneau de Jupiter
struct obj_model_t obj_saturne;				// Données stockées par le loader d'obj pour le model Saturne
struct obj_model_t obj_anneaux_saturne; 	// Données stockées par le loader d'obj pour le model Anneau de Saturne
struct obj_model_t obj_uranus;				// Données stockées par le loader d'obj pour le model Uranus
struct obj_model_t obj_neptune;				// Données stockées par le loader d'obj pour le model Neptune


/***  Déclaration des Variables PNG  ***/
Image *texture_ciel;						// Texture png de Ciel
Image *texture_soleil;						// Texture png du Soleil
Image *texture_mercure;						// Texture png de Mercure
Image *texture_venus;						// Texture png de Venus
Image *texture_terre;						// Texture png de la Terre
Image *texture_lune;						// Texture png de Lune
Image *texture_mars;						// Texture png de Mars
Image *texture_jupiter;						// Texture png de Jupiter
Image *texture_anneaux_jupiter;				// Texture png de Anneau de Jupiter
Image *texture_saturne;						// Texture png de Saturne
Image *texture_anneaux_saturne;				// Texture png de Anneau de Saturne
Image *texture_uranus;						// Texture png de Uranus
Image *texture_neptune;						// Texture png de Neptune


/***  Déclaration des Variables  ***/
int couleur;							// couleur du texte (permet de choisir la couleur pour le degradé selon la position du texte)
string text[50];						// Contient les phrases de présentation, description et de fin de l'HB


/**
 * GuInit : cette fonction initialise le Gu.
 * @param : aucun paramètre.
 */
void GuInit(void);

/**
 * GuClearScreen : cette fonction efface l'écran affiché par le Gu.
 * @param : aucun paramètre.
 */
void GuClearScreen(void);

/**
 * GuRefresh : cette fonction rafraichie l'écran du Gu.
 * @param : aucun paramètre.
 */
void GuRefresh(void);

/**
 * GuPositionInit : cette fonction initialise les positions des modèls (obj)
 * @param : aucun paramètre.
 */
void GuPositionInit(void);

/**
 * GuLoadModel : cette fonction charge les modèls (obj)
 * @param : aucun paramètre.
 */
void GuLoadModel(void);

/**
 * GuPrintModel : cette fonction affiche un modèle
 * @param : obj_model : structure de l'obj créé avant avec GuLoadModel
 * @param : *texture : structure de l'image png (texture)
 * @param : model : structure de la position de l'obj
 */
void GuPrintModel(struct obj_model_t obj_model,Image *texture,position model);

/**
 * GuPrintf : cette fonction affiche du texte avec le Gu
 * @param : *text : texte à afficher avec le Gu
 * @param : x : position x du texte
 * @param : y : position y du texte
 * @param : color : couleur du texte
 * @param : fw : taille du texte
 */
void GuPrintf(const char* text, int x, int y, unsigned int color, int fw);

/**
 * ScreenShot : cette fonction prend un screenshot de l'écran (utile pour un fondu à tous moment dans l'HB)
 * @param : aucun paramètre.
 */
void ScreenShot(void);

/**
 * Introduction : cette fonction execute et gère la présentation de l'HB pour ce qui est de la partie Gu.
 * @param : aucun paramètre.
 */
void Introduction(void);

/**
 * Exit : cette fonction execute et gère l'affichage de fin de l'HB pour ce qui est de la partie Gu.
 * @param : aucun paramètre.
 */
void Exit(void);

/**
 * GuAnimation : cette fonction avance l'animation et  affiche la description des planètes lors de l'execution de l'animation Gu.
 * @param : phase : référe la phase de n'animation. 
 * @return : 0=fin de programme
 */
int GuAnimation(float animation);


#endif
