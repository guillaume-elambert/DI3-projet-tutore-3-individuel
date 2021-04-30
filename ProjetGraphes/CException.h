#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <iostream>
#include <string.h>

#define Erreur_Par_Defaut -1


class CException
{
	//Attributs
private:
	unsigned int uEXCErreur;
	char * sEXCEMessage;

	//Constructeurs
public:

	/*!
	 * Constructeur par défaut
	 * 
	 */
	CException();


	/*!
	 * Constructeur de confort
	 * 
	 * \param uErreur Le code de l'erreur
	 * \param sMessage Le message de l'erreur
	 */
	CException(unsigned int uErreur, const char * sMessage);

	//Destructeurs

	/*!
	 * Destructeur par defaut
	 * 
	 */
	~CException();

	//Accesseurs

	/*!
	 * Accesseur en lecture du code d'erreur
	 * 
	 * \return Le code de l'erreur
	 */
	unsigned int EXCGetErreur(void);

	
	/*!
	 * Accesseur en écriture du code d'erreur
	 * 
	 * \param uErreur Le nouveau code d'erreur.
	 */
	void EXCSetErreur(unsigned int uErreur);

	
	/*!
	 * Accesseur en lecture du message d'erreur
	 * 
	 * \return Le message de l'erreur
	 */
	const char * EXCGetMessage(void);


	/*!
	 * Accesseur en écriture du message d'erreur
	 * 
	 * \param sMessage Le nouveau message d'erreur.
	 */
	void EXCSetMessage(const char * sMessage);
};
#endif