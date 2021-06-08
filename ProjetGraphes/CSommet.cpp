/*!
 * \file CSommet.cpp
 * \brief Fichier contenant l'implémentation de la classe CSommet
 * \author Guillaume ELAMBERT
 * \author Clément NONCHER-GILLET
 * \date 2021
 */


#include "CSommet.h"


/*!
 * Constructeur par défaut
 *
 */
CSommet::CSommet(void)
{
	pARCSOMListeArcsArrivants = NULL;
	pARCSOMListeArcsSortants = NULL;
	uSOMId = 0;
	uSOMTailleListeA = 0;
	uSOMTailleListeS = 0;
}


/*!
 * Constructeur de confort
 *
 * \param uNid Le numéro du sommet
 */
CSommet::CSommet(unsigned int uNid) {

	pARCSOMListeArcsArrivants = NULL;
	pARCSOMListeArcsSortants = NULL;
	uSOMId = uNid;
	uSOMTailleListeA = 0;
	uSOMTailleListeS = 0;
}


/*!
 * Constructeur de recopie.
 * Créé un objet CSommet copie de SOMParam.
 *
 * \param SOMParam L'objet CSommet à copier
 */
CSommet::CSommet(CSommet & SOMParam)
{
	//On fait appel à la surcharge de l'opérateur =
	*this = SOMParam;
}


/*!
 * Destructeur par défaut
 *
 */
CSommet::~CSommet(void)
{
	//On appel le destructeur pour tous les arcs arrivants
	//Et on d"salloue la liste
	if (pARCSOMListeArcsArrivants) {

		for (unsigned uBoucle = 0; uBoucle < this->uSOMTailleListeA; ++uBoucle) {
			delete pARCSOMListeArcsArrivants[uBoucle];
		}

		free(pARCSOMListeArcsArrivants);
	}

	//On fait pareil pour les arcs sortants
	if (pARCSOMListeArcsSortants) {

		for (unsigned uBoucle = 0; uBoucle < this->uSOMTailleListeS; ++uBoucle) {
			delete pARCSOMListeArcsSortants[uBoucle];
		}

		free(pARCSOMListeArcsSortants);
	}
}


/*!
 * Accesseur en lecture de uSOMId.
 *
 * \return Le numéro du sommet
 */
unsigned int CSommet::SOMGetId(void) {
	return uSOMId;
}


/*!
 * Accesseur en lecture de uSOMTailleListeArrivants.
 *
 * \return Le nombre d'arcs arrivants au sommet
 */
unsigned int CSommet::SOMGetTailleA()
{
	return uSOMTailleListeA;
}


/*!
 * Accesseur en lecture de uSOMTailleListeS.
 *
 * \return Le nombre d'arcs partants du sommet
 */
unsigned int CSommet::SOMGetTailleS()
{
	return uSOMTailleListeS;
}


/*!
 * Ajoute un arc arrivant au sommet.
 *
 * \param uDestination La destination de l'objet CArc à ajouter à la liste des arcs arrivants
 * \pre Il n'existe pas d'objet CArc dans la liste des arcs arrivants ayant pour destination uDestination.
 */
void CSommet::SOMAjouterArcArrivant(unsigned int uDestination) {

	//Verification qu'il n'y ai pas de doublons
	if (SOMChercherArcArrivant(uDestination) == -1) {

		CArc ** pARCNouvelleListe = (CArc **) realloc(pARCSOMListeArcsArrivants, sizeof(CArc *)*(++uSOMTailleListeA));

		//Erreur si allocation échouée
		if (pARCNouvelleListe == NULL) {
			throw(CException(CSOMMET_Alloc_Echouee, "CSommet::SOMAjouterArcArrivant(unsigned int uDestination) : Erreur d'allocation/réallocation.\n"));
		}

		pARCNouvelleListe[uSOMTailleListeA-1] = new CArc(uDestination);
		pARCSOMListeArcsArrivants = pARCNouvelleListe;
	}

}


/*!
 * Retire un arc arrivant au sommet.
 *
 * \param uDestination La destination de l'objet CArc à supprimer de la liste des arcs arrivants
 * \pre Il existe un objet CArc dans la liste des arcs arrivants ayant pour destination uDestination.
 */
void CSommet::SOMRetirerArcArrivant(unsigned int uDestination) {

	//Entrée : il existe bien la connexion de this vers uDestination
	if (SOMChercherArcArrivant(uDestination) != -1) {

		CArc ** pARCNouvelleListe = (CArc **) malloc(sizeof(CArc *)*(uSOMTailleListeA - 1));

		//Erreur si allocation échouée
		if (pARCNouvelleListe == NULL) {
			throw(CException(CSOMMET_Alloc_Echouee, "CSommet::SOMRetirerArcArrivant(unsigned int uDestination) : Erreur d'allocation.\n"));
		}

		//On parcourt tous les arcs
		for (unsigned uBoucle = 0, uCounter = 0; uBoucle < uSOMTailleListeA; uBoucle++) {

			//Entrée : Nous ne sommes pas sur l'arc à supprimer
			//		=> On copie dan l'arc dans le nouveau tableau
			if (pARCSOMListeArcsArrivants[uBoucle]->ARCGetDestination() != uDestination) {
				pARCNouvelleListe[uCounter] = pARCSOMListeArcsArrivants[uBoucle];
				++uCounter;
			}
			else {
				//delete pARCNouvelleListe[uCounter];
			}
		}

		//On supprime l'ancien tableau et on lui assigne le nouveau
		free(pARCSOMListeArcsArrivants);
		pARCSOMListeArcsArrivants = pARCNouvelleListe;

		
		uSOMTailleListeA--;
	}
}


/*!
 * Recherche l'arc arrivant ayant pour point de départ le sommet numéro uSOMIdDestination.
 *
 * \param uSOMIdDestination Le numéro du sommet de départ de l'arc
 * \return La position de l'arc cherché dans la liste des arcs arrivants si il y est, -1 sinon.
 */
int CSommet::SOMChercherArcArrivant(unsigned int uSOMIdDestination)
{
	unsigned int uBoucle;

	//On parcourt les arcs sortants
	for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++) {

		//Entrée : On trouve un arcs ayant pour destination uSOMIdDestination
		//		=> On renvoie l'index
		if (pARCSOMListeArcsArrivants[uBoucle]->ARCGetDestination() == uSOMIdDestination) {
			return uBoucle;
		}
	}
	return -1;
}


/*!
 * Lis l'arc arrivant en position uPos de la liste pARCSOMListeArcsArrivants.
 *
 * \param uPos La position de l'arc dans la liste pARCSOMListeArcsArrivants
 * \pre  0 <= uPos <= uSOMTailleListeA - 1
 * \return Objet CArc à la position uPos dans la liste des arcs entrants
 */
CArc* CSommet::SOMLireListeA(unsigned int uPos)
{

	//Entrée : uPos est un index hors limite de la liste des arcs arrivants
	//		=> On lève une erreur
	if (uPos > uSOMTailleListeA - 1 || uPos < 0) {
		char sExceptionMessage[255];
		sprintf_s(sExceptionMessage, 255, "CSommet::SOMLireListeA(unsigned int uPos) : Impossible de lire l'arc d'arrivee %d.\n", uPos);
		throw CException(CSOMMET_Lecture_Impossible, sExceptionMessage);
	}
		
	return pARCSOMListeArcsArrivants[uPos];
}


/*!
 * Ajoute un arc sortant au sommet.
 *
 * \param uDestination La destination de l'objet CArc à ajouter à la liste des arcs sortants
 * \pre Il n'existe pas d'objet CArc dans la liste des arcs sortants ayant pour destination uDestination.
 */
void CSommet::SOMAjouterArcSortant(unsigned int uDestination)
{

	//Verification qu'il n'y ai pas de doublons
	if (SOMChercherArcSortant(uDestination) == -1) {


		CArc ** pARCNouvelleListe = (CArc **) realloc(pARCSOMListeArcsSortants, sizeof(CArc *)*(++uSOMTailleListeS));

		//Erreur si allocation échouée
		if (pARCNouvelleListe == NULL) {
			throw(CException(CSOMMET_Alloc_Echouee, "CSommet::SOMAjouterArcSortant(unsigned int uDestination) : Erreur d'allocation/réallocation.\n"));
		}
		pARCNouvelleListe[uSOMTailleListeS-1] = new CArc(uDestination);
		pARCSOMListeArcsSortants = pARCNouvelleListe;

	}

}


/*!
 * Retire un arc sortant au sommet.
 *
 * \param uDestination La destination de l'objet CArc à supprimer de la liste des arcs sortants
 * \pre Il existe un objet CArc dans la liste des arcs sortants ayant pour destination uDestination.
 */
void CSommet::SOMRetirerArcSortant(unsigned int uDestination)
{
	//Entrée : il existe bien la connexion de this vers uDestination
	if (SOMChercherArcSortant(uDestination) != -1) {
		

		CArc ** pARCNouvelleListe = (CArc **) malloc(sizeof(CArc *)*(uSOMTailleListeS - 1));

		//Erreur si allocation échouée
		if (pARCNouvelleListe == NULL) {
			throw(CException(CSOMMET_Alloc_Echouee, "CSommet::SOMRetirerArcSortant(unsigned int uDestination) : Erreur d'allocation.\n"));
		}

		//On parcourt tous les arcs
		for (unsigned uBoucle = 0, uCounter = 0; uBoucle < uSOMTailleListeS; uBoucle++) {

			//Entrée : Nous ne sommes pas sur l'arc à supprimer
			//		=> On copie dan l'arc dans le nouveau tableau
			if (pARCSOMListeArcsSortants[uBoucle]->ARCGetDestination() != uDestination) {
				pARCNouvelleListe[uCounter] = pARCSOMListeArcsSortants[uBoucle];
				++uCounter;
			}
			else {
				//delete pARCNouvelleListe[uCounter];
			}
		}

		//On supprime l'ancien tableau et on lui assigne le nouveau
		free(pARCSOMListeArcsSortants);
		pARCSOMListeArcsSortants = pARCNouvelleListe;

		uSOMTailleListeS--;
	}
}


/*!
 * Recherche l'arc partant ayant pour point d'arrivé le sommet numéro uSOMIdDestination.
 *
 * \param uSOMIdDestination Le numéro du sommet d'arrivé de l'arc
 * \return La position de l'arc cherché dans la liste des arcs sortants si il y est, -1 sinon.
 */
int CSommet::SOMChercherArcSortant(unsigned int uSOMIdDestination)
{
	unsigned int uBoucle;

	//On parcourt les arcs sortants
	//=> Si on trouve un arcs ayant pour destination uSOMIdDestination : on renvoie l'index
	for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++) {
		if (pARCSOMListeArcsSortants[uBoucle]->ARCGetDestination() == uSOMIdDestination) {
			return uBoucle;
		}
	}
	return -1;
}


/*!
 * Lis l'arc en position uPos de la liste pARCSOMListeArcsSortants.
 *
 * \param uPos La position de l'arc dans la liste pARCSOMListeArcsSortants
 * \pre  0 <= uPos <= uSOMTailleListeS - 1
 * \return Objet CArc à la position uPos dans la liste des arcs sortants
 */
CArc* CSommet::SOMLireListeS(unsigned int uPos)
{
	//Entrée : uPos est un index hors limite de la liste des arcs sortants
	//		=> On lève une erreur
	if (uPos > uSOMTailleListeS - 1 || uPos < 0) {
		char sExceptionMessage[255];
		sprintf_s(sExceptionMessage, 255, "CSommet::SOMLireListeS(unsigned int uPos) : Impossible de lire l'arc de sortie %d.\n", uPos);
		throw CException(CSOMMET_Lecture_Impossible, sExceptionMessage);
	}

	return pARCSOMListeArcsSortants[uPos];
}


/*!
 * Teste si deux sommets sont liés dans le sens *this -> SOMParam
 *
 * \param SOMParam L'objet CSommet dont il faut vérifier la connexion avec this
 * \return true s'il existe un arc allant de cet objet vers SOMParam, false sinon.
 */
bool CSommet::SOMLies(CSommet & SOMParam)
{
	unsigned int uBoucle;
	unsigned int uValeurTeste = 0;

	//On parcourt les arcs arrivants à SOMParam tant qu'on en a pas trouvé provenant de this
	for (uBoucle = 0; uBoucle < SOMParam.uSOMTailleListeA && uValeurTeste == 0; uBoucle++) {
		
		//Entrée : on à trouvé un arc de this ayant pour destination SOMParam
		//		=> on incrémente la varable qui sert à vérifier qu'on à trouvé
		if (SOMParam.pARCSOMListeArcsArrivants[uBoucle]->ARCGetDestination() == SOMGetId()) {
			uValeurTeste++;
		}
	}

	//Si on à trouvé un résultat dans la boucle précédente :
	//On parcourt les arcs sortants des this tant qu'on en a pas trouvé ayant pour destination SOMParam
	for (uBoucle = 0; uBoucle < uSOMTailleListeS && uValeurTeste == 1; uBoucle++) {
		if (pARCSOMListeArcsSortants[uBoucle]->ARCGetDestination() == SOMParam.SOMGetId()) {
			uValeurTeste++;
		}
	}
	
	//Entrée : this contient un arc sortant vers SOMParam
	//		ET SOMParam contient un arcs entrant en provenance de this
	if (uValeurTeste == 2) {
		return true;
	}

	return false;
}


/*!
 * Inverse les arcs entrants et sortants.
 * Les CArcs arrivants deviennent les CArcs sortants et vice-versa
 *
 */
void CSommet::SOMInverser() {
	
	//On copie le pointeur sur la liste des arivants
	CArc **ARCTmp = this->pARCSOMListeArcsArrivants;
	//On copie la taille de la liste des arivants
	unsigned uiNbArrivants = this->uSOMTailleListeA;

	//La liste des arcs arrivants prend le pointeur sur la liste des arcs sortant, idem pour la taille
	this->pARCSOMListeArcsArrivants = this->pARCSOMListeArcsSortants;
	this->uSOMTailleListeA = this->uSOMTailleListeS;

	//La liste des arcs sortant prend le pointeur sur la liste temporaire (= liste arcs arrivants), idem pour la taille
	this->pARCSOMListeArcsSortants = ARCTmp;
	this->uSOMTailleListeS = uiNbArrivants;

}


/*!
 * Affiche le graphe sur la sortie standard.
 *
 */
void CSommet::SOMAfficherSommet() {
	unsigned int uBoucle;
	std::cout << "L'ID du sommet est : " << uSOMId << std::endl;
	
	std::cout << "La liste des arcs arrivants est :" << std::endl;

	//On parcourt les arcs arrivants et on les affiche (retour à la ligne tous les 3 affichés)
	for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++) {
		std::cout << "\t" << pARCSOMListeArcsArrivants[uBoucle]->ARCGetDestination() << ((uBoucle + 1) % 3 == 0 ? "\n" : "");
	}

	//On évite 2 retours à la lignes successifs
	if (uBoucle % 3 != 0){
		std::cout << std::endl;
	}
	
	std::cout << "La liste des arcs sortants est :" << std::endl;

	//On parcourt les arcs sortants et on les affiche (retour à la ligne tous les 3 affichés)
	for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++) {
		std::cout << "\t" << pARCSOMListeArcsSortants[uBoucle]->ARCGetDestination() << ((uBoucle + 1) % 3 == 0 ? "\n" : "");
	}

	//On évite 2 retours à la lignes successifs
	if (uBoucle % 3 != 0){
		std::cout << std::endl;
	}
	std::cout << std::endl;
}



/*!
 * Surcharge de l'operateur =
 * Copie le contenu de SOMParam dans l'objet appelant
 *
 * \param SOMParam L'objet CSommet à copier
 * \return Un pointeur sur l'objet appelant, copie de SOMParam
 */
CSommet & CSommet::operator=(const CSommet & SOMParam)
{
	if (this != &SOMParam) {
		uSOMId = SOMParam.uSOMId;
		uSOMTailleListeA = SOMParam.uSOMTailleListeA;
		uSOMTailleListeS = SOMParam.uSOMTailleListeS;
		
		//On alloue les nouvelles listes des arcs
		if (	( pARCSOMListeArcsArrivants = (CArc **) realloc( pARCSOMListeArcsArrivants, sizeof(CArc *) * (SOMParam.uSOMTailleListeA) ) ) == NULL
			||	( pARCSOMListeArcsSortants  = (CArc **) realloc( pARCSOMListeArcsSortants , sizeof(CArc *) * (SOMParam.uSOMTailleListeS) ) ) == NULL ) {

			throw(CException(CSOMMET_Alloc_Echouee, "CSommet::operator=(const CSommet & SOMParam) : Erreur d'allocation/réallocation.\n"));
		}

		unsigned int uBoucle;

		//On copier les arcs entrants
		for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++) {
			pARCSOMListeArcsArrivants[uBoucle] = new CArc(*SOMParam.pARCSOMListeArcsArrivants[uBoucle]);
		}

		//On copie les arcs sortants
		for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++) {
			pARCSOMListeArcsSortants[uBoucle] = new CArc(*SOMParam.pARCSOMListeArcsSortants[uBoucle]);
		}
	}
	return *this;
}