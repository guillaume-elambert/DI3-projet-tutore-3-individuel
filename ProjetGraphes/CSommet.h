#ifndef CSOMMET_H
#define CSOMMET_H

#include <iostream>
#include <string>
#include "CException.h"
#include "CArc.h"

#define Lecture_Impossible 20


class CSommet
{
private:
	unsigned int uSOMId;
	CArc * pARCSOMListeArcsArrivants;
	unsigned int uSOMTailleListeA;
	CArc * pARCSOMListeArcsSortants;
	unsigned int uSOMTailleListeS;

public:
	/*************************************************
	*****NOM : CSommet
	**************************************************
	*****Constructeur par défaut
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Créaction d'un CSommet d'uSOMId = 0.
	*************************************************/
	CSommet(void);
	/*************************************************
	*****NOM : CSommet
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entrée : unsigned int uNid l'Id du Sommet.
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Créaction d'un CSommet d'uSOMId = uNid.
	*************************************************/
	CSommet(unsigned int uNid);
	/*************************************************
	*****NOM : CSommet
	**************************************************
	*****Constructeur de recopie
	**************************************************
	*****Entrée : CSommet & SOMParam
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Création d'un CSommet copie de SOMParam.
	*************************************************/
	CSommet(CSommet & SOMParam);

	/*************************************************
	*****NOM : ~CSommet
	**************************************************
	*****Destructeur par défaut
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : L'objet est prêt à être désalloué.
	*************************************************/
	~CSommet(void);

	/*************************************************
	*****NOM : SOMGetId
	**************************************************
	*****Accesseur en lecture de uSOMId.
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : uSOMId
	*****Entraîne : /
	*************************************************/
	unsigned int SOMGetId();

	/*************************************************
	*****NOM : SOMLireTailleE
	**************************************************
	*****Accesseur en lecture de uSOMTailleListeArrivants.
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : uSOMTailleListeArrivants
	*****Entraîne : /
	*************************************************/
	unsigned int SOMGetTailleA();

	/*************************************************
	*****NOM : SOMLireTailleE
	**************************************************
	*****Accesseur en lecture de uSOMTailleListeA.
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : uSOMTailleListeS
	*****Entraîne : /
	*************************************************/
	unsigned int SOMGetTailleS();

	/*************************************************
	*****NOM : SOMAjouterArcArrivant
	**************************************************
	*****Ajoute un arc arrivant.
	**************************************************
	*****Entrée : CArc ARCParam
	*****Nécessite : ARCParam n'est pas déjà dans la liste des arcs arrivants.
	*****Sortie : néant
	*****Entraîne : La liste des arcs contient maintenant ARCParam.
	*************************************************/
	void SOMAjouterArcArrivant(CArc & ARCParam);


	/*************************************************
	*****NOM : SOMRetirerArcArrivant
	**************************************************
	*****Retire un arc arrivant.
	**************************************************
	*****Entrée : CArc ARCParam
	*****Nécessite : ARCParam est dans la liste des arcs arrivants.
	*****Sortie : néant
	*****Entraîne : La liste des arcs ne contient maintenant plus ARCParam.
	*************************************************/
	void SOMRetirerArcArrivant(CArc & ARCParam);


	/*************************************************
	*****NOM : SOMChercherArcArrivant
	**************************************************
	*****Recherche un arc d'id particulier.
	**************************************************
	*****Entrée : unsigned int uSOMIdDestination
	*****Nécessite : néant
	*****Sortie : la position de l'arc cherché dans la liste si il y est, -1 sinon.
	*****Entraîne : /
	*************************************************/
	int SOMChercherArcArrivant(unsigned int uSOMIdDestination);


	/*************************************************
	*****NOM : SOMLireListeA
	**************************************************
	*****Lis l'arc en position uPos de la liste.
	**************************************************
	*****Entrée : unsigned int uPos
	*****Nécessite : uPos < uSOMTailleListeA - 1
	*****Sortie : néant
	*****Entraîne : /
	*************************************************/
	CArc SOMLireListeA(unsigned int uPos);


	/*************************************************
	*****NOM : SOMAjouterArcSortant
	**************************************************
	*****Ajoute un arc sortant.
	**************************************************
	*****Entrée : CArc ARCParam
	*****Nécessite : ARCParam n'est pas déjà dans la liste des arcs sortants.
	*****Sortie : néant
	*****Entraîne : La liste des arcs contient maintenant ARCParam.
	*************************************************/
	void SOMAjouterArcSortant(CArc & ARCParam);


	/*************************************************
	*****NOM : SOMRetirerArcSortant
	**************************************************
	*****Retire un arc sortant.
	**************************************************
	*****Entrée : CArc ARCParam
	*****Nécessite : ARCParam est dans la liste des arcs sortants.
	*****Sortie : néant
	*****Entraîne : La liste des arcs ne contient maintenant plus ARCParam.
	*************************************************/
	void SOMRetirerArcSortant(CArc & ARCParam);


	/*************************************************
	*****NOM : SOMChercherArcSortant
	**************************************************
	*****Recherche un arc d'id particulier.
	**************************************************
	*****Entrée : unsigned int uSOMIdDestination
	*****Nécessite : néant
	*****Sortie : la position de l'arc cherché dans la liste si il y est, -1 sinon.
	*****Entraîne : /
	*************************************************/
	int SOMChercherArcSortant(unsigned int uSOMIdDestination);


	/*************************************************
	*****NOM : SOMLireListeS
	**************************************************
	*****Lis l'arc en position uPos de la liste.
	**************************************************
	*****Entrée : unsigned int uPos
	*****Nécessite : uPos < uSOMTailleListeS
	*****Sortie : néant
	*****Entraîne : /
	*************************************************/
	CArc SOMLireListeS(unsigned int uPos);


	/*************************************************
	*****NOM : operator=
	**************************************************
	*****Surcharge de l'opérateur =
	**************************************************
	*****Entrée : const CSommet & SOMParam
	*****Nécessite : néant
	*****Sortie : CSommet &
	*****Entraîne : L'objet deviens une copie de SOMParam
	*************************************************/
	CSommet & operator=(const CSommet & SOMParam);


	/*************************************************
	*****NOM : SOMLies
	**************************************************
	*****Teste si deux sommets sont liés dans le sens *this -> SOMParam
	**************************************************
	*****Entrée : CSommet & SOMParam
	*****Nécessite : néant
	*****Sortie : bool bTeste
	*****Entraîne : Si il existe un arc allant de cet objet vers SOMParam, bTeste = true. bTeste = false sinon.
	*************************************************/
	bool SOMLies(CSommet & SOMParam);


	/*************************************************
	*****NOM : SOMInverser
	**************************************************
	*****Inverse les arcs entrants et sortants.
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : /
	*************************************************/
	void SOMInverser();


	/*************************************************
	*****NOM : SOMAfficherSommet
	**************************************************
	*****Affiche le graphe sur la sortie standard.
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : /
	*************************************************/
	void SOMAfficherSommet();
};

#endif