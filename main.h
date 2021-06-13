//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	main.c : partie principale du programme
//*********************************************************



#ifndef MAIN__
#define MAIN__


int oldtouch;				// Utilis� pour le thread des touches, permet de savoir si l'utilisateur a appuy� sur une touche
int boucle;					// Stock l'�tat d'execution de l'HB (soit actif, soit en voit de fermeture)
int phaseAnimation=0;		// D�fini la phase de l'animation
char PrintBuffer[100];		// Buffer de stockage de texte pour l'affichage en debug
float animation=0.0;		// Sert de rep�re dans le temps pour l'animation
float coef_animation=1.0;	// Co�ficient permettant de faire varier la vitesse d'animation (pr�vu au debut mais finalement pas utilis�)



/**
 * touches_thread : utile lors du debug, cette fonction permet de g�rer la camera ,de connaitre diverses infos lors de l'execution du programme.
 * @param : automatiquement mit.
 */
int touches_thread(SceSize args, void *argp);

/**
 * Pause : cette fonction qui permet de faire une pause dans le programme.
 * @param : temp : le nombre de seconde de la pause
 */
void Pause(int temp);


#endif
