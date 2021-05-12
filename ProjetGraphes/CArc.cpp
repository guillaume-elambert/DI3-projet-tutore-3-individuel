/*!
 * \file CArc.cpp
 * \brief Fichier contenant l'implémentation de la classe CArc
 * \author Guillaume ELAMBERT
 * \author Clément NONCHER-GILLET
 * \date 2021
 */


#include "CArc.h"

/*!
 * Constructeur par défaut
 *
 */
CArc::CArc(void)
{
	uARCDestination = 0;
}


/*!
 * Constructeur de confort
 * 
 * \param uARCDestinationParam Le numéro du sommet de destination de l'arc
 */
CArc::CArc(unsigned int uARCDestinationParam)
{
	uARCDestination = uARCDestinationParam;
}

/*!
 * Constructeur de recopie
 *
 * \param ARCParam L'arc à copier
 */
CArc::CArc(CArc & ARCParam)
{
	uARCDestination = ARCParam.uARCDestination;
}


/*!
 * Destructeur par défaut
 *
 */
CArc::~CArc(void)
{
	//Ne fait rien
}


/*!
 * Accesseur en lecture de SOMDestination
 *
 * \return uARCDestination la destination de l'arc.
 */
unsigned int CArc::ARCGetDestination(void)
{
	return uARCDestination;
}
