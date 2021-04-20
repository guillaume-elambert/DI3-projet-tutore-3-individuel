#ifndef CEXCEPTION_H
#include "CException.h"
#endif
/*************************************************
*****NOM : CException
**************************************************
*****Constructeur par défaut
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : néant
*****Entraine : néant
*************************************************/
CException::CException()
{
	uEXCErreur = Erreur_Par_Defaut;
}

/*************************************************
*****NOM : CException
**************************************************
*****Constructeur de confort
**************************************************
*****Entrée : unsiged int uErreur le code d'erreur.
*****Nécessite : néant
*****Sortie : néant
*****Entraine : néant
*************************************************/
CException::CException(unsigned int uErreur)
{
	uEXCErreur = uErreur;
}

/*************************************************
*****NOM : ~CException
**************************************************
*****Destructeur par défaut
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : néant
*****Entraine : néant
*************************************************/
CException::~CException()
{

}

/*************************************************
*****NOM : EXCGetErreur
**************************************************
*****Accesseur en lecture du code d'erreur
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : uErreur
*****Entraine : néant
*************************************************/
unsigned int CException::EXCGetErreur(void)
{
	return uEXCErreur;
}

/*************************************************
*****NOM : EXCSetErreur
**************************************************
*****Accesseur en écriture du code d'erreur
**************************************************
*****Entrée : unsigned int uErreur le nouveau code d'erreur.
*****Nécessite : néant
*****Sortie : néant
*****Entraine : néant
*************************************************/
void CException::EXCSetErreur(unsigned int uErreur)
{
	uEXCErreur = uErreur;
}

/*************************************************
*****NOM : EXCAfficherMessageErreur
**************************************************
*****Affiche dans la sortie standard un message d'erreur approprié.
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : néant
*****Entraine : néant
*************************************************/
void CException::EXCAfficherMessageErreur(void)
{
	cerr << "Exception : ";
	switch (uEXCErreur) {
		/*Erreur par defaut*/
	case Erreur_Par_Defaut:
		cerr << "Exception par defaut";
		break;

		/*Main*/
	case 1:
		cerr << "Le nombre de paramètres que vous avez passé est illogique" << endl;
		break;

		/*CSommet*/
	case 2:
		cerr << "L'index de votre sommet n'est pas correct" << endl;
		break;

		/*CGraphe*/
	case 3:
		cerr << "L'arc spécifié existe déjà" << endl;
		break;
	case 4:
		cerr << "L'arc spécifié n'est pas valable" << endl;
		break;
	case 5:
		cerr << "Le sommet spécifié existe déjà" << endl;
		break;
	case 6:
		cerr << "Le sommet spécifié n'est pas valable" << endl;
		break;
	case 7:
		cerr << "La grammaire du fichier n'est pas bonne" << endl;
		break;
	case 8:
		cerr << "Erreur par défaut : CGraphe :" << endl;
		break;

		/*CParser*/
	case 9:
		cerr << "Le parser n'est pas initialisé" << endl;
		break;
	case 10:
		cerr << "Impossible d'ouvrir le fichier" << endl;
		break;

		cerr << endl;
	}
}

