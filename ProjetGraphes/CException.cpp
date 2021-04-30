#include "CException.h"

/*!
 * Constructeur par défaut
 *
 */
CException::CException()
{
	uEXCErreur = Erreur_Par_Defaut;
}


/*!
 * Constructeur de confort
 *
 * \param uErreur Le code de l'erreur
 * \param sMessage Le message de l'erreur
 */
CException::CException(unsigned int uErreur, const char * sMessage)
{
	uEXCErreur = uErreur;
	sEXCEMessage = _strdup(sMessage);
}


/*!
 * Destructeur par defaut
 *
 */
CException::~CException()
{
	if(sEXCEMessage) free(sEXCEMessage);
}


/*!
 * Accesseur en lecture du code d'erreur
 *
 * \return Le code de l'erreur
 */
unsigned int CException::EXCGetErreur(void)
{
	return uEXCErreur;
}


/*!
 * Accesseur en écriture du code d'erreur
 *
 * \param uErreur Le nouveau code d'erreur.
 */
void CException::EXCSetErreur(unsigned int uErreur)
{
	uEXCErreur = uErreur;
}


/*!
 * Accesseur en lecture du message d'erreur
 *
 * \return Le message de l'erreur
 */
const char * CException::EXCGetMessage(void)
{
	return sEXCEMessage;
}


/*!
 * Accesseur en écriture du message d'erreur
 *
 * \param sMessage Le nouveau message d'erreur.
 */
void CException::EXCSetMessage(const char * sMessage)
{
	sEXCEMessage = _strdup(sMessage);
}

