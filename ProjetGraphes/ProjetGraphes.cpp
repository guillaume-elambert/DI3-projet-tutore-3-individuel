// ProjetGraphes.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>
//#include <regex>
//#include <string>
#include <Windows.h>
#include "CGraphe.h"
#include "CSommet.h"
#include "CArc.h"
#include "CException.h"

using namespace std;


/*!
 * Fonction qui retourne le contenu d'un fichier, à partir de son chemin.
 * 
 * \param sChemin Le chemin vers le fichier souhaité
 * \return La chaîne de caractères correspondant au contenu du fichier
 */
string lireFichier(const char * cpChemin) {
	std::string sFileContent(""), sBuffer;
	std::fstream FILfichier(cpChemin);
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
		sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpChemin) : Impossible d'ouvrir le fichier \"%s\"\n", cpChemin);
		throw CException(Ouverture_Fichier_Impossible, sExceptionMessage);
	}

	FILfichier.close();
	return sFileContent;
}


int main(int argc, char * argv[])
{
	// Set console code page to UTF-8 so console known how to interpret string data
	SetConsoleOutputCP(CP_UTF8);

	// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
	setvbuf(stdout, nullptr, _IOFBF, 1000);


	if (argc > 1) {
		CGraphe *GPHLeGraphe;
		CGraphe *GPHLeGrapheInverse;
		for (int i = 1; i < argc; ++i) {
			try {
				printf(i > 1 ? "\n\n" : "");
				printf("----- GRAPHE DU FICHIER \"%s\" -----\n\n", argv[i]);
				GPHLeGraphe = new CGraphe(lireFichier(argv[i]).c_str());
				GPHLeGraphe->GPHAfficherGraphe();
				GPHLeGrapheInverse = &GPHLeGraphe->GPHRenverserGraphe();

				printf("\n----- GRAPHE INVERSE DU FICHIER \"%s\" -----\n\n", argv[i]);
				GPHLeGrapheInverse->GPHAfficherGraphe();

				cout << endl << endl;
				delete GPHLeGraphe;
				delete GPHLeGrapheInverse;
			}
			catch (CException EXCELevee) {
				printf("%s\n", EXCELevee.EXCGetMessage());
			}
		}
	}
	else {
		printf("Il faut passer au moins un fichier en parametre.\n");
	}


	return 0;
}
