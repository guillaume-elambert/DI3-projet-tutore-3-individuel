/*!
 * \file ProjetGraphes.cpp
 * \brief Fichier contenant la fonction main
 * \warning La fonction main nécessite au moins 1 chemin vers un fichier pour traiter la création d'un graphe, sinon fin de programme
 * \author Guillaume ELAMBERT
 * \author Clément NONCHER-GILLET
 * \date 2021
 */


#include <iostream>
#include <Windows.h>

#include "CFichier.h"
#include "CGraphe.h"
#include "CSommet.h"
#include "CArc.h"
#include "CException.h"
#include "conio.h"

using namespace std;


/*!
 * La fonction principale.
 * 
 * \warning Nécessite au moins 1 chemin vers un fichier pour traiter la création d'un graphe, sinon fin de programme
 * \param argc Le nombre d'arguments passés au programme
 * \param argv La liste des arguments passés au programme
 * \return 0 => l'exécution s'est faite sans erreur
 */
int main(int argc, char * argv[])
{
	// Set console code page to UTF-8 so console known how to interpret string data
	SetConsoleOutputCP(CP_UTF8);

	// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
	setvbuf(stdout, nullptr, _IOFBF, 1000);


	if (argc > 1) {

		CGraphe *GPHLeGraphe = NULL;
		CGraphe *GPHLeGrapheInverse = NULL;
		CFichier *FILLeFichier = NULL;

		//On parcourt l'ensemble des chemins passés en paramètre
		for (int i = 1; i < argc; ++i) {
			try {
				FILLeFichier = new CFichier(argv[i]);

				printf(i > 1 ? "\n\n" : "");


				printf("----- GRAPHE DU FICHIER \"%s\" -----\n\n", argv[i]);
				GPHLeGraphe = new CGraphe(FILLeFichier->getContenu());
				GPHLeGraphe->GPHAfficherGraphe();


				printf("\n----- GRAPHE INVERSE DU FICHIER \"%s\" -----\n\n", argv[i]);
				GPHLeGrapheInverse = &GPHLeGraphe->GPHRenverserGraphe();
				GPHLeGrapheInverse->GPHAfficherGraphe();

				cout << endl << endl;
				
				delete GPHLeGraphe;
				delete GPHLeGrapheInverse;
			}
			//On gère les erreurs de création du graphe et d'inversion du graphe
			catch (CException EXCELevee) {
				cerr << EXCELevee.EXCGetMessage();
			}
		}
	}
	else {
		cout << "Il faut passer au moins un fichier en paramètre.\n";
	}

	cout << "\n\nAppuyez sur une touche pour fermer" << endl;
	_getch();
	return 0;
}
