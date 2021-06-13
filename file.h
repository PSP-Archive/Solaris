//********************************************************
//	Solaris by PEB
//	http://pebdev.eu
//*********************************************************
//	pub@29/01/08
//	rev@01/11/10
//*********************************************************
//	file.c : contient les fonctions majeurs qui op�rent 
//	sur les fichiers
//*********************************************************


 
 #ifndef FILE__
#define FILE__


int erreur;


/**
 * fsize : renvoi la taille d'un fichier
 * @param : *fn : chemin du fichier
 */
int fsize(char *fn);

/**
 * VerificationFichiers : v�rifie l'existance d'un fichier
 * Si le fichier est manquant, la fonction fait quitter le programme de force
 * @param : *CheminFichier : chemin du fichier
 */
void VerificationFichiers(char *CheminFichier);

/**
 * CheckUp : v�rifie la pr�sence de tous les fichiers du programme. Si un fichier est manquant, le programme quitte.
 * @param : aucun param�tre.
 */
void CheckUp(void);


#endif
