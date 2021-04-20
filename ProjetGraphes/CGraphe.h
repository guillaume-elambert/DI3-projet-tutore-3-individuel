#ifndef CGRAPHE_H
#define CGRAPHE_H

#include "CSommet.h"
#include "CException.h"
#include "CParser.h"

#define Erreur_Graphe_Defaut 30
#define Erreur_Syntaxe 31
#define Sommet_Inconnu 32
#define Sommet_Existant 33
#define Arc_Inconnu 34
#define Arc_Existant 35

class CGraphe
{
private :

	CSommet * pSOMGPHListeSommet;
	unsigned int uGPHTailleLSom;
	unsigned int uGPHMaxIdSommet;

protected :

	/*************************************************
	*****NOM : GPHChercherSommet
	**************************************************
	*****Cherche si le somemt existe
	**************************************************
	*****Entrée : Un numero de sommet
	*****Nécessite : néant
	*****Sortie : l'index du numero du sommet
	OU -1 si non trouvé
	*****Entraîne : /
	*************************************************/
	int GPHChercherSommet(unsigned int uId);

public:

	/*************************************************
	*****NOM : CGraphe
	**************************************************
	*****Constructeur par défaut
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Création d'un graphe vide et correctement initialisé.
	*************************************************/
	CGraphe(void);

	/*************************************************
	*****NOM : CGraphe
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entrée : CGraphe & GPHParam
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Creation d'un nouveau graphe copie de GPHParam.
	*************************************************/
	CGraphe(CGraphe & GPHParam);

	/*************************************************
	*****NOM : CGraphe
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entrée : sChemin, le chemin vers le fichier d'initialisation.
	*****Nécessite : Le fichier contenu dans sChemin est d'un format correcte.
	*****Sortie : néant
	*****Entraîne : Création d'un graphe vide et correctement initialisé à partir du fichier stocké dans sChemin.
	OU Une bonne erreur des famille si le chemin ou le fichier est mauvais
	*************************************************/
	CGraphe(const CString & STRString);

	/*************************************************
	*****NOM : ~CGraphe
	**************************************************
	*****Destructeur par défaut
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Le graphe est prêt à être désalloué et ses ressources sont désallouées.
	*************************************************/
	~CGraphe(void);

	/*************************************************
	*****NOM : GPHAjouterSommet
	**************************************************
	*****Ajoute un nouveau sommet dans le graphe.
	**************************************************
	*****Entrée : Le numero du nouveau sommet
	*****Nécessite : néant
	*****Sortie : L'Id du nouveau sommet.
	*****Entraîne : Un nouveau sommet est créé dans le graphe.
	*************************************************/
	unsigned int GPHAjouterSommet(unsigned int uNumero);

	/*************************************************
	*****NOM : GPHSupprimerSommet
	**************************************************
	*****Supprime un sommet dans le graphe.
	**************************************************
	*****Entrée : SOMSommet un sommet du graphe.
	*****Nécessite : SOMSommet est un sommet du graphe.
	*****Sortie : néant
	*****Entraîne : Supprime SOMSOmmet du graphe ainsi que tout les liens avec les autres sommets.
	**************************************************/

	void GPHSupprimerSommet(unsigned int uId);

	/*************************************************
	*****NOM : GPHLierSommets
	**************************************************
	*****Lie deux sommets du graphe.
	**************************************************
	*****Entrée : CSommet SOMDepart, CSommet SOMArrivee.
	*****Nécessite : SOMDepart & SOMArrivee sont deux sommets du graphe.
	*****Sortie : néant
	*****Entraîne : Les deux sommets sont liés par un nouvel arc.
	*************************************************/
	void GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee);

	/*************************************************
	*****NOM : GPHDelierSommets
	**************************************************
	*****Délie deux sommets du graphe.
	**************************************************
	*****Entrée : CSommet SOMDepart, CSommet SOMArrivee.
	*****Nécessite : SOMDepart & SOMArrivee sont deux sommets liés du graphe.
	*****Sortie : néant
	*****Entraîne : Les deux sommets ne sont plus liés par un nouvel arc.
	*************************************************/
	void GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee);

	/*************************************************
	*****NOM : GPHLireArcsS
	**************************************************
	*****Renvoie les id des arcs sortants d'un sommet.
	**************************************************
	*****Entrée : unsigned int uId, le sommet à lire.
	*****Nécessite : Le sommet est dans le graphe.
	*****Sortie : Un tableau d'entier naturel contenant en première position le nombre d'éléments scannés. Sa taille sera donc de Tableau[0] + 1.
	*****Entraîne : /
	*************************************************/
	unsigned int * GPHLireArcsS(unsigned int uId);

	/*************************************************
	*****NOM : GPHLireArcsA
	**************************************************
	*****Renvoie les id des arcs arrivants d'un sommet.
	**************************************************
	*****Entrée : unsigned int uId, le sommet à lire.
	*****Nécessite : Le sommet est dans le graphe.
	*****Sortie : Un tableau d'entier naturel contenant en première position le nombre d'éléments scannés. Sa taille sera donc de Tableau[0] + 1.
	*****Entraîne : /
	*************************************************/
	unsigned int * GPHLireArcsA(unsigned int uId);

	/*************************************************
	*****NOM : GPHAfficherSommet
	**************************************************
	*****Affiche le sommet
	**************************************************
	*****Entrée : id du sommet
	*****Nécessite : cet id est valable
	*****Sortie : néant
	*****Entraîne : L'affichage des sommets du graphes
	*************************************************/
	void GPHAfficherSommet(unsigned int uId);
	
	/*************************************************
	*****NOM : GPHAfficherGraphe
	**************************************************
	*****Affiche le graphez
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : L'affichage des sommets du graphes
	*************************************************/
	void GPHAfficherGraphe();

	/*************************************************
	*****NOM : GPHRenverserGraphe
	**************************************************
	*****Renverse le graphe.
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : Un nouveau graphe inversé par rapport à cet objet.
	*****Entraîne : /
	*************************************************/
	CGraphe & GPHRenverserGraphe();

	/*************************************************
	*****NOM : CGraphe
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entrée : CGraphe & GPHParam
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Creation d'un nouveau graphe copie de GPHParam.
	*************************************************/
	CGraphe & operator=(CGraphe & GPHParam);

	bool GPHLiees(unsigned int uSommetDep, unsigned int uSommetArr);
};

#endif