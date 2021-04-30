// ProjetGraphes.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <Windows.h>
#include "CGraphe.h"
#include "CSommet.h"
#include "CArc.h"
#include "CException.h"
#include "conio.h"

using namespace std;



int main(int argc, char * argv[])
{
	// Set console code page to UTF-8 so console known how to interpret string data
	SetConsoleOutputCP(CP_UTF8);

	// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
	setvbuf(stdout, nullptr, _IOFBF, 1000);


	if (argc > 1) {
		CGraphe *GPHLeGraphe = NULL;
		CGraphe *GPHLeGrapheInverse = NULL;
		for (int i = 1; i < argc; ++i) {
			try {
				printf(i > 1 ? "\n\n" : "");
				printf("----- GRAPHE DU FICHIER \"%s\" -----\n\n", argv[i]);
				GPHLeGraphe = new CGraphe(argv[i], true);
				GPHLeGraphe->GPHAfficherGraphe();
				GPHLeGrapheInverse = &GPHLeGraphe->GPHRenverserGraphe();

				printf("\n----- GRAPHE INVERSE DU FICHIER \"%s\" -----\n\n", argv[i]);
				GPHLeGrapheInverse->GPHAfficherGraphe();

				cout << endl << endl;
				delete GPHLeGraphe;
				delete GPHLeGrapheInverse;
			}
			catch (CException EXCELevee) {
				delete GPHLeGraphe;
				delete GPHLeGrapheInverse;
				std::cerr << EXCELevee.EXCGetMessage();
			}
		}
	}
	else {
		printf("Il faut passer au moins un fichier en parametre.\n");
	}

	_getch();
	return 0;
}
