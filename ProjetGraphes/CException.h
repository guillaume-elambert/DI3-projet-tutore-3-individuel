#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <iostream>

#define Erreur_Par_Defaut 0

using namespace std;

class CException
{
	//Attributs
private:
	unsigned int uEXCErreur;

	//Constructeurs
public:

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
	CException();

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
	CException(unsigned int uErreur);

	//Destructeurs

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
	~CException();

	//Accesseurs

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
	unsigned int EXCGetErreur(void);

	/*************************************************
	*****NOM : EXCSetErreur
	**************************************************
	*****Accesseur en écriture du code d'erreur
	**************************************************
	*****Entrée : unsigned int uErreur le nouveau code d'erreur.
	*****Nécessite : néant
	*****Sortie : IdErreur
	*****Entraine : néant
	*************************************************/
	void EXCSetErreur(unsigned int uErreur);

	/*************************************************
	*****NOM : EXCAfficherMessageErreur
	**************************************************
	*****Affiche dans la sortie standard un message d'erreur approprié.
	**************************************************
	*****Entrée : idErreur
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraine : néant
	*************************************************/
	void EXCAfficherMessageErreur(void);
};
#endif