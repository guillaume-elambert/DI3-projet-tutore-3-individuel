#include "CParser.h"

/*************************************************
*****NOM : CParser
**************************************************
*****Constructeur par défaut
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : néant
*****Entraîne : Création d'un parser vide
*************************************************/
CParser::CParser()
{
	CString STRTypeAttribut = "fin";
	iPARValeurAttribut = 0;
	STRPARChemin = CString();
	STRPARContenuAttribut = CString();
	cPARCaractereActuel = '\0';
}

/*************************************************
*****NOM : CParser
**************************************************
*****Constructeur de confort (CString)
**************************************************
*****Entrée : Une chaine de charactère du chemin du fichier à convertir
*****Nécessite : Un chemin valide
*****Sortie : néant
*****Entraîne : Création d'un parser initialisé avec le chemin,
si non valide, déclenche une exception indiquant la non validité du chemin
*************************************************/
CParser::CParser(const CString STRChemin)
{
	CString STRTypeAttribut = "fin";
	iPARValeurAttribut = 0;
	STRPARContenuAttribut = CString();
	cPARCaractereActuel = '\0';
	PARInitialiser(STRChemin);
}

/*************************************************
*****NOM : ~CParser
**************************************************
*****Destructeur
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : néant
*****Entraîne : Destruction d'un parser
*************************************************/
CParser::~CParser()
{
	PARFinaliser();
}

/*************************************************
*****NOM : PARLireType
**************************************************
*****Acesseur en lecture de PARTYAType
**************************************************
*****Entrée : néant
*****Nécessite : Un parser initialisé
*****Sortie : le type de la valeur
*****Entraîne : /
*************************************************/
CString CParser::PARLireType()
{
	return TYAPARTypeAttribut;
}

/*************************************************
*****NOM : PARLireNom
**************************************************
*****Acesseur en lecture de PARNomAttribut
**************************************************
*****Entrée : néant
*****Nécessite : être utilisé après PARLireType si il renvoi entier
*****Sortie : un CString représentant la valeur
*****Entraîne : /
*************************************************/
CString CParser::PARLireNom()
{
	return STRPARNomAttribut;
}

/*************************************************
*****NOM : PARLireValeur
**************************************************
*****Acesseur en lecture de PARValeur
**************************************************
*****Entrée : néant
*****Nécessite : être utilisé après PARLireType si il renvoi entier
*****Sortie : iParValeurAttribut
*****Entraîne : Retour de la valeur
*************************************************/
int CParser::PARLireValeur()
{
	return iPARValeurAttribut;
}

/*************************************************
*****NOM : PARInitialiser
**************************************************
*****Initialisation et mise au début de la lecture
**************************************************
*****Entrée : néant
*****Nécessite : Le parser a déjà un chemin valide
*****Sortie : néant
*****Entraîne : Initialisation du parser,
si chemin invalide, entraine une exception indiquant la non validité du chemin,
si déjà initialisé, le réinitialise.
*************************************************/
void CParser::PARInitialiser(const CString STRChemin)
{
	STRPARChemin = STRChemin;
	if (STRPARChemin.STRGetLongueur() == 0)
	{
		throw(CException(Ouverture_Fichier_Impossible));
	}
	if (FILPARFichier.is_open())
	{
		FILPARFichier.close();
	}
	FILPARFichier = ifstream(STRPARChemin.STRGetChaine(), ios::in);
	if (FILPARFichier.fail())
	{
		FILPARFichier.close();
		throw(CException(Ouverture_Fichier_Impossible));
	}
	PARSuivant();
}

/*************************************************
*****NOM : PARFinaliser
**************************************************
*****Finalisation de la lecture
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : true si la finalisation s'est faite,
false si l'initialisation ne s'était pas faite
*****Entraîne : Finalisation du parser, ferme le ifstream
*************************************************/
bool CParser::PARFinaliser()
{
	if (FILPARFichier.is_open())
	{
		FILPARFichier.close();
		CString STRTypeAttribut = "fin";
		iPARValeurAttribut = 0;
		STRPARChemin = "";
		STRPARContenuAttribut = "";
		cPARCaractereActuel = '\0';
		return true;
	}
	return false;
}

/*************************************************
*****NOM : PARSuivant
**************************************************
*****Passe à l'objet syntaxique suivant
**************************************************
*****Entrée : néant
*****Nécessite : Le parser est initialisé
*****Sortie : néant
*****Entraîne : Passage à l'entité synthaxique suivante
				Si à la fin, reste à la fin et renvoi false
*************************************************/
bool CParser::PARSuivant()
{
	if (FILPARFichier.is_open())
	{
		/* On vide le contenu précédent*/
		STRPARContenuAttribut = "";

		/*Si ce n'est pas le premier appel*/
		if (cPARCaractereActuel != '\0')
		{
			/*A chaque appel le dernier caractere reste en suspens, il faut donc l'ajouter sauf cas espace et regarder si c'est un separateur*/
			if (cPARCaractereActuel != ' ')
			{
				STRPARContenuAttribut += cPARCaractereActuel;
			}
		}

		while (FILPARFichier.get(cPARCaractereActuel))
		{
			if (PARIsSeparator(cPARCaractereActuel) || (STRPARContenuAttribut.STRGetLongueur() == 1 && PARIsSeparator(STRPARContenuAttribut[0])))
			{
				PARConvertirLigne();
				return true;
			}
			if (cPARCaractereActuel != ' ')
				STRPARContenuAttribut += cPARCaractereActuel;
		}

		/*Si on arrive ici, c'est que le FILPARFichier est arrivé à la fin sans separateur*/

		if (STRPARContenuAttribut.STRGetLongueur() == 0)
		{
			CString STRTypeAttribut = "fin";
			cPARCaractereActuel = '\0';
			return false;
		}
		else
		{
			cPARCaractereActuel = '\0';
			PARConvertirLigne();
		}

	}
	else
	{
		throw(CException(Fichier_Non_Ouvert));
	}
	return true;
}

/*************************************************
*****NOM : PARConvertirLigne
**************************************************
*****Permet au parser de lire convertir l'attribut
trouvé en type voir en valeur pour les cas spécifiques
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : néant
*****Entraîne : Mise à jour des attributs nom, type et valeur
*************************************************/
void CParser::PARConvertirLigne()
{
	unsigned int uIndexBoucle = 0;
	unsigned int uIndexEgal = 0;

	STRPARNomAttribut = "";
	iPARValeurAttribut = 0;
	CString STRTypeAttribut = "non reconnu";

	/*Tout les éléments synthaxique de 1 de longueur*/
	if (STRPARContenuAttribut.STRGetLongueur() == 1)
	{
		switch (STRPARContenuAttribut[0])
		{
		case ']':
			STRTypeAttribut = "fin de tableau";
			break;
		case ',':
			STRTypeAttribut = "virgule";
			break;
		case '\n':
			STRTypeAttribut = "saut";
			break;
		default:
			break;
		}
	}
	/*Tout les éléments synthaxique de plus de 1 de longueur*/
	else
	{
		/*Ils ont tous le format nomAttribut=valeur donc on cherche le premier égal*/
		uIndexEgal = STRPARContenuAttribut.STRFindNextIndexSeparators(0, "=");

		/*Le égal ne doit ni être au début ni à la fin sinon on a pas de valeur ou de nom d'attribut*/
		if (uIndexEgal > 0 && uIndexEgal < STRPARContenuAttribut.STRGetLongueur() - 1)
		{
			/*Debut de tableau*/
			if (STRPARContenuAttribut[uIndexEgal + 1] == '[' && STRPARContenuAttribut.STRGetLongueur() == uIndexEgal + 2)
			{
				CString STRTypeAttribut = "debutTableau";
			}
			/*Valeur entière positive*/
			else if (STRPARContenuAttribut[uIndexEgal + 1] >= '0' && STRPARContenuAttribut[uIndexEgal + 1] <= '9')
			{
				CString STRTypeAttribut = "entier";
				/*Conversion de chaine en entier positif*/
				for (uIndexBoucle = uIndexEgal + 1; uIndexBoucle < STRPARContenuAttribut.STRGetLongueur(); uIndexBoucle++)
				{
					if (STRPARContenuAttribut[uIndexBoucle] >= '0' && STRPARContenuAttribut[uIndexBoucle] <= '9')
					{
						iPARValeurAttribut = iPARValeurAttribut * 10 + (STRPARContenuAttribut[uIndexBoucle] - '0');
					}
					/*Si il n'y a pas que des chiffres, c'est pas reconnu*/
					else
					{
						CString STRTypeAttribut = "nonReconnu";
						break;
					}
				}
			}
		}
		if (STRTypeAttribut != "nonReconnu")
			STRPARNomAttribut = STRPARContenuAttribut.STRDupliquerString(0, uIndexEgal - 1);
	}
}

/*************************************************
*****NOM : PARIsSeparator
**************************************************
*****Permet au parser de savoir si un caractere
spécifique délimite une séparation
**************************************************
*****Entrée : néant
*****Nécessite : néant
*****Sortie : boolean
*****Entraîne : /
*************************************************/
bool CParser::PARIsSeparator(const char cCaractere)
{
	if (cCaractere == ',' || cCaractere == '\n')
		return true;
	else
		return false;
}
