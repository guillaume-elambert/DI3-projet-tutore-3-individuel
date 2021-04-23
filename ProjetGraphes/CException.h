#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <iostream>
#include <string>

#define Erreur_Par_Defaut 0


class CException
{
	//Attributs
private:
	unsigned int uEXCErreur;
	char * sEXCEMessage;

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
	CException(unsigned int uErreur, const char * sMessage);

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
	*****Sortie : néant
	*****Entraine : néant
	*************************************************/
	void EXCSetErreur(unsigned int uErreur);

	/*************************************************
	*****NOM : EXCGetMessage
	**************************************************
	*****Accesseur en lecture du message d'erreur
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : sEXCEMessage
	*****Entraine : néant
	*************************************************/
	const char * EXCGetMessage(void);

	/*************************************************
	*****NOM : EXCSetMessage
	**************************************************
	*****Accesseur en écriture du message d'erreur
	**************************************************
	*****Entrée : std::string sMessage le nouveau message d'erreur.
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraine : néant
	*************************************************/
	void EXCSetMessage(const char * sMessage);
};
#endif