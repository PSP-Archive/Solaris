//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	define.h : Contient toutes les defines du porgramme
//*********************************************************



#ifndef DEFINES__
#define DEFINES__

/***  Define de param�trage de l'�cran  ***/
#define BUF_WIDTH	512
#define SCR_WIDTH	480
#define SCR_HEIGHT	272


/*** DEFINE DE DEVELOPPEMENT (DEBUG)  ***/
//#define DEBUG		// Debug qui, si d�fini, permet d'utiliser psplink2.0 pour le d�veloppement				(penser � recompiler l'ensemble des fichiers)
//#define DEBUG2		// Debug qui, si d�fini, zap l'intro 										(penser � recompiler sdl_functions.c)
//#define DEBUG3		// Debug qui, si d�fini, zap la fin										(penser � recompiler sdl_functions.c)
//#define DEBUG4		// Debug qui, si d�fini, remplacer le "appuyer sur une touche" par une temporisation de 2sec 	(penser � recompiler gu_functions.c)
//#define DEBUG5		// Debug qui, si d�fini, rajoute la possibilit� de changer les coordon�es de la camera			(penser � recompiler main.c) DEBUG6 DOIT ETRE DEFINI!!!
//#define DEBUG6		// Debug qui, si d�fini, rajoute la possibilit� de cr�er thread touch					(penser � recompiler main.c)


/*** Define de logique  ***/
#define YES			1
#define NO			0
#define ACTIVE		1
#define DESACTIVE	0
#define CHARGE 		69
#define DECHARGE 	96


/*** Define d'affichage en debug  ***/
#define printf2		pspDebugScreenPrintf
#define printfxy	pspDebugScreenSetXY
#define printfcolor pspDebugScreenSetTextColor
#define printfbg 	pspDebugScreenSetBackColor


/*** Define de couleur  ***/
#define BLANC 	0xffffffff				// Couleur du texte
#define BLEU 	0xffff0000				// Couleur du texte
#define ROUGE 	0xff0000ff				// Couleur du texte
#define VERT 	0xff00ff00				// Couleur du texte
#define T0 		0xffffffff				// Couleur de degrad� du texte
#define T1 		0xdfffffff				// Couleur de degrad� du texte
#define T2 		0xbfffffff				// Couleur de degrad� du texte
#define T3 		0x9fffffff				// Couleur de degrad� du texte
#define T4 		0x7fffffff				// Couleur de degrad� du texte
#define T5 		0x5fffffff				// Couleur de degrad� du texte
#define T6 		0x3fffffff				// Couleur de degrad� du texte
#define T7 		0x0fffffff				// Couleur de degrad� du texte
#define T8 		0x0dffffff				// Couleur de degrad� du texte
#define T9 		0x0bffffff				// Couleur de degrad� du texte
#define T10 	0x09ffffff				// Couleur de degrad� du texte
#define T11 	0x07ffffff				// Couleur de degrad� du texte
#define T12 	0x05ffffff				// Couleur de degrad� du texte
#define T13 	0x03ffffff				// Couleur de degrad� du texte
#define T14 	0x00ffffff				// Couleur de degrad� du texte


/***  Define des infos sur la lumi�re Gu  ***/
#define LIGHT_DISTANCE 	-130.0f
#define LIGHT_COLOR		0xffffffff


/*** Distance des plan�tes (et etoile)  par rapport au soleil ***/
#define D_PROV				10						// Coeficient qui dimentionne l'espace xyz (proportion gard�e)
#define DISTANCE_MERCURE	-(20.0*D_PROV+1000)
#define DISTANCE_VENUS		-(36.0*D_PROV+1000)
#define DISTANCE_TERRE		-(51.0*D_PROV+1000)
#define DISTANCE_MARS		-(77.0*D_PROV+1000)
#define DISTANCE_JUPITER	-(263.0*D_PROV+1000)
#define DISTANCE_SATURNE	-(474.0*D_PROV+1000)
#define DISTANCE_URANUS		-(783.0*D_PROV+1000)	// en vrai 983.0
#define DISTANCE_NEPTUNE	-(995.0*D_PROV+1000)	// en vrai 1525.0
#define DISTANCE_PLUTON		-(1010.0*D_PROV+1000)	// en vrai 2000.0
#define DISTANCE_TERRE_LUNE		DISTANCE_TERRE-20
#define	DISTANCE_SATURNE_TITAN	DISTANCE_SATURNE-50


#endif


