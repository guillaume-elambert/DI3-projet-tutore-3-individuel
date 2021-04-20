#include "CArc.h"

/*************************************************
*****NOM : CArc
**************************************************
*****Constructeur par défaut
**************************************************
*****Entrée : néant
*****Nécessite : Ne pas utiliser.
*****Sortie : néant
*****Entraîne : Lève une exception.
*************************************************/
CArc::CArc(void)
{
	uARCDestination = 0;
}

/*************************************************
*****NOM : CArc
**************************************************
*****Constructeur de confort.
**************************************************
*****Entrée : unsigned int uARCDestination
*****Nécessite : néant
*****Sortie : néant
*****Entraîne : Création d'un arc ayant pour destination unsigned int uARCDestination.
*************************************************/
CArc::CArc(unsigned int uARCDestinationParam)
{
	uARCDestination = uARCDestinationParam;
}

/*************************************************
*****NOM : CArc
**************************************************
*****Constructeur de recopie.
**************************************************
*****Entrée : CArc & ARCParam
*****Nécessite : néant
*****Sortie : néant
*****Entraîne : Création d'un arc copie de ARCParam.
*************************************************/
CArc::CArc(CArc & ARCParam)
{
	uARCDestination = ARCParam.uARCDestination;
}

/*************************************************
*****NOM : ~CArc
**************************************************
*****Destructeur par défaut.
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : néant
*****Entraîne : L'obket est prêt à être détruite.
*************************************************/
CArc::~CArc(void)
{
	//Ne fait rien
}

/*************************************************
*****NOM : ARCGetDestination
**************************************************
*****Accesseur en lecture de SOMDestination
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : uARCDestination la destination de l'arc.
*****Entraîne : /
*************************************************/
unsigned int CArc::ARCGetDestination(void)
{
	return uARCDestination;
}
