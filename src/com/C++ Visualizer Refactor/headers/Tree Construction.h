#ifndef TREE_CONSTRUCTION_H_INCLUDED
#define TREE_CONSTRUCTION_H_INCLUDED

#include "Matrix Construction.h"

void umplereCuSemnulIntrebarii(char arboreTablou[], int dimensiuneTablouri)
{
	for (int i = 1; i <= dimensiuneTablouri; i++)
		if (arboreTablou[i] == 0)
			arboreTablou[i] = '?';
}

void construireVectorDeTati(char poz[], int t[], int dimensiuneTablouri)
{
	t[1] = 0;
	for (int i = 1; i <= dimensiuneTablouri - 2; i++)
		if (poz[i] != '?')
		{
			t[i * 2] = i;
			t[i * 2 + 1] = i;
		}
		else
			t[i] = -1;
}

void construireVectorFiuStSiFiuDr(int t[], int fiu_st[], int fiu_dr[], int dimensiuneTablouri)
{
	for (int i = 1; i <= dimensiuneTablouri; i++)
	{
		fiu_dr[i] = 0;
		fiu_st[i] = 0;
	}
	for (int i = 2; i <= dimensiuneTablouri; i++)
		if (t[i] != -1)
		{
			if (i % 2 == 0)
				fiu_st[t[i]] = i;
			else
				fiu_dr[t[i]] = i;
		}
}

void adaugareNod(arbore& a, char k)
{
	a = new nodA;
	a->info = k;
	a->st = NULL;
	a->dr = NULL;
}

void adaugareNod(arboreE& a, const entitate k)
{
	a = new nodAE;
	strcpy(a->info, k);
	a->st = NULL;
	a->dr = NULL;
}

int radacina(int T[], int dimensiuneTablouri)
{
	int i;
	for (i = 1; i <= dimensiuneTablouri; i++)
		if (T[i] == 0)
			return i;
	return 0;
}

void construireArbore(arbore& a, int k, int fiu_st[], int fiu_dr[], char arboreTablou[])
{
	if (k != 0)
	{
		adaugareNod(a, arboreTablou[k]);
		construireArbore(a->st, fiu_st[k], fiu_st, fiu_dr, arboreTablou);
		construireArbore(a->dr, fiu_dr[k], fiu_st, fiu_dr, arboreTablou);
	}
}

int construireArbore(arboreE& a, matriceDeCaractere prefix, int idx)
{

	adaugareNod(a, prefix.tablouEntitati[idx]);
	if (esteOperator(prefix.tablouEntitati[idx]))
	{
		idx = construireArbore(a->st, prefix, idx + 1);
		idx = construireArbore(a->dr, prefix, idx + 1);
	}
	else if (esteFunctie(prefix.tablouEntitati[idx]))
		idx = construireArbore(a->st, prefix, idx + 1);
	return idx;
}

int numarLinii(arbore a)
{
	if (a == NULL)
		return 0;
	else
	{
		int nrl_st = numarLinii(a->st);
		int nrl_dr = numarLinii(a->dr);
		return max(nrl_st, nrl_dr) + 1;
	}
}

int numarLinii(arboreE a)
{
	if (a == NULL)
		return 0;
	else
	{
		int nrl_st = numarLinii(a->st);
		int nrl_dr = numarLinii(a->dr);
		return max(nrl_st, nrl_dr) + 1;
	}
}

int numarColoane(arbore a)
{
	if (a == NULL)
		return 0;
	else
	{
		int nrc_st = numarColoane(a->st);
		int nrc_dr = numarColoane(a->dr);
		return nrc_st + 1 + nrc_dr;
	}
}

int numarColoane(arboreE a)
{
	if (a == NULL)
		return 0;
	else
	{
		int nrc_st = numarColoane(a->st);
		int nrc_dr = numarColoane(a->dr);
		return nrc_st + 1 + nrc_dr;
	}
}

void repartizareLinieSiColoanaNoduriArbore(arbore& a, int linie, int coloana)
{
	a->linie = linie;
	a->coloana = coloana;
	arbore fiuStang = a->st;
	if (fiuStang != NULL)
		repartizareLinieSiColoanaNoduriArbore(fiuStang, linie + 1, coloana - numarColoane(fiuStang->dr) - 1);
	arbore fiuDrept = a->dr;
	if (fiuDrept != NULL)
		repartizareLinieSiColoanaNoduriArbore(fiuDrept, linie + 1, coloana + numarColoane(fiuDrept->st) + 1);
}

void repartizareLinieSiColoanaNoduriArbore(arboreE& a, int linie, int coloana)
{
	a->linie = linie;
	a->coloana = coloana;
	arboreE fiuStang = a->st;
	if (fiuStang != NULL)
		repartizareLinieSiColoanaNoduriArbore(fiuStang, linie + 1, coloana - numarColoane(fiuStang->dr) - 1);
	arboreE fiuDrept = a->dr;
	if (fiuDrept != NULL)
		repartizareLinieSiColoanaNoduriArbore(fiuDrept, linie + 1, coloana + numarColoane(fiuDrept->st) + 1);
}

void construireSiActualizareArbore(arbore& a, int T[], int fiu_st[], int fiu_dr[], int lungimePlansa, int inaltimePlansa,
	int& lungimeCelula, int& inaltimeCelula, int& razaCerc, char arboreTablou[], int dimensiuneTablouri)
{
	int nrL, nrC, coloanaRadacina, R;
	R = radacina(T, dimensiuneTablouri);
	construireArbore(a, R, fiu_st, fiu_dr, arboreTablou);
	nrL = numarLinii(a);
	nrC = numarColoane(a);
	lungimeCelula = lungimePlansa / nrC;
	inaltimeCelula = inaltimePlansa / nrL;
	razaCerc = min(lungimeCelula, inaltimeCelula) / 2;
	coloanaRadacina = numarColoane(a->st) + 1;
	repartizareLinieSiColoanaNoduriArbore(a, 1, coloanaRadacina);
}

void construireSiActualizareArbore(arboreE& a, int lungimePlansa, int inaltimePlansa,
	int& lungimeCelula, int& inaltimeCelula, int& razaCerc, matriceDeCaractere prefix)
{
	int nrL, nrC, coloanaRadacina;

	construireArbore(a, prefix, 0);

	nrL = numarLinii(a);
	nrC = numarColoane(a);
	lungimeCelula = lungimePlansa / nrC;
	inaltimeCelula = inaltimePlansa / nrL;
	razaCerc = min(lungimeCelula, inaltimeCelula) / 2;
	coloanaRadacina = numarColoane(a->st) + 1;
	repartizareLinieSiColoanaNoduriArbore(a, 1, coloanaRadacina);
}

void actualizareArboreCuParanteze(arbore a, int lungimePlansa, int inaltimePlansa, int& lungimeCelula, int& inaltimeCelula, int& razaCerc)
{
	int nrL, nrC, coloanaRadacina;
	nrL = numarLinii(a);
	nrC = numarColoane(a);
	lungimeCelula = lungimePlansa / nrC;
	inaltimeCelula = inaltimePlansa / nrL;
	razaCerc = min(lungimeCelula, inaltimeCelula) / 2;
	coloanaRadacina = numarColoane(a->st) + 1;
	repartizareLinieSiColoanaNoduriArbore(a, 1, coloanaRadacina);
}

void actualizareArboreCuParanteze(arboreE a, int lungimePlansa, int inaltimePlansa, int& lungimeCelula, int& inaltimeCelula, int& razaCerc)
{
	int nrL, nrC, coloanaRadacina;
	nrL = numarLinii(a);
	nrC = numarColoane(a);
	lungimeCelula = lungimePlansa / nrC;
	inaltimeCelula = inaltimePlansa / nrL;
	razaCerc = min(lungimeCelula, inaltimeCelula) / 2;
	coloanaRadacina = numarColoane(a->st) + 1;
	repartizareLinieSiColoanaNoduriArbore(a, 1, coloanaRadacina);
}

int lungimeEcuatie(arbore a)
{
	int nr_st, nr_dr;
	if (a)
	{
		nr_st = lungimeEcuatie(a->st);
		nr_dr = lungimeEcuatie(a->dr);
		if (a->info == '/')
			return max(nr_st, nr_dr);
		else
			return nr_st + 1 + nr_dr;
	}
	else
		return 0;
}

int lungimeEcuatie(arboreE a)
{
	int nr_st, nr_dr;
	if (a)
	{
		nr_st = lungimeEcuatie(a->st);
		nr_dr = lungimeEcuatie(a->dr);
		if (esteOperatorSlash(a->info))
			return max(nr_st, nr_dr);
		else
			if (esteFunctie(a->info))
				return nr_st + (strlen(a->info) + 2) + nr_dr;
			else
				return nr_st + strlen(a->info) + nr_dr;
	}
	else
		return 0;
}

int inaltimeEcuatie(arbore a)
{
	if (a)
	{
		int nr_st = inaltimeEcuatie(a->st);
		int nr_dr = inaltimeEcuatie(a->dr);
		if (a->info == '/')
			return nr_st + 1 + nr_dr;
		else
			return max(max(nr_st, nr_dr), 1);
	}
	else
		return 0;
}

int inaltimeEcuatie(arboreE a)
{
	if (a)
	{
		int nr_st = inaltimeEcuatie(a->st);
		int nr_dr = inaltimeEcuatie(a->dr);
		if (esteOperatorSlash(a->info))
			return nr_st + 1 + nr_dr;
		else
			return max(max(nr_st, nr_dr), 1);
	}
	else
		return 0;
}

void duplicareArbore(arbore a, arbore& b)
{
	if (a)
	{
		b = new nodA;
		*b = *a;
		duplicareArbore(a->st, b->st);
		duplicareArbore(a->dr, b->dr);
	}
	else
		b = NULL;
}

void duplicareArbore(arboreE a, arboreE& b)
{
	if (a)
	{
		b = new nodAE;
		*b = *a;
		duplicareArbore(a->st, b->st);
		duplicareArbore(a->dr, b->dr);
	}
	else
		b = NULL;
}

void adaugareParantezaSt(arbore& a)
{
	nodA* aux = a;
	while (aux->st != NULL)
		aux = aux->st;
	adaugareNod(aux->st, '(');
}

void adaugareParantezaSt(arboreE& a)
{
	nodAE* aux = a;
	while (aux->st != NULL)
		aux = aux->st;
	adaugareNod(aux->st, _parantezaRotundaDeschisa);
}

void adaugareParantezaDr(arbore& a)
{
	nodA* aux = a;
	while (aux->dr != NULL)
		aux = aux->dr;
	adaugareNod(aux->dr, ')');
}

void adaugareParantezaDr(arboreE& a)
{
	nodAE* aux = a;
	while (aux->dr != NULL)
		aux = aux->dr;
	adaugareNod(aux->dr, _parantezaRotundaInchisa);
}

void adaugareParanteze(arbore& a)
{
	if (a)
	{
		adaugareParanteze(a->st);

		if (a->info == '+' || a->info == '-')
		{
			adaugareParantezaSt(a);
			adaugareParantezaDr(a);
		}

		adaugareParanteze(a->dr);
	}
}

void adaugareParanteze(arboreE& a)
{
	if (a)
	{
		adaugareParanteze(a->st);

		if (esteOperatorPlus(a->info) || esteOperatorMinus(a->info))
		{
			adaugareParantezaSt(a);
			adaugareParantezaDr(a);
		}

		adaugareParanteze(a->dr);
	}
}

void adaugareParantezaSt(arboreE& a, int linieOperator)
{
	nodAE* aux = a;
	while (aux->st != NULL)
		aux = aux->st;
	adaugareNod(aux->st, _parantezaRotundaDeschisa);
	aux->st->linie = linieOperator;
}

void adaugareParantezaDr(arboreE& a, int linieOperator)
{
	nodAE* aux = a;
	while (aux->dr != NULL)
		aux = aux->dr;
	adaugareNod(aux->dr, _parantezaRotundaInchisa);
	aux->dr->linie = linieOperator;
}

void adaugareParanteze(arboreE& a, arboreE nodParinte)
{
	if (a)
	{
		adaugareParanteze(a->st, a);

		if (nodParinte && (esteOperatorAsterisc(nodParinte->info) || esteOperatorControl(nodParinte->info)) && (esteOperatorPlus(a->info) || esteOperatorMinus(a->info)))
		{
			adaugareParantezaSt(a, a->linie);
			adaugareParantezaDr(a, a->linie);
		}

		adaugareParanteze(a->dr, a);
	}
}

void adaugareFunctieSt(arboreE& a, entitate functie, int linieOperator)
{
	nodAE* aux = a;
	while (aux->st != NULL)
		aux = aux->st;
	adaugareNod(aux->st, functie);
	aux->st->linie = linieOperator;
}

void actualizareArboreExpresieCuFunctii(arboreE& a, arboreE nodParinte, arboreE nodParinteParinte)
{
	if (a)
	{
		actualizareArboreExpresieCuFunctii(a->st, a, nodParinte);
		actualizareArboreExpresieCuFunctii(a->dr, a, nodParinte);

		if (nodParinte && esteFunctie(nodParinte->info))
		{
			adaugareParantezaSt(a, a->linie);

			adaugareFunctieSt(a, nodParinte->info, a->linie);

			if (nodParinteParinte)
			{
				if (nodParinteParinte->st && esteFunctie(nodParinteParinte->st->info) && nodParinteParinte->st->st == a)
					nodParinteParinte->st = a;
				if (nodParinteParinte->st && esteFunctie(nodParinteParinte->st->info) && nodParinteParinte->st->dr == a)
					nodParinteParinte->st = a;
				if (nodParinteParinte->dr && esteFunctie(nodParinteParinte->dr->info) && nodParinteParinte->dr->st == a)
					nodParinteParinte->dr = a;
				if (nodParinteParinte->dr && esteFunctie(nodParinteParinte->dr->info) && nodParinteParinte->dr->dr == a)
					nodParinteParinte->dr = a;

			}
			adaugareParantezaDr(a, a->linie);
		}

	}
}

void actualizareArboreExpresieCuFuctiiInRadacina(arboreE& a)
{
	while (esteFunctie(a->info))
	{
		arboreE aux = a;
		a = a->st;
		delete aux;
	}
}

void intitializareLiniiColoaneCuInfinit(arbore a)
{
	if (a)
	{
		a->linie = a->coloana = INFINIT;

		a->numarColoaneLinieFractie = 0;

		intitializareLiniiColoaneCuInfinit(a->st);

		intitializareLiniiColoaneCuInfinit(a->dr);
	}
}

void intitializareLiniiColoaneCuInfinit(arboreE a)
{
	if (a)
	{
		a->linie = a->coloana = INFINIT;

		a->numarColoaneLinieFractie = 0;

		intitializareLiniiColoaneCuInfinit(a->st);

		intitializareLiniiColoaneCuInfinit(a->dr);
	}
}

#endif // TREE_CONSTRUCTION_H_INCLUDED
