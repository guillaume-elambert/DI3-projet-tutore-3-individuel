#include "CGraphe.h"


/*!
 * Constructeur par défaut
 *
 */
CGraphe::CGraphe(void)
{
	pSOMGPHListeSommet = NULL;
	uGPHTailleLSom = 0;
}


/*!
 * Constructeur de recopie
 *
 * \param GPHParam L'objet CGraphe à copier
 */
CGraphe::CGraphe(CGraphe & GPHParam) {

	*this = GPHParam;
}


/*!
 * Constructeur de confort
 * Création d'un graphe correctement initialisé à partir d'une chaîne de caractère OU un chemin vers un fichier contenant la chaîne de caractères. 
 * OU Une erreur si contenu est mal formatté ou qu'il contient des incohérences ou des erreurs.
 *
 * \param cpContenu La chaîne de caractère utilisée pour initialiser l'objet CGraphe
 * \param bContenuEstChemin Un booléen qui indique si la variable cpContenu correspond à un chemin vers un fichier contenant l'initialisation d'un CGraphe (true) ou s'il s'agit directement d'une chaîne de caractère d'initialisation
 */
CGraphe::CGraphe(const char *cpContenu, bool bContenuEstChemin)
{
	if (cpContenu) {
		char *cpContentToUse;

		//Entrée : La variable cpContenu correspond au chemin vers un fichier
		//		=> On ouvre le fichier et on utilise le contenu pour l'initialisation
		if (bContenuEstChemin) {
			std::string sFileContent(""), sBuffer;
			std::fstream FILfichier(cpContenu);
			char sExceptionMessage[] = "";

			//Entrée : Le fichier à pu être ouvert
			//Sinon  : On renvoie une erreur
			if (FILfichier.is_open())
			{
				while (std::getline(FILfichier, sBuffer)) {
					//On concatène la ligne courrante avec les lignes précédentes
					//On ajoute on retour à la ligne si la ligne courrante n'est pas la dernière du fichier
					sFileContent += sBuffer + (!FILfichier.eof() ? "\n" : "");
				}

			}
			else {
				FILfichier.close();
				sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpChemin) : Impossible d'ouvrir le fichier \"%s\"\n", cpContenu);
				throw CException(CGRAPHE_Ouverture_Fichier_Impossible, sExceptionMessage);
			}

			FILfichier.close();
			cpContentToUse = _strdup(sFileContent.c_str());
		}
		else {
			cpContentToUse = _strdup(cpContenu);
		}

		//Initialisation par défaut
		pSOMGPHListeSommet = NULL;
		uGPHTailleLSom = 0;

		char sExceptionMessage[] = "";

		std::string sRegexResult;
		std::regex rRegex("NBSommets[ \\t]*=[ \\t]*([0-9]+)[ \\t]*\\nNBArcs[ \\t]*=[ \\t]*([0-9]+)[ \\t]*\\nSommets[ \\t]*=[ \\t]*(\\[)[ \\t]*\\n((?:Numero[ \\t]*=[ \\t]*[0-9]+\\n)*)\\][ \\t]*\\nArcs[ \\t]*=[ \\t]*(\\[)[ \\t]*\\n((?:Debut[ \\t]*=[ \\t]*[0-9]+[ \\t]*,[ \\t]*Fin[ \\t]*=[ \\t]*([0-9]+)[ \\t]*\\n)*)\\]\\s*");
		std::cmatch cmMatchGlobal, cmMatchNumeric;

		int iNbSommets, iNbArcs;
		int iNbInit = 0;

		std::regex rNumericRegex("[0-9]+");

		//Entrée : Le fichier correspond à l'expression régulière
		//Sinon  : On renvoie une erreur
		if (std::regex_match(cpContentToUse, cmMatchGlobal, rRegex)) {

			//On parcourt l'ensemble des résultats des groupes de capture du fichier (cf. la variable regex rRegex)
			for (unsigned uiRegexIndex = 1; uiRegexIndex < cmMatchGlobal.size(); ++uiRegexIndex) {
				sRegexResult = cmMatchGlobal[uiRegexIndex].str();

				//On vérifie si la ligne suivante est une initialisation du contenu
				switch (sRegexResult[sRegexResult.length() - 1]) {
				case '[':

					++iNbInit;

					//Entrée : Il y a bien un résultat de la recherche regex après celui courrant
					//Vérification normalement inutile car regex_match a renvoyé true
					if (++uiRegexIndex < cmMatchGlobal.size()) {

						sRegexResult = cmMatchGlobal[uiRegexIndex].str();

						int iCurrentResIndex = 0, iResValue, iTempInitValue;

						//On parcourt la zone d'initialisation
						while (std::regex_search(sRegexResult.c_str(), cmMatchNumeric, rNumericRegex)) {

							//On récupère la valeur du sommet/de l'arc
							iResValue = atoi(cmMatchNumeric.str().c_str());

							//Entrée : On est dans la partie d'initialisation des sommets
							//		=> On ajoute le sommet
							if (iNbInit == 1) {
								try {
									this->GPHAjouterSommet(iResValue);
								}
								catch (CException EXCELevee) {
									std::cerr << EXCELevee.EXCGetMessage();
								}
							}
							//Entrée : On est dans la partie d'initialisation des arcs
							else {
								//Entrée : On est sur un idex pair (càd on est sur un début)
								//		=> On stock la valeur pour la réutiliser quand on sera sur une fin de l'arc
								if (iCurrentResIndex % 2 == 0) {
									iTempInitValue = iResValue;
								}
								else {
									try {
										//On relie les deux sommets
										this->GPHLierSommets(iTempInitValue, iResValue);
									}
									catch (CException EXCELevee) {
										std::cerr << EXCELevee.EXCGetMessage();
									}
								}
							}

							//On passe à la suite de la chaîne
							sRegexResult = cmMatchNumeric.suffix();
							++iCurrentResIndex;
						}

						//Entrée : le nombre de sommets définit est différent que celui trouvé
						//		=> on renvoie une erreur
						if (iNbInit == 1 && iCurrentResIndex != iNbSommets) {
							sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpContenu, bool bContenuEstChemin) : %d sommets attendus %d sommets obtenus\n", iNbSommets, iCurrentResIndex);
							throw CException(CGRAPHE_Erreur_NbArcs, sExceptionMessage);
						}

						//Entrée : le nombre d'arcs définit est différent que celui trouvé
						//		=> On renvoie une erreur
						else if (iNbInit == 2 && (iCurrentResIndex /= 2) != iNbArcs) {
							sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpContenu, bool bContenuEstChemin) : %d arcs attendus %d arcs obtenus\n", iNbArcs, iCurrentResIndex);
							throw CException(CGRAPHE_Erreur_NbArcs, sExceptionMessage);
						}
					}

					break;

				default:
					switch (uiRegexIndex) {

					case 1:
						//printf("Le nombre de sommets est de : %s\n", sRegexResult.c_str());
						iNbSommets = atoi(sRegexResult.c_str());
						break;

					case 2:
						//printf("Le nombre d'arcs est de : %s\n", sRegexResult.c_str());
						iNbArcs = atoi(sRegexResult.c_str());

						//Entrée : On a défini un nombre de sommets à 0 pourtant on à defini des arcs
						//		=> On renvoie une erreur
						if (iNbSommets == 0 && iNbArcs != 0) {
							throw CException(CGRAPHE_Erreur_NbArcs, "CGraphe::CGraphe(const char *cpContenu, bool bContenuEstChemin) : Le nombre de sommets a été défini sur 0, le nombre d'arcs devrait l'être aussi.\n");
						}


						//Entrée : On a dépasser le nombre de possibilité totale de laision entre les sommets
						//		=> On renvoie une erreur
						if (iNbArcs > (iNbSommets * iNbSommets - iNbSommets)) {
							sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpContenu, bool bContenuEstChemin) : Top d'arcs a initialiser, %d maximum .\n", (iNbSommets * iNbSommets - iNbSommets));
							throw CException(CGRAPHE_Erreur_NbArcs, sExceptionMessage);
						}

						break;
					}
					break;
				}
			}
			free(cpContentToUse);
		}
		else {
			throw CException(CGRAPHE_Erreur_Syntaxe, "CGraphe::CGraphe(const char *cpContenu, bool bContenuEstChemin) : La chaîne de caractères ne correspond pas au format attendu\n");
		}
	}
	else {
	throw CException(CGRAPHE_Erreur_Syntaxe, "CGraphe::CGraphe(const char *cpContenu, bool bContenuEstChemin) : La chaîne de caractères est nulle\n");
	}
}


/*!
 * Destructeur par défaut
 *
 */
CGraphe::~CGraphe(void)
{
	if(pSOMGPHListeSommet) delete[] pSOMGPHListeSommet;
}



/*!
 * Cherche si le sommet existe
 *
 * \param uId Un numero de sommet
 * \return L'index du sommet cherché
 */
int CGraphe::GPHChercherSommet(unsigned int uId)
{
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		if (pSOMGPHListeSommet[uBoucle]->SOMGetId() == uId) {
			return(uBoucle);
		}
	}
	return -1;
}


/*!
 * Ajoute un nouveau sommet dans le graphe.
 * OU renvoie une erreur si le sommet existe déjà
 *
 * \param uNumero Le numéro du nouveau sommet charché.
 * \return L'index du sommet créé
 */
unsigned int CGraphe::GPHAjouterSommet(unsigned int uNumero)
{

	//Entrée : Le sommet existe déjà dans le graphe
	//		=> On renvoie une erreurs
	if (GPHChercherSommet(uNumero) != -1) {
		char sExceptionMessage[] = "";
		sprintf_s(sExceptionMessage, 255, "CGraphe::GPHAjouterSommet(unsigned int uNumero) : Le sommet numero %d existe deja.\n", uNumero);
		throw CException(CGRAPHE_Sommet_Existant, sExceptionMessage);
	}


	//Nouveau tableau à assigner à pSOMGPHListeSommet
	CSommet ** pSOMNouvelleListe = (CSommet **) realloc(pSOMGPHListeSommet, sizeof(CSommet *)*(uGPHTailleLSom + 1));

	//Erreur si allocation échouée
	if (pSOMNouvelleListe == NULL) {
		throw(CException(CGRAPHE_Alloc_Echouee, "CGraphe::GPHAjouterSommet(unsigned int uNumero) : Erreur d'allocation/réallocation.\n"));
	}

	//On ajoute le nouveau sommet
	pSOMNouvelleListe[uGPHTailleLSom] = new CSommet(uNumero);
	pSOMGPHListeSommet = pSOMNouvelleListe;

	uGPHTailleLSom++;
	return uGPHTailleLSom - 1;
}


/*!
 * Supprime un sommet dans le graphe.
 * Supprime le sommet de numero uId du graphe ainsi que tout ses liens avec les autres sommets.
 * OU renvoie une erreur si le sommet n'existe pas
 *
 * \param uId Numéro du sommet à supprimer
 */
void CGraphe::GPHSupprimerSommet(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);

	//Entrée : le sommet cherché existe
	if (iPos != -1) {

		//On supprime tous les arcs (arrivants et partant) du sommet
		for (unsigned uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
			try {
				GPHDelierSommets(uId, uBoucle);
				GPHDelierSommets(uBoucle, uId);
			}
			catch (CException EXCELevee) {
				std::cerr << EXCELevee.EXCGetMessage();
			}
		}

		CSommet ** pSOMNouvelleListe = (CSommet **) malloc(sizeof(CSommet *)*(uGPHTailleLSom - 1));


		//Erreur si allocation échouée
		if (pSOMNouvelleListe == NULL) {
			throw(CException(CGRAPHE_Alloc_Echouee, "CGraphe::GPHSupprimerSommet(unsigned int uId) : Erreur d'allocation.\n"));
		}

		//On copie tous les autres sommets dans un nouveau tableau
		for (unsigned uBoucle = 0, uCounter = 0; uBoucle < uGPHTailleLSom; uBoucle++) {

			//Ajoute le sommet dans la nouvelle liste s'il ce n'est pas celui à supprimer
			if (pSOMGPHListeSommet[uBoucle]->SOMGetId() != uId) {
				pSOMNouvelleListe[uCounter] = pSOMGPHListeSommet[uBoucle];
				uCounter++;
			}
			else {
				delete pSOMNouvelleListe[uCounter];
			}
		}

		//On supprime l'ancien tableau et on lui assigne le nouveau
		free(pSOMGPHListeSommet);
		pSOMGPHListeSommet = pSOMNouvelleListe;
		
		uGPHTailleLSom--;
	}
}


/*!
 * Vérifie si deux sommets sont liés dans le sens sommet n° uSommetDep vers sommet n° uSommetArr
 *
 * \param uSommetDep Le sommet de départ
 * \param uSommetArr Le sommet d'arrivé
 * \return true si les deux sommets sons liés dans le sens sommet n° uSommetDep vers sommet n° uSommetArr false sinon
 */
bool CGraphe::GPHLiees(unsigned int uSommetDep, unsigned int uSommetArr)
{
	//Entrée : les deux sommets existent dans le graphe
	if (GPHChercherSommet(uSommetDep) != -1 && GPHChercherSommet(uSommetArr) != -1) {
		//On renvoie true s'ils sont liés, false sinon
		return(pSOMGPHListeSommet[GPHChercherSommet(uSommetDep)]->SOMLies(*pSOMGPHListeSommet[GPHChercherSommet(uSommetArr)]));
	}

	return false;
}


/*!
 * Lie deux sommets du graphe (créé l'arc Sommet de n° uIdDepart vers Sommet de n° uIdArrivee).
 * OU renvoie une erreur s'il existe déjà un arc dirigé entre les deux sommets (càd de Sommet de n° uIdDepart vers Sommet de n° uIdArrivee)
 *
 * \param uIdDepart Le numéro du sommet de départ
 * \param uIdArrivee Le numéro du sommet d'arrivé
 */
void CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee)
{
	char sExceptionMessage[] = "";

	//Entrée : Pas de tentative de relier un sommet avec lui-même
	//Sinon  : On renvoie une erreur
	if (uIdDepart != uIdArrivee) {
		int iPosDep;
		int iPosArr = GPHChercherSommet(uIdArrivee);

		//Entrée : Le sommet d'arrivée existe dans le graphe
		//Sinon  : On renvoie une erreur
		if (iPosArr != -1)
		{
			iPosDep = GPHChercherSommet(uIdDepart);

			//Le sommet de départ existe dans le graphe
			//Sinon  : On renvoie une erreur
			if (iPosDep != -1) {

				//Entrée : Il existe déjà un arc dans le sens Sommet de n° uIdDepart vers Sommet de n° uIdArrivee
				//		=> On renvoie une erreur
				if (pSOMGPHListeSommet[iPosDep]->SOMChercherArcSortant(uIdArrivee) != -1) {
					sprintf_s(sExceptionMessage, 255, "CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : L'arc sortant depuis %d vers %d existe deja.\n", uIdDepart, uIdArrivee);
					throw CException(CGRAPHE_Arc_Existant, sExceptionMessage);
				}

				try {
					//On créé on arc de départ dans le sommet de départ et un d'arrivé dans le sommet d'arrivé
					pSOMGPHListeSommet[iPosDep]->SOMAjouterArcSortant(uIdArrivee);
					pSOMGPHListeSommet[iPosArr]->SOMAjouterArcArrivant(uIdDepart);
				}
				catch (CException EXCELevee) {
					std::cerr << EXCELevee.EXCGetMessage();
				}
			}
			else {
				sprintf_s(sExceptionMessage, 255, "CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Le sommet de depart %d est inconnu.\n", uIdDepart);
				throw CException(CGRAPHE_Sommet_Inconnu, sExceptionMessage);
			}
		}
		else
		{
			sprintf_s(sExceptionMessage, 255, "CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Le sommet d'arrivee %d est inconnu.\n", uIdArrivee);
			throw CException(CGRAPHE_Sommet_Inconnu, sExceptionMessage);
		}
	}
	else {
		sprintf_s(sExceptionMessage, 255, "CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Tentative de relier le sommet %d avec lui-meme.\n", uIdArrivee);
		throw CException(CGRAPHE_Auto_Referencement, sExceptionMessage);
	}
}


/*!
 * Délie deux sommets du graphe (supprime l'arc Sommet de n° uIdDepart vers Sommet de n° uIdArrivee).
 * OU renvoie une erreur si l'arc n'existe pas
 *
 * \param uIdDepart Le numéro du sommet de départ
 * \param uIdArrivee Le numéro du sommet d'arrivé
 */
void CGraphe::GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee)
{
	int iPosDep;
	int iPosArr = GPHChercherSommet(uIdArrivee);


	char sExceptionMessage[] = "";

	//Entrée : le sommet d'arrivé existe dans le graphe
	//Sinon  : On renvoie une erreur
	if (iPosArr != -1){

		iPosDep = GPHChercherSommet(uIdDepart);

		//Entrée : le sommet de départ existe dans le graphe
		//Sinon  : On renvoie une erreur
		if (iPosDep != -1) {

			//Entrée : Les sommets sont bien liés par un arc dans le sens Sommet de n° uIdDepart vers Sommet de n° uIdArrivee
			if (pSOMGPHListeSommet[iPosDep]->SOMLies(*pSOMGPHListeSommet[iPosArr]) == true) {
				
				try {
					//On créé on arc de départ dans le sommet de départ et un d'arrivé dans le sommet d'arrivé
					pSOMGPHListeSommet[iPosDep]->SOMRetirerArcSortant(uIdArrivee);
					pSOMGPHListeSommet[iPosArr]->SOMRetirerArcArrivant(uIdDepart);
				}
				catch (CException EXCELevee) {
					std::cerr << EXCELevee.EXCGetMessage();
				}
			}
		}
		else {
			sprintf_s(sExceptionMessage, 255, "CGraphe::GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Le sommet de depart %d est inconnu.\n", uIdDepart);
			throw CException(CGRAPHE_Sommet_Inconnu, sExceptionMessage);
		}
	}
	else
	{
		sprintf_s(sExceptionMessage, 255, "CGraphe::GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Le sommet d'arrivee %d est inconnu.\n", uIdArrivee);
		throw CException(CGRAPHE_Sommet_Inconnu, sExceptionMessage);
	}
}


/*!
 * Renvoie les numéros des arcs sortants d'un sommet.
 *
 * \param uId Le numero du sommet dont on veut les arcs sortants
 * \return Un tableau d'entiers contenant les arcs sortant et en première position le nombre d'éléments scannés.
 */
unsigned int * CGraphe::GPHLireArcsS(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);

	//Entrée : Le sommet n'existe pas dans le graphe
	if (iPos == -1) {
		return nullptr;
	}

	//Entrée : Le sommet n'a pas d'arcs sortants
	if (pSOMGPHListeSommet[iPos]->SOMGetTailleS() == 0) {
		return nullptr;
	}

	unsigned int uBoucle;
	unsigned int * puTableau = new unsigned int[pSOMGPHListeSommet[iPos]->SOMGetTailleS() + 1];
	
	//On parcourt tous les arcs sortants du sommet et on les met dans le tableau à retourner
	for (uBoucle = 1; uBoucle < pSOMGPHListeSommet[iPos]->SOMGetTailleS() + 1; uBoucle++) {
		try {
			puTableau[uBoucle] = pSOMGPHListeSommet[iPos]->SOMLireListeS(uBoucle)->ARCGetDestination();
		}
		catch (CException EXCELevee) {
			std::cerr << EXCELevee.EXCGetMessage();
		}
	}

	//On stock à l'indice 0 le nombre d'arcs dans le tableau à retourner
	puTableau[0] = pSOMGPHListeSommet[iPos]->SOMGetTailleS();
	return puTableau;
}


/*!
 * Renvoie les numéros des arcs arrivants d'un sommet.
 *
 * \param uId Le numero du sommet dont on veut les arcs arrivants
 * \return Un tableau d'entiers contenant les arcs arrivants et en première position le nombre d'éléments scannés.
 */
unsigned int * CGraphe::GPHLireArcsA(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);

	//Entrée : Le sommet n'existe pas dans le graphe
	if (iPos == -1) {
		return nullptr;
	}

	//Entrée : Le sommet n'a pas d'arcs arrivants
	if (pSOMGPHListeSommet[iPos]->SOMGetTailleA() == 0) {
		return nullptr;
	}

	unsigned int uBoucle;
	unsigned int * puTableau = new unsigned int[pSOMGPHListeSommet[iPos]->SOMGetTailleA() + 1];

	//On parcourt tous les arcs arrivants du sommet et on les met dans le tableau à retourner
	for (uBoucle = 1; uBoucle < pSOMGPHListeSommet[iPos]->SOMGetTailleA() + 1; uBoucle++) {
		try {
			puTableau[uBoucle] = pSOMGPHListeSommet[iPos]->SOMLireListeA(uBoucle)->ARCGetDestination();
		}
		catch (CException EXCELevee) {
			std::cerr << EXCELevee.EXCGetMessage();
		}
	}

	//On stock à l'indice 0 le nombre d'arcs dans le tableau à retourner
	puTableau[0] = pSOMGPHListeSommet[iPos]->SOMGetTailleA();
	return puTableau;
}


/*!
 * Affiche le sommet de numéro uId
 *
 * \param uId Le numéro du sommet à afficher
 */
void CGraphe::GPHAfficherSommet(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);

	//Entrée : Le sommet existe dans le graphe
	//Sinon  : On renvoie une erreur
	if (iPos != -1) {
		pSOMGPHListeSommet[iPos]->SOMAfficherSommet();
	}
	else {
		char sExceptionMessage[] = "";
		sprintf_s(sExceptionMessage, 255, "Le sommet %d n'est pas dans le graphe.\n", uId);
		throw CException(CGRAPHE_Sommet_Inconnu, sExceptionMessage);
	}
}


/*!
 * Affiche le graphe
 *
 */
void CGraphe::GPHAfficherGraphe()
{
	std::cout << "Nb sommets : " << uGPHTailleLSom << std::endl;
	unsigned int uBoucle;

	//On affiche tous les sommets
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		try {
			pSOMGPHListeSommet[uBoucle]->SOMAfficherSommet();
		}
		catch (CException EXCELevee) {
			std::cerr << EXCELevee.EXCGetMessage();
		}
	}
	std::cout << std::endl;
}


/*!
 * Inverse les arcs du graphe : les arcs sortants deviennent arrivants et vice-versa
 *
 * \return Un nouvel objet CGraphe, inversé par rapport à 'objet appelant
 */
CGraphe & CGraphe::GPHRenverserGraphe() {
	CGraphe * GPHGrapheRenv = new CGraphe(*this);
	unsigned int uBoucle;

	//On inverse les arcs pour chaque sommet
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		GPHGrapheRenv->pSOMGPHListeSommet[uBoucle]->SOMInverser();
	}
	return *GPHGrapheRenv;
}


/*!
 * Surcharge de l'opérateur =
 * Copie le contenu de GPHParam dans l'objet appelant
 *
 * \param GPHParam
 * \return Un pointeur sur l'objet appelant, copie de GPHParam
 */
CGraphe & CGraphe::operator=(CGraphe & GPHParam)
{
	if (this != &GPHParam) {
		uGPHTailleLSom = GPHParam.uGPHTailleLSom;
		//pSOMGPHListeSommet = new CSommet[GPHParam.uGPHTailleLSom];

		//On alloue la liste des sommets
		if ( ( pSOMGPHListeSommet = (CSommet **) realloc(pSOMGPHListeSommet, sizeof(CSommet *) * (GPHParam.uGPHTailleLSom) ) ) == NULL ) {

			throw(CException(CGRAPHE_Alloc_Echouee, "CSommet::operator=(const CSommet & SOMParam) : Erreur d'allocation/réallocation.\n"));
		}

		unsigned int uBoucle;

		//On copie la liste des sommets de GPHParam
		for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
			pSOMGPHListeSommet[uBoucle] = new CSommet(*GPHParam.pSOMGPHListeSommet[uBoucle]);
		}
	}

	return *this;
}
