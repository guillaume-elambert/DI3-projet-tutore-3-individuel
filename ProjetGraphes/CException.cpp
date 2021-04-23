#include "CException.h"

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
*****Entrée : unsiged int uErreur le code d'erreur et char * sMessage le message d'erreur
*****Nécessite : néant
*****Sortie : néant
*****Entraine : néant
*************************************************/
CException::CException(unsigned int uErreur, const char * sMessage)
{
	uEXCErreur = uErreur;
	sEXCEMessage = _strdup(sMessage);
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
	delete[] sEXCEMessage;
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

const char * CException::EXCGetMessage(void)
{
	return sEXCEMessage;
}

void CException::EXCSetMessage(const char * sMessage)
{
	sEXCEMessage = _strdup(sMessage);
}

