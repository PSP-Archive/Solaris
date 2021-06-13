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


 
	#include "sdl_functions.h"
	
	
void SdlPlaySound(int son){

	Mix_Music *decompte = NULL;		// Pointeur du son decompte
	Mix_Chunk *depart = NULL;		// Pointeur du son depart
	
	if(son==1)	// Son de decomptage
	{
		#ifdef DEBUG
			decompte = Mix_LoadMUS("/data/sounds/decompte.wav");	// On charge la musique pour psplink2.0
		#else
			decompte = Mix_LoadMUS("data/sounds/decompte.wav");		// On charge la musique
		#endif
		
		Mix_PlayMusic(decompte, 1);			// On lance la lecture 1 foi
	}
	
	if(son==2)	// Son de passage proche d'une planète
	{
		#ifdef DEBUG
			depart =  Mix_LoadWAV("/data/sounds/depart.wav");		// On charge la musique pour psplink2.0
		#else
			depart =  Mix_LoadWAV("data/sounds/depart.wav");		// On charge la musique
		#endif
		
		Mix_PlayChannel( -1, depart, 0 );	// On lance la lecture 1 foi
	}

}
void SdlLoading(void){

	SDL_Surface *ecran = NULL;		// On défini les pointeurs des images
	SDL_Surface *xtreamlua = NULL;
	SDL_Surface *xtra = NULL;
	SDL_Surface *chargement = NULL;
	SDL_Surface *fondu = NULL;
	SDL_Surface *fondu2 = NULL;
	SDL_Surface *decompte = NULL;
	Mix_Music *intro = NULL;
	Mix_Music *voyager = NULL;
	
	
	SDL_Rect P_background;			// On défini la position des images en fonction de x,y
		P_background.x = 0;			// en x
		P_background.y = 0;			// en y
	
	ecran = SDL_SetVideoMode(480, 272, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);	// On défini l'affichage utilisé
	
	VerificationFichiers("/data/images/xtreamlua.png");			// Vérification de l'existence de fichier. Quitte directement si le fichier et manquant.
	VerificationFichiers("/data/images/xtra_production.png");
	VerificationFichiers("/data/images/chargement.png");
	VerificationFichiers("/data/images/fondu.png");
	VerificationFichiers("/data/images/decompte.png");
	
	VerificationFichiers("/data/sounds/intro.wav");
	
	xtreamlua = IMG_Load("data/images/xtreamlua.png");			// On charge nos images
	xtra = IMG_Load("data/images/xtra_production.png");
	chargement = IMG_Load("data/images/chargement.png");
	fondu = IMG_Load("data/images/fondu.png");
	fondu2 = IMG_Load("data/images/fondu2.png");
	decompte = IMG_Load("data/images/decompte.png");
	
	#ifdef DEBUG
		intro = Mix_LoadMUS("/data/sounds/intro.wav");			// On charge nos musiques
	#else
		intro = Mix_LoadMUS("data/sounds/intro.wav");
	#endif
	
	Mix_PlayMusic(intro, 1);									// On joue la musique d'intro 1 foi
	
	#ifdef DEBUG2
		//RIEN
	#else
		Fondu(CHARGE,5,35,ecran,xtreamlua,fondu,&P_background);	// Fondu pour une transition douce entre chaque image
		Fondu(DECHARGE,1,35,ecran,xtreamlua,fondu,&P_background);
		
		Fondu(CHARGE,2,35,ecran,xtra,fondu,&P_background);
		Fondu(DECHARGE,1,35,ecran,xtra,fondu,&P_background);
	#endif

	Fondu(CHARGE,1,35,ecran,chargement,fondu,&P_background);
	
	
	CheckUp();								// Vérification de la présence des fichiers, avec ecran de chargement
	GuLoadModel();							// Configuration des objets (les planètes, étoiles, satelites...)
	GuPositionInit();						// Initialisation des positions des objets
	Fondu(DECHARGE,1,35,ecran,chargement,fondu,&P_background);

	#ifdef DEBUG2
		//RIEN
	#else
		Introduction();						// Présentation de l'HB
		SdlPlaySound(1);					// Bruitage du decompte
		sceKernelDelayThread(1000*1000*9);	// Pause de 10sec
	
	Fondu(DECHARGE,1,35,ecran,decompte,fondu,&P_background);
	Fondu(CHARGE,1,35,ecran,fondu2,fondu,&P_background);
	sceKernelDelayThread(1000*1000*4);						// Pause de 4sec
	Fondu(DECHARGE,1,15,ecran,fondu2,fondu,&P_background);
	sceKernelDelayThread(1000*1000*2);						// Pause de 2sec
	
	#ifdef DEBUG
		voyager = Mix_LoadMUS("/data/sounds/voyager.wav");	// On charge nos musiques
	#else
		voyager = Mix_LoadMUS("data/sounds/voyager.wav");
	#endif
	
	#endif
	Mix_PlayMusic(voyager, -1);
	
	/*  Vidage de la ram : SDL  */
	SDL_FreeSurface(ecran);		// On décharge la ram avant de sortir de la fonction
	SDL_FreeSurface(xtreamlua);
	SDL_FreeSurface(xtra);
	SDL_FreeSurface(chargement);
	SDL_FreeSurface(fondu);
	SDL_FreeSurface(fondu2);
	SDL_FreeSurface(decompte);
	Mix_FreeMusic(intro);
	
}
void SdlQuitting(void){
	
	SDL_Surface *ecran = NULL;	// On défini les pointeurs des images
	SDL_Surface *end = NULL;
	SDL_Surface *solaris = NULL;
	SDL_Surface *fondu = NULL;
	SDL_Surface *fondu2 = NULL;
	Mix_Music *intro = NULL;
	
	SDL_Rect P_background;		// On défini la position des images en fonction de x,y
		P_background.x = 0;		// En x
		P_background.y = 0;		// En y
	
	ecran = SDL_SetVideoMode(480, 272, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);	// On défini l'affichage utilisé
	
	solaris = IMG_Load("data/images/solaris.png");		// On charge nos images
	fondu = IMG_Load("data/images/fondu.png");
	fondu2 = IMG_Load("data/images/fondu2.png");
	end = IMG_Load("data/images/end.png");
	
	#ifdef DEBUG
		intro = Mix_LoadMUS("/data/sounds/intro.wav");	// On charge nos musiques
	#else
		intro = Mix_LoadMUS("data/sounds/intro.wav");
	#endif
	
	Mix_PlayMusic(intro, 1);	// On joue la musique d'intro 1 foi
	
	Fondu(CHARGE,3,35,ecran,fondu2,end,&P_background);	// Fondu pour une transition douce entre chaque image
	Fondu(DECHARGE,1,35,ecran,fondu2,fondu,&P_background);
	
	Exit();		// Texte de fin de l'HB
	
	Fondu(CHARGE,3,35,ecran,solaris,fondu,&P_background);
	Fondu(DECHARGE,1,35,ecran,solaris,fondu,&P_background);
	
	/*  Vidage de la ram : SDL  */
	SDL_FreeSurface(ecran);	// On décharge la ram avant de sortir de la fonction
	SDL_FreeSurface(end);
	SDL_FreeSurface(solaris);
	SDL_FreeSurface(fondu);
	SDL_FreeSurface(fondu2);
	Mix_FreeMusic(intro);
}
void Fondu(int sens, int tempo, int vitesse, SDL_Surface *ecran, SDL_Surface *image, SDL_Surface *fondu, SDL_Rect *P_background){
	
	int transparence;
	
	if(sens==DECHARGE)	// Si on a à l'écran une image vers écran noir
	{
		for(transparence=0; transparence <= 255; transparence = transparence + vitesse)	// On augmente la transparance
		{
			SDL_BlitSurface(image, NULL, ecran, P_background);		// L'image
			SDL_SetAlpha(fondu, SDL_SRCALPHA, transparence);		// le fond noir configuré en "alpha"
			SDL_BlitSurface(fondu, NULL, ecran, P_background);		// affichage du fond noir
			SDL_Flip(ecran);										// On met à jour l'écran
			
			if((255-transparence) < 0){transparence=254-vitesse;}	// Si on ne dépasse pas 255 en transparance on met à jour la transparance
		}
		
		SDL_BlitSurface(fondu, NULL, ecran, P_background);			// Pour finir proprement on affiche le fondu noir
		SDL_Flip(ecran);
		if(tempo!=0){sceKernelDelayThread(1000*1000*tempo);}		// Avec une petite temporisation défini par l'utilisateur
	}
	
	else	// Sinon on veut aller de n'écran noir à l'affichage d'une image
	{
		for(transparence=255; transparence >= 0; transparence = transparence - vitesse)	// On diminu la transparance
		{
			if(transparence <= 0){transparence = 0;}
			SDL_BlitSurface(image, NULL, ecran, P_background);		// L'image
			SDL_SetAlpha(fondu, SDL_SRCALPHA, transparence);		// le fond noir configuré en "alpha"
			SDL_BlitSurface(fondu, NULL, ecran, P_background);		// affichage du fond noir
			SDL_Flip(ecran);										// On met à jour l'écran
			
			if((255+transparence) < 255){transparence=vitesse+1;}	// Si on est toujours pas à 0 on met à jour la transparance
		}	
		
		SDL_BlitSurface(image, NULL, ecran, P_background);			// Pour finir proprement on affiche le fondu noir
		SDL_Flip(ecran);
		if(tempo!=0){sceKernelDelayThread(1000*1000*tempo);}		// Avec une petite temporisation défini par l'utilisateur
	}
	
}




