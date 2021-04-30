#ifndef CGRAPHE_H
#define CGRAPHE_H

#include <regex>
#include <fstream>
#include <string.h>
#include "CSommet.h"
#include "CArc.h"
#include "CException.h"


#define CGRAPHE_Chaine_Initialisation_Nulle	 1
#define CGRAPHE_Ouverture_Fichier_Impossible 2
#define CGRAPHE_Auto_Referencement			 3
#define CGRAPHE_Erreur_Syntaxe				 4
#define CGRAPHE_Erreur_NbSommets			 5
#define CGRAPHE_Erreur_NbArcs				 6
#define CGRAPHE_Sommet_Inconnu				 7
#define CGRAPHE_Sommet_Existant				 8
#define CGRAPHE_Arc_Inconnu					 9
#define CGRAPHE_Arc_Existant				 10
#define CGRAPHE_Alloc_Echouee				 11

class CGraphe
{
private :

	CSommet ** pSOMGPHListeSommet;
	unsigned int uGPHTailleLSom;


public:

	/*!
	 * Constructeur par défaut
	 * 
	 */
	CGraphe(void);

	
	/*!
	 * Constructeur de recopie
	 * 
	 * \param GPHParam L'objet CGraphe à copier
	 */
	CGraphe(CGraphe & GPHParam);

	
	/*!
	 * Constructeur de confort
	 * Création d'un graphe correctement initialisé à partir d'une chaîne de caractère OU un chemin vers un fichier contenant la chaîne de caractères.
	 * OU Une erreur si contenu est mal formatté ou qu'il contient des incohérences ou des erreurs.
	 *
	 * \param cpContenu La chaîne de caractère utilisée pour initialiser l'objet CGraphe
	 * \param bContenuEstChemin Un booléen qui indique si la variable cpContenu correspond à un chemin vers un fichier contenant l'initialisation d'un CGraphe (true) ou s'il s'agit directement d'une chaîne de caractère d'initialisation
	 */
	CGraphe(const char * cpContenu, bool bContenuEstChemin);


	/*!
	 * Destructeur par défaut
	 * 
	 */
	~CGraphe(void);



	/*!
	 * Cherche si le sommet existe
	 *
	 * \param uId Un numero de sommet
	 * \return L'index du sommet cherché
	 */
	int GPHChercherSommet(unsigned int uId);


	/*!
	 * Ajoute un nouveau sommet dans le graphe. 
	 * OU renvoie une erreur si le sommet existe déjà
	 * 
	 * \param uNumero Le numéro du nouveau sommet charché.
	 * \return L'index du sommet créé
	 */
	unsigned int GPHAjouterSommet(unsigned int uNumero);



	/*!
	 * Supprime un sommet dans le graphe.
	 * Supprime le sommet de numero uId du graphe ainsi que tout ses liens avec les autres sommets. 
	 * OU renvoie une erreur si le sommet n'existe pas
	 * 
	 * \param uId Numéro du sommet à supprimer
	 */
	void GPHSupprimerSommet(unsigned int uId);



	/*!
	 * Vérifie si deux sommets sont liés dans le sens sommet n° uSommetDep vers sommet n° uSommetArr
	 * 
	 * \param uSommetDep Le sommet de départ
	 * \param uSommetArr Le sommet d'arrivé
	 * \return true si les deux sommets sons liés dans le sens sommet n° uSommetDep vers sommet n° uSommetArr false sinon
	 */
	bool GPHLiees(unsigned int uSommetDep, unsigned int uSommetArr);


	/*!
	 * Lie deux sommets du graphe (créé l'arc Sommet de n° uIdDepart vers Sommet de n° uIdArrivee).
	 * OU renvoie une erreur s'il existe déjà un arc dirigé entre les deux sommets (càd de Sommet de n° uIdDepart vers Sommet de n° uIdArrivee)
	 * 
	 * \param uIdDepart Le numéro du sommet de départ
	 * \param uIdArrivee Le numéro du sommet d'arrivé
	 */
	void GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee);

	

	/*!
	 * Délie deux sommets du graphe (supprime l'arc Sommet de n° uIdDepart vers Sommet de n° uIdArrivee). 
	 * OU renvoie une erreur si l'arc n'existe pas
	 * 
	 * \param uIdDepart Le numéro du sommet de départ
	 * \param uIdArrivee Le numéro du sommet d'arrivé
	 */
	void GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee);


	/*!
	 * Renvoie les numéros des arcs sortants d'un sommet.
	 * 
	 * \param uId Le numero du sommet dont on veut les arcs sortants
	 * \return Un tableau d'entiers contenant les arcs sortant et en première position le nombre d'éléments scannés.
	 */
	unsigned int * GPHLireArcsS(unsigned int uId);


	/*!
	 * Renvoie les numéros des arcs arrivants d'un sommet.
	 *
	 * \param uId Le numero du sommet dont on veut les arcs arrivants
	 * \return Un tableau d'entiers contenant les arcs arrivants et en première position le nombre d'éléments scannés.
	 */
	unsigned int * GPHLireArcsA(unsigned int uId);


	/*!
	 * Affiche le sommet de numéro uId
	 * 
	 * \param uId Le numéro du sommet à afficher
	 */
	void GPHAfficherSommet(unsigned int uId);
	
	

	/*!
	 * Affiche le graphe
	 * 
	 */
	void GPHAfficherGraphe();


	/*!
	 * Inverse les arcs du graphe : les arcs sortants deviennent arrivants et vice-versa
	 * 
	 * \return Un nouvel objet CGraphe, inversé par rapport à 'objet appelant
	 */
	CGraphe & GPHRenverserGraphe();


	/*!
	 * Surcharge de l'opérateur =
	 * Copie le contenu de GPHParam dans l'objet appelant
	 *
	 * \param GPHParam L'objet CGraphe à copier
	 * \return Un pointeur sur l'objet appelant, copie de GPHParam
	 */
	CGraphe & operator=(CGraphe & GPHParam);
};

#endif