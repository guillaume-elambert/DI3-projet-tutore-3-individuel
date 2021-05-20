#include "CFichier.h"

CFichier::CFichier()
{
	cpCheminFichier = nullptr;
	cpContenu = nullptr;
}

CFichier::CFichier(char * cpCheminFichier)
{
	if (cpCheminFichier == nullptr) {
		throw CException(CFICHIER_Chemin_Null, "CFichier::CFichier(char * cpCheminFichier) : La chaîne de caractères correspondant au chemin vers le fichier est nulle.\n");
	}

	std::string sFileContent(""), sBuffer;
	std::fstream FILfichier(cpCheminFichier);
	char sExceptionMessage[255];

	//Entrée : Le fichier n'a pas pu être ouvert
	if (!FILfichier.is_open())
	{
		sprintf_s(sExceptionMessage, 255, "CFichier::CFichier(char * cpCheminFichier) : Impossible d'ouvrir le fichier \"%s\".\n", cpCheminFichier);
		throw CException(CFICHIER_Ouverture_Fichier_Impossible, sExceptionMessage);
	}


	while (std::getline(FILfichier, sBuffer)) {
		//On concatène la ligne courrante avec les lignes précédentes
		//On ajoute on retour à la ligne si la ligne courrante n'est pas la dernière du fichier
		cpContenu += sBuffer + (!FILfichier.eof() ? "\n" : "");
	}

	FILfichier.close();

}

CFichier::~CFichier()
{
}

char * CFichier::getContenu()
{
	return _strdup(cpContenu.c_str());;
}
