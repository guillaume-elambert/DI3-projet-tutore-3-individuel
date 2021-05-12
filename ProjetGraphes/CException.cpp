/*!
 * \file CException.cpp
 * \brief Fichier contenant l'implémentation de la classe CException
 * \author Guillaume ELAMBERT
 * \author Clément NONCHER-GILLET
 * \date 2021
 */


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
	sEXCEMessage = sMessage;
}


/*!
 * Destructeur par defaut
 *
 */
CException::~CException()
{
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
	return sEXCEMessage.c_str();
}


/*!
 * Accesseur en écriture du message d'erreur
 *
 * \param sMessage Le nouveau message d'erreur.
 */
void CException::EXCSetMessage(const char * sMessage)
{
	sEXCEMessage = sMessage;
}

