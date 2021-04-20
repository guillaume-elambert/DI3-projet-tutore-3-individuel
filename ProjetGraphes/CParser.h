#ifndef CPARSER_H
#define CPARSER_H

#include <fstream>

#include "CString.h"


#define Ouverture_Fichier_Impossible 50
#define Fichier_Non_Ouvert 51

class CParser
{
private:
	CString STRPARChemin;

	CString STRPARNomAttribut;
	CString TYAPARTypeAttribut;
	int iPARValeurAttribut;

	char cPARCaractereActuel;
	CString STRPARContenuAttribut;
	ifstream FILPARFichier;

	/*************************************************
	*****NOM : PARConvertirLigne
	**************************************************
	*****Permet au parser de lire convertir l'attribut
	trouvé en type voir en valeur pour les cas spécifiques
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Mise à jour des attributs nom, type et valeur
	*************************************************/
	void PARConvertirLigne();

	/*************************************************
	*****NOM : PARIsSeparator
	**************************************************
	*****Permet au parser de savoir si un caractere
	spécifique délimite une séparation
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : boolean
	*****Entraîne : /
	*************************************************/
	static bool PARIsSeparator(const char cCaractere);

public:

	/*************************************************
	*****NOM : CParser
	**************************************************
	*****Constructeur par défaut
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Création d'un parser vide
	*************************************************/
	CParser();

	/*************************************************
	*****NOM : CParser
	**************************************************
	*****Constructeur de confort (CString)
	**************************************************
	*****Entrée : Une chaine de charactère du chemin du fichier à convertir
	*****Nécessite : Un chemin valide
	*****Sortie : néant
	*****Entraîne : Création d'un parser initialisé avec le chemin,
	si non valide, déclenche une exception indiquant la non validité du chemin
	*************************************************/
	CParser(const CString STRChemin);

	/*************************************************
	*****NOM : ~CParser
	**************************************************
	*****Destructeur
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Destruction d'un parser
	*************************************************/
	~CParser();

	/*************************************************
	*****NOM : PARLireType
	**************************************************
	*****Acesseur en lecture de PARTYAType
	**************************************************
	*****Entrée : néant
	*****Nécessite : Un parser initialisé
	*****Sortie : le type de la valeur
	*****Entraîne : /
	*************************************************/
	CString PARLireType();

	/*************************************************
	*****NOM : PARLireNom
	**************************************************
	*****Acesseur en lecture de PARNomAttribut
	**************************************************
	*****Entrée : néant
	*****Nécessite : être utilisé après PARLireType si il renvoi entier
	*****Sortie : un CString représentant la valeur
	*****Entraîne : /
	*************************************************/
	CString PARLireNom();

	/*************************************************
	*****NOM : PARLireValeur
	**************************************************
	*****Acesseur en lecture de PARValeur
	**************************************************
	*****Entrée : néant
	*****Nécessite : être utilisé après PARLireType si il renvoi entier
	*****Sortie : iParValeurAttribut
	*****Entraîne : Retour de la valeur
	*************************************************/
	int PARLireValeur();

	/*************************************************
	*****NOM : PARInitialiser
	**************************************************
	*****Initialisation et mise au début de la lecture
	**************************************************
	*****Entrée : néant
	*****Nécessite : Le parser a déjà un chemin valide
	*****Sortie : néant
	*****Entraîne : Initialisation du parser,
	si chemin invalide, entraine une exception indiquant la non validité du chemin,
	si déjà initialisé, le réinitialise.
	*************************************************/
	void PARInitialiser(const CString STRChemin);

	/*************************************************
	*****NOM : PARFinaliser
	**************************************************
	*****Finalisation de la lecture
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : true si la finalisation s'est faite,
	false si l'initialisation ne s'était pas faite
	*****Entraîne : Finalisation du parser, ferme le ifstream
	*************************************************/
	bool PARFinaliser();

	/*************************************************
	*****NOM : PARSuivant
	**************************************************
	*****Passe à l'objet syntaxique suivant
	**************************************************
	*****Entrée : néant
	*****Nécessite : Le parser est initialisé
	*****Sortie : néant
	*****Entraîne : Passage à l'entité synthaxique suivante
					Si à la fin, reste à la fin et renvoi false
	*************************************************/
	bool PARSuivant();
};
#endif