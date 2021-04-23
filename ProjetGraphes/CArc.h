#ifndef CARC_H
#define CARC_H

#include <string>

class CArc
{
private:

	unsigned int uARCDestination;

public:

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
	CArc(void);
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
	CArc(unsigned int uARCDestination);
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
	CArc(CArc & ARCParam);
	/*************************************************
	*****NOM : ~CArc
	**************************************************
	*****Destructeur par défaut.
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : L'objet est prêt à être désalloué.
	*************************************************/
	~CArc(void);

	//Accesseur :

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
	unsigned int ARCGetDestination(void);
};
#endif
