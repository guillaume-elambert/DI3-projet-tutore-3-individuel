#ifndef CSTRING_H
#define CSTRING_H

#include <iostream>

#include "CException.h"

#define Erreur_String_Base 60
#define Index_Incompatible 61

using namespace std;

class CString
{
private:
	char * sSTRChaine;
	unsigned int uSTRTaille;
	unsigned int uSTRTailleMemoire;
public:

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur par defaut
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Creation d'un CString vide ""
	*************************************************/
	CString();

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur de recopie
	**************************************************
	*****Entrée : STRString
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Creation d'un CString à partir de STRString
	*************************************************/
	CString(const CString & STRString);

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entrée : sChaine
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Creation d'un CString à partir de sChaine
	*************************************************/
	CString(const char * sChaine);

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entrée : iEntier
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Creation d'un CString à partir de iEntier
	*************************************************/
	CString(const int iEntier);

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entrée : uEntier
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Creation d'un CString à partir de uEntier
	*************************************************/
	CString(const unsigned int uEntier);

	/*************************************************
	*****NOM : ~CString
	**************************************************
	***** Destructeur
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : néant
	*****Entraîne : Destruction de sSTRChaine
	*************************************************/
	~CString();

	/*************************************************
	*****NOM :STRGetChaine
	**************************************************
	***** Accesseur en lecture de sSTRChaine
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : const char *
	*****Entraîne : Une copie du char * contenu dans CString
	*************************************************/
	const char * STRGetChaine();

	/*************************************************
	*****NOM : STRGetLongueur
	**************************************************
	***** Accesseur en lecture de uSTRTaille
	**************************************************
	*****Entrée : néant
	*****Nécessite : néant
	*****Sortie : unsigned int
	*****Entraîne : Une copie de uSTRTaille
	*************************************************/
	unsigned int STRGetLongueur();

	/*************************************************
	*****NOM : STRGetCaractere
	**************************************************
	***** Accesseur en lecture d'un char
	**************************************************
	*****Entrée : unsigned int uIndex
	*****Nécessite : uIndex valable
	*****Sortie : char
	*****Entraîne : Renvoi du uIndex iéme caractere de sSTRChaine
	*************************************************/
	char STRGetCaractere(unsigned int uIndex);

	/*************************************************
	*****NOM : STRStringSansCaracteres
	**************************************************
	***** Renvoi un CString sans tout les caracteres présents dans STRListeCaractere
	**************************************************
	*****Entrée : const CString & STRListeCaractere
	*****Nécessite : néant
	*****Sortie : CString &
	*****Entraîne : Création d'un CString & sans les caractères de STRListeCaractere
	*************************************************/
	CString & STRStringSansCaracteres(const CString & STRListeCaractere);

	/*************************************************
	*****NOM : STRDupliquerString
	**************************************************
	***** Duplique le CString courant entre les bornes indiquées
	**************************************************
	*****Entrée : unsigned int uIndexDepart = 0, unsigned int uIndexArrivee = UINT_MAX
	*****Nécessite : uIndexDepart et uIndexArrivee >= 0
	ET uIndexArrivee >= uIndexDepart
	*****Sortie : CString &
	*****Entraîne : Duplique le CString courant entre les bornes indiquées
	OU une exception
	*************************************************/
	CString & STRDupliquerString(unsigned int uIndexDepart = 0, unsigned int uIndexArrivee = UINT_MAX);

	/*************************************************
	*****NOM : STRFindNextIndexSeparators
	**************************************************
	*****Méthode de recherche de separateur
	**************************************************
	*****Entrée : unsigned int uIndexDepart, const CString & STRString
	*****Nécessite : uIndexDepart < uSTRTaille
	*****Sortie : unsigned int
	*****Entraîne : le renvoi de l'index coreespondant à la prochaine itération
	d'un des caractères de STRString dans l'objet, si non trouvé, ce sera celui de '\0'
	OU une exception
	*************************************************/
	unsigned int STRFindNextIndexSeparators(unsigned int uIndexDepart, const CString & STRString);

	/*************************************************
	*****NOM : operator==
	**************************************************
	***** Test l'égalité de 2 CString
	**************************************************
	*****Entrée : const CString & STRString, le CString avec qui comparer
	*****Nécessite : néant
	*****Sortie : bool
	*****Entraîne : true si egal, false sinon
	*************************************************/
	bool operator==(const CString & STRString);

	/*************************************************
	*****NOM : operator!=
	**************************************************
	***** Test l'inégalité de 2 CString
	**************************************************
	*****Entrée : const CString & STRString, le CString avec qui comparer
	*****Nécessite : néant
	*****Sortie : bool
	*****Entraîne : false si egal, true sinon
	*************************************************/
	bool operator!=(const CString & STRString);

	/*************************************************
	*****NOM : operator=
	**************************************************
	***** Opérateur d'affection
	**************************************************
	*****Entrée : const CString & STRString
	*****Nécessite : néant
	*****Sortie : CString &
	*****Entraîne : *this == STRString
	*************************************************/
	CString & operator=(const CString & STRString);

	/*************************************************
	*****NOM : operator+
	**************************************************
	*****Opérateur + char
	**************************************************
	*****Entrée : const CString & STRString
	*****Nécessite : néant
	*****Sortie : CString &
	*****Entraîne : concaténation de 2 CString en un troisième retourné
	*************************************************/
	CString & operator+(const CString & STRString);

	/*************************************************
	*****NOM : operator+=
	**************************************************
	*****Opérateur += CString
	**************************************************
	*****Entrée : const CString & STRString
	*****Nécessite : néant
	*****Sortie : CString &
	*****Entraîne : concaténation de 2 CString dans l'appelant
	*************************************************/
	CString & operator+=(const CString & STRString);

	/*************************************************
	*****NOM : operator+
	**************************************************
	*****Opérateur + char
	**************************************************
	*****Entrée : const char & STRString
	*****Nécessite : néant
	*****Sortie : CString &
	*****Entraîne : concaténation d'un CString et d'un char en un troisième retourné
	*************************************************/
	CString & operator+(const char & cChar);

	/*************************************************
	*****NOM : operator+=
	**************************************************
	*****Opérateur += char
	**************************************************
	*****Entrée : const char & STRString
	*****Nécessite : néant
	*****Sortie : CString &
	*****Entraîne : ajout de cChar à la fin de l'objet courant
	*************************************************/
	CString & operator+=(const char & cChar);

	/*************************************************
	*****NOM : operator[]
	**************************************************
	***** Accesseur du uIndexème caractère de sSTRString
	**************************************************
	*****Entrée : const unsigned int uIndex
	*****Nécessite : uIndex valable
	*****Sortie : char
	*****Entraîne : le renvoie d'une copie du uIndexème caractère
	*************************************************/
	char operator[](const unsigned int uIndex);
};

#endif