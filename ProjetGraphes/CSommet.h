#ifndef CSOMMET_H
#define CSOMMET_H

#include <iostream>
#include <string.h>
#include "CException.h"
#include "CArc.h"

#define CSOMMET_Lecture_Impossible	20
#define CSOMMET_Alloc_Echouee		21


class CSommet
{
private:
	unsigned int uSOMId;
	CArc ** pARCSOMListeArcsArrivants;
	unsigned int uSOMTailleListeA;
	CArc ** pARCSOMListeArcsSortants;
	unsigned int uSOMTailleListeS;

public:
	
	/*!
	 * Constructeur par défaut
	 * 
	 */
	CSommet(void);
	

	/*!
	 * Constructeur de confort
	 * 
	 * \param uNid Le numéro du sommet
	 */
	CSommet(unsigned int uNid);

	
	/*!
	 * Constructeur de recopie. 
	 * Créé un objet CSommet copie de SOMParam.
	 * 
	 * \param SOMParam L'objet CSommet à copier
	 */
	CSommet(CSommet & SOMParam);

	
	/*!
	 * Destructeur par défaut
	 * 
	 */
	~CSommet(void);

	

	/*!
	 * Accesseur en lecture de uSOMId.
	 * 
	 * \return Le numéro du sommet
	 */
	unsigned int SOMGetId();


	/*!
	 * Accesseur en lecture de uSOMTailleListeArrivants.
	 * 
	 * \return Le nombre d'arcs arrivants au sommet
	 */
	unsigned int SOMGetTailleA();


	/*!
	 * Accesseur en lecture de uSOMTailleListeS.
	 * 
	 * \return Le nombre d'arcs partants du sommet
	 */
	unsigned int SOMGetTailleS();


	/*!
	 * Ajoute un arc arrivant au sommet.
	 * 
	 * \param uDestination La destination de l'objet CArc à ajouter à la liste des arcs arrivants
	 * \pre Il n'existe pas d'objet CArc dans la liste des arcs arrivants ayant pour destination uDestination.
	 */
	void SOMAjouterArcArrivant(unsigned int uDestination);


	/*!
	 * Retire un arc arrivant au sommet.
	 * 
	 * \param uDestination La destination de l'objet CArc à supprimer de la liste des arcs arrivants
	 * \pre Il existe un objet CArc dans la liste des arcs arrivants ayant pour destination uDestination.
	 */
	void SOMRetirerArcArrivant(unsigned int uDestination);



	/*!
	 * Recherche l'arc arrivant ayant pour point de départ le sommet numéro uSOMIdDestination.
	 * 
	 * \param uSOMIdDestination Le numéro du sommet de départ de l'arc
	 * \return La position de l'arc cherché dans la liste des arcs arrivants si il y est, -1 sinon.
	 */
	int SOMChercherArcArrivant(unsigned int uSOMIdDestination);


	
	/*!
	 * Lis l'arc arrivant en position uPos de la liste pARCSOMListeArcsArrivants.
	 * 
	 * \param uPos La position de l'arc dans la liste pARCSOMListeArcsArrivants
	 * \pre  0 <= uPos <= uSOMTailleListeA - 1
	 * \return Objet CArc à la position uPos dans la liste des arcs entrants
	 */
	CArc* SOMLireListeA(unsigned int uPos);



	/*!
	 * Ajoute un arc sortant au sommet.
	 *
	 * \param uDestination La destination de l'objet CArc à ajouter à la liste des arcs sortants
	 * \pre Il n'existe pas d'objet CArc dans la liste des arcs sortants ayant pour destination uDestination.
	 */
	void SOMAjouterArcSortant(unsigned int uDestination);


	/*!
	 * Retire un arc sortant au sommet.
	 *
	 * \param uDestination La destination de l'objet CArc à supprimer de la liste des arcs sortants
	 * \pre Il existe un objet CArc dans la liste des arcs sortants ayant pour destination uDestination.
	 */
	void SOMRetirerArcSortant(unsigned int uDestination);


	/*!
	 * Recherche l'arc partant ayant pour point d'arrivé le sommet numéro uSOMIdDestination.
	 * 
	 * \param uSOMIdDestination Le numéro du sommet d'arrivé de l'arc
	 * \return La position de l'arc cherché dans la liste des arcs sortants si il y est, -1 sinon.
	 */
	int SOMChercherArcSortant(unsigned int uSOMIdDestination);


	/*!
	 * Lis l'arc en position uPos de la liste pARCSOMListeArcsSortants.
	 * 
	 * \param uPos La position de l'arc dans la liste pARCSOMListeArcsSortants
	 * \pre  0 <= uPos <= uSOMTailleListeS - 1
	 * \return Objet CArc à la position uPos dans la liste des arcs sortants
	 */
	CArc* SOMLireListeS(unsigned int uPos);


	/*!
	 * Teste si deux sommets sont liés dans le sens *this -> SOMParam
	 * 
	 * \param SOMParam true s'il existe un arc allant de cet objet vers SOMParam, false sinon.
	 * \return 
	 */
	bool SOMLies(CSommet & SOMParam);


	/*!
	 * Inverse les arcs entrants et sortants. 
	 * Les CArcs arrivants deviennent les CArcs sortants et vice-versa
	 * 
	 */
	void SOMInverser();


	/*!
	 * Affiche le graphe sur la sortie standard.
	 * 
	 */
	void SOMAfficherSommet();


	/*!
	 * Surcharge de l'operateur =
	 * Copie le contenu de SOMParam dans l'objet appelant
	 * 
	 * \param SOMParam L'objet CSommet à copier
	 * \return Un pointeur sur l'objet appelant, copie de SOMParam
	 */
	CSommet & operator=(const CSommet & SOMParam);
};

#endif