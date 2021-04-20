#include "CGraphe.h"
#include "CString.h"
#include "CParser.h"
#include "CSommet.h"
#include "CArc.h"

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
int CGraphe::GPHChercherSommet(unsigned int uId)
{
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
		if (pSOMGPHListeSommet[uBoucle].SOMGetId() == uId)
			return(uBoucle);
	return -1;
}

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
CGraphe::CGraphe(void)
{
	pSOMGPHListeSommet = new CSommet[0];
	uGPHMaxIdSommet = 0;
	uGPHTailleLSom = 0;
}

CGraphe::CGraphe(CGraphe & GPHParam) {
	uGPHMaxIdSommet = GPHParam.uGPHMaxIdSommet;
	uGPHTailleLSom = GPHParam.uGPHTailleLSom;
	pSOMGPHListeSommet = new CSommet[GPHParam.uGPHTailleLSom];
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
		pSOMGPHListeSommet[uBoucle] = GPHParam.pSOMGPHListeSommet[uBoucle];
}

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
CGraphe::CGraphe(const CString & STRString)
{
	unsigned int uIndexBoucle = 0;
	unsigned int uNombreSommets = 0;
	unsigned int uNombreArcs = 0;
	unsigned int uDebutArc = 0;
	unsigned int uFinArc = 0;

	pSOMGPHListeSommet = new CSommet[0];
	uGPHMaxIdSommet = 0;
	uGPHTailleLSom = 0;

	CParser PARParser;
	PARParser.PARInitialiser(STRString);

	/*NombreSommet*/
	if (PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "NBSommets" && PARParser.PARLireValeur() >= 0)
	{
		uNombreSommets = PARParser.PARLireValeur();
	}
	else
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*NBArcs*/
	if (PARParser.PARSuivant() && PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "NBArcs" && PARParser.PARLireValeur() >= 0)
	{
		uNombreArcs = PARParser.PARLireValeur();
	}
	else
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*DebutTableau*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "debutTableau" || PARParser.PARLireNom() != "Sommets")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Ajout des sommets*/
	for (uIndexBoucle = 1; uIndexBoucle <= uNombreSommets; uIndexBoucle++)
	{
		/*Numero*/
		if (PARParser.PARSuivant() && PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "Numero")
		{
			GPHAjouterSommet(PARParser.PARLireValeur());
		}
		else
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}

		/*Saut de ligne*/
		if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}
	}
	/*FinTableau*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "finTableau")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*DebutTableau*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "debutTableau" || PARParser.PARLireNom() != "Arcs")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Ajout des arcs*/
	for (uIndexBoucle = 1; uIndexBoucle <= uNombreArcs; uIndexBoucle++)
	{
		/*Debut*/
		if (PARParser.PARSuivant() && PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "Debut")
		{
			uDebutArc = PARParser.PARLireValeur();
		}
		else
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}

		/*Virgule*/
		if (!PARParser.PARSuivant() || PARParser.PARLireType() != "virgule")
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}

		/*Fin*/
		if (PARParser.PARSuivant() && PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "Fin")
		{
			uFinArc = PARParser.PARLireValeur();
			GPHLierSommets(uDebutArc, uFinArc);
		}
		else
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}

		/*Saut de ligne*/
		if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}
	}
	/*FinTableau*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "finTableau")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	while (PARParser.PARSuivant())
	{
		if (PARParser.PARLireType() != "saut")
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}
	}
	PARParser.PARFinaliser();
}

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
CGraphe::~CGraphe(void)
{
	delete[] pSOMGPHListeSommet;
}

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
unsigned int CGraphe::GPHAjouterSommet(unsigned int uNumero)
{
	if (GPHChercherSommet(uNumero) != -1)
		throw CException(Sommet_Existant);

	CSommet SOMNouveauSommet(uNumero);
	uGPHMaxIdSommet++;

	if (uGPHTailleLSom == 0) {
		delete[] pSOMGPHListeSommet;
		pSOMGPHListeSommet = new CSommet[1];
		pSOMGPHListeSommet[0] = SOMNouveauSommet;
		uGPHTailleLSom++;
	}
	else {
		CSommet * pSOMNouvelleListe = new CSommet[uGPHTailleLSom + 1];
		unsigned int uBoucle;

		for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
			pSOMNouvelleListe[uBoucle] = pSOMGPHListeSommet[uBoucle];

		pSOMNouvelleListe[uGPHTailleLSom] = SOMNouveauSommet;
		delete[] pSOMGPHListeSommet;
		pSOMGPHListeSommet = new CSommet[uGPHTailleLSom + 1];

		for (uBoucle = 0; uBoucle < uGPHTailleLSom + 1; uBoucle++)
			pSOMGPHListeSommet[uBoucle] = pSOMNouvelleListe[uBoucle];

		uGPHTailleLSom++;
	}

	return uGPHMaxIdSommet - 1;
}

/*************************************************
*****NOM : GPHSupprimerSommet
**************************************************
*****Supprime un sommet dans le graphe.
**************************************************
*****Entrée : SOMSommet un sommet du graphe.
*****Nécessite : SOMSommet est un sommet du graphe.
*****Sortie : néant
*****Entraîne : Supprime SOMSOmmet du graphe ainsi que tout les liens avec les autres sommets.
*************************************************

1/ Si SOM n'existe pas => Exception
2/Chercher tout les sommets lié à SOM
3/Les délier
4/Echanger la position de ListeSOM[End] et SOM dans ListeSom.
5/Réallouer ListeSOM à la taille TailleListeSOM - 1
6/FIN
*/
void CGraphe::GPHSupprimerSommet(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);
	if (iPos != -1) {
		unsigned int uBoucle = 0;
		for (uBoucle = 0; uBoucle < uGPHMaxIdSommet; uBoucle++) {
			GPHDelierSommets(uId, uBoucle);
			GPHAfficherGraphe();
			GPHDelierSommets(uBoucle, uId);
			GPHAfficherGraphe();
		}
		CSommet * pSOMNouvelleListe = new CSommet[uGPHTailleLSom - 1];
		unsigned int uCpt = 0;
		for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
			if (pSOMGPHListeSommet[uBoucle].SOMGetId() == uId)
				uBoucle++;
			pSOMNouvelleListe[uCpt] = pSOMGPHListeSommet[uBoucle];
			uCpt++;
		}
		delete[] pSOMGPHListeSommet;
		pSOMGPHListeSommet = new CSommet[uGPHTailleLSom - 1];
		for (uBoucle = 0; uBoucle < uGPHTailleLSom - 1; uBoucle++)
			pSOMGPHListeSommet[uBoucle] = pSOMNouvelleListe[uBoucle];
		delete[] pSOMNouvelleListe;
		uGPHTailleLSom--;
	}
}

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
void CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee)
{
	int iPosDep = GPHChercherSommet(uIdDepart);
	int iPosArr = GPHChercherSommet(uIdArrivee);
	if (iPosArr != -1 && iPosDep != -1)
	{
		if (pSOMGPHListeSommet[iPosDep].SOMChercherArcSortant(uIdArrivee) != -1)
			throw CException(Arc_Existant);

		CArc ARCNArcA(uIdArrivee);
		CArc ARCNArcD(uIdDepart);
		pSOMGPHListeSommet[iPosDep].SOMAjouterArcSortant(ARCNArcA);
		pSOMGPHListeSommet[iPosArr].SOMAjouterArcArrivant(ARCNArcD);
	}
	else
	{
		throw CException(Sommet_Inconnu);
	}
}

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
void CGraphe::GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee)
{
	int iPosDep = GPHChercherSommet(uIdDepart);
	int iPosArr = GPHChercherSommet(uIdArrivee);

	cout << pSOMGPHListeSommet[iPosDep].SOMLies(pSOMGPHListeSommet[iPosArr]) << endl;

	if (iPosArr != -1 && iPosDep != -1 && pSOMGPHListeSommet[iPosDep].SOMLies(pSOMGPHListeSommet[iPosArr]) == true) {
		CArc ARCNArcA(uIdArrivee);
		CArc ARCNArcD(uIdDepart);
		pSOMGPHListeSommet[iPosDep].SOMRetirerArcSortant(ARCNArcA);
		pSOMGPHListeSommet[iPosArr].SOMRetirerArcArrivant(ARCNArcD);
	}
	else
	{
		//throw CException(Sommet_Inconnu);
	}
}

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
unsigned int * CGraphe::GPHLireArcsS(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);
	if (iPos == -1)
		return nullptr;
	if (pSOMGPHListeSommet[iPos].SOMGetTailleS() == 0)
		return nullptr;
	unsigned int uBoucle;
	unsigned int * puTableau = new unsigned int[pSOMGPHListeSommet[iPos].SOMGetTailleS() + 1];
	for (uBoucle = 1; uBoucle < pSOMGPHListeSommet[iPos].SOMGetTailleS() + 1; uBoucle++)
		puTableau[uBoucle] = pSOMGPHListeSommet[iPos].SOMLireListeS(uBoucle).ARCGetDestination();
	puTableau[0] = pSOMGPHListeSommet[iPos].SOMGetTailleS();
	return puTableau;
}


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
unsigned int * CGraphe::GPHLireArcsA(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);
	if (iPos == -1)
		return nullptr;
	if (pSOMGPHListeSommet[iPos].SOMGetTailleA() == 0)
		return nullptr;
	unsigned int uBoucle;
	unsigned int * puTableau = new unsigned int[pSOMGPHListeSommet[iPos].SOMGetTailleA() + 1];
	for (uBoucle = 1; uBoucle < pSOMGPHListeSommet[iPos].SOMGetTailleA() + 1; uBoucle++)
		puTableau[uBoucle] = pSOMGPHListeSommet[iPos].SOMLireListeA(uBoucle).ARCGetDestination();
	puTableau[0] = pSOMGPHListeSommet[iPos].SOMGetTailleA();
	return puTableau;
}

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
void CGraphe::GPHAfficherSommet(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);
	if (iPos != -1) {
		pSOMGPHListeSommet[iPos].SOMAfficherSommet();
	}
	else {
		cout << "Le sommet n'est pas dans le graphe." << endl;
	}
}

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
void CGraphe::GPHAfficherGraphe()
{
	cout << "Nb sommets : " << uGPHTailleLSom << endl;
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
		pSOMGPHListeSommet[uBoucle].SOMAfficherSommet();
	cout << endl;
}

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
CGraphe & CGraphe::GPHRenverserGraphe() {
	CGraphe * GPHGrapheRenv = new CGraphe(*this);
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		GPHGrapheRenv->pSOMGPHListeSommet[uBoucle].SOMInverser();
	}
	return *GPHGrapheRenv;
}

CGraphe & CGraphe::operator=(CGraphe & GPHParam)
{
	delete[] pSOMGPHListeSommet;
	uGPHMaxIdSommet = GPHParam.uGPHMaxIdSommet;
	uGPHTailleLSom = GPHParam.uGPHTailleLSom;
	pSOMGPHListeSommet = new CSommet[GPHParam.uGPHTailleLSom];
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
		pSOMGPHListeSommet[uBoucle] = GPHParam.pSOMGPHListeSommet[uBoucle];
	return *this;
}

bool CGraphe::GPHLiees(unsigned int uSommetDep, unsigned int uSommetArr)
{
	if (GPHChercherSommet(uSommetDep) != -1 && GPHChercherSommet(uSommetArr) != -1)
		return(pSOMGPHListeSommet[GPHChercherSommet(uSommetDep)].SOMLies(pSOMGPHListeSommet[GPHChercherSommet(uSommetArr)]));
	return false;
}
