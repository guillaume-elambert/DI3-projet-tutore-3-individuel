/*!
 * \file CArc.h
 * \brief Fichier contenant la déclaration de la classe CArc.
 * \author Guillaume ELAMBERT
 * \author Clément NONCHER-GILLET
 * \date 2021
 */


#ifndef CARC_H
#define CARC_H

/*!
 * \brief Classe des arcs d'un sommet.
 * \author Guillaume ELAMBERT
 * \author Clément NONCHER-GILLET
 * \date 2021
 */
class CArc
{
private:
	
	unsigned int uARCDestination;	/*!< Le numéro du sommet de destination. */

public:

	/*!
	 * Constructeur par défaut
	 * 
	 */
	CArc(void);

	
	/*!
	 * Constructeur de confort
	 * 
	 * \param uARCDestinationParam Le numéro du sommet de destination de l'arc
	 */
	CArc(unsigned int uARCDestinationParam);
	

	/*!
	 * Constructeur de recopie
	 * 
	 * \param ARCParam L'arc à copier
	 */
	CArc(CArc & ARCParam);
	
	/*!
	 * Destructeur par défaut
	 * 
	 */
	~CArc(void);

	
	/*!
	 * Accesseur en lecture de SOMDestination
	 * 
	 * \return uARCDestination la destination de l'arc.
	 */
	unsigned int ARCGetDestination(void);
};
#endif
