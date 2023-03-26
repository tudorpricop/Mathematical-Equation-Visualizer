#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <iostream>
using namespace std;

const int NUMAR_ENTITATI = 100;
const int LUNGIME_ENTITATE = 20;

typedef char entitate[LUNGIME_ENTITATE];

struct butonCuloare
{
    char nume[20];
    int culoare;
};

struct matriceDeCaractere
{
	entitate tablouEntitati[NUMAR_ENTITATI];
	int dimensiuneTablouEntitati;
};

struct nodA
{
	char info;
	int linie, coloana;
	int numarColoaneLinieFractie;
	nodA* st, * dr;
};
typedef nodA* arbore;

struct nodAE
{
	entitate info;
	int linie;
	float coloana;
	int numarColoaneLinieFractie;
	nodAE* st, * dr;
};
typedef nodAE* arboreE;

struct nod
{
	nod* urm;
	int info;
};
struct stiva
{
	nod* varf;
	int nrElem;
};

struct nodE
{
	nodE* urm;
	entitate info;
};
struct stivaE
{
	nodE* varf;
	int nrElem;
};


#endif // STRUCTURES_H_INCLUDED
