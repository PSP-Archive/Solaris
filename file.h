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


 
 #ifndef FILE__
#define FILE__


int erreur;


/**
 * fsize : renvoi la taille d'un fichier
 * @param : *fn : chemin du fichier
 */
int fsize(char *fn);

/**
 * VerificationFichiers : vérifie l'existance d'un fichier
 * Si le fichier est manquant, la fonction fait quitter le programme de force
 * @param : *CheminFichier : chemin du fichier
 */
void VerificationFichiers(char *CheminFichier);

/**
 * CheckUp : vérifie la présence de tous les fichiers du programme. Si un fichier est manquant, le programme quitte.
 * @param : aucun paramètre.
 */
void CheckUp(void);


#endif
