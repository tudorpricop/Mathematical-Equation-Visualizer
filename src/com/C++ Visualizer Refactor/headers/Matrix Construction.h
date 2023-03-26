#ifndef MATRIX_CONSTRUCTION_H_INCLUDED
#define MATRIX_CONSTRUCTION_H_INCLUDED

#include "Infix Prefix Conversion.h"
#include "Tree Construction.h"


void ecuatieStringCatreTablouDeEntitati(char ecuatieString[], matriceDeCaractere& infix)
{
	int i, j;
	char entitate[LUNGIME_ENTITATE];
	infix.dimensiuneTablouEntitati = 0;
	for (i = 0; i < strlen(ecuatieString); i++)
	{
		j = i;
		while (j < strlen(ecuatieString) && !strchr("()+-*/^", ecuatieString[j]))
			j++;
		if (i == j)
		{
			infix.tablouEntitati[infix.dimensiuneTablouEntitati][0] = ecuatieString[i];
			infix.tablouEntitati[infix.dimensiuneTablouEntitati][1] = '\0';
		}
		else
		{
			strncpy(infix.tablouEntitati[infix.dimensiuneTablouEntitati], ecuatieString + i, j - i);
			infix.tablouEntitati[infix.dimensiuneTablouEntitati][j - i] = '\0';
			i = j - 1;
		}
		infix.dimensiuneTablouEntitati++;
	}
}

int prefixCatreArboreTablou(int poz, int idx, int& dimensiuneTablouri, string s, char arboreTablou[])
{
	if (s[poz] == '*' || s[poz] == '+' || s[poz] == '-' || s[poz] == '/' || s[poz] == '^')
	{
		arboreTablou[idx] = s[poz];
		int newpoz = prefixCatreArboreTablou(poz + 1, idx * 2, dimensiuneTablouri, s, arboreTablou);
		int newpoz2 = prefixCatreArboreTablou(newpoz, idx * 2 + 1, dimensiuneTablouri, s, arboreTablou);
		return newpoz2;
	}
	else
	{
		arboreTablou[idx] = s[poz];
		dimensiuneTablouri = max(dimensiuneTablouri, idx);
		return poz + 1;
	}
}

void determinareNumarLiniiColoanePlansaEcuatie(arbore a, int& maxPozitivLinie, int& maxPozitivColoana)
{
	if (a)
	{
		maxPozitivLinie = max(maxPozitivLinie, a->linie);
		maxPozitivColoana = max(maxPozitivColoana, a->coloana);
		determinareNumarLiniiColoanePlansaEcuatie(a->st, maxPozitivLinie, maxPozitivColoana);
		determinareNumarLiniiColoanePlansaEcuatie(a->dr, maxPozitivLinie, maxPozitivColoana);
	}
}

void determinareNumarLiniiColoanePlansaEcuatie(arboreE a, int& maxPozitivLinie, float& maxPozitivColoana)
{
	if (a)
	{
		maxPozitivLinie = max(maxPozitivLinie, a->linie);
		maxPozitivColoana = max(maxPozitivColoana, a->coloana + (float)strlen(a->info) / 2 - 1);
		determinareNumarLiniiColoanePlansaEcuatie(a->st, maxPozitivLinie, maxPozitivColoana);
		determinareNumarLiniiColoanePlansaEcuatie(a->dr, maxPozitivLinie, maxPozitivColoana);
	}
}

void CrearePostfixPrefix(matriceDeCaractere infix, matriceDeCaractere& postfix, matriceDeCaractere& prefix)
{
	infixCatrePostfix(infix, postfix);
	infixCatrePrefix(infix, prefix);
}


void repartizareNoduriArboreExpresiePeLiniiFractie(arbore& a, int linieAnterioaraFractie, int& linieUrmatoareFractie,
	int deUndeVin, bool amPredecesorFractie)
{
	if (a != NULL)
	{
		int linieCurenta = linieAnterioaraFractie, linieUrmatoareaFractieSt, linieUrmatoareaFractieDr;
		if (a->info == '/')
		{
			if (amPredecesorFractie)
				if (deUndeVin <= 0)
					linieCurenta += 2;
				else
					linieCurenta -= 2;
			a->linie = linieCurenta;
			linieUrmatoareFractie = linieCurenta;
			amPredecesorFractie = true;
		}
		else
			linieUrmatoareFractie = INFINIT;
		if (a->info == '/')
		{
			repartizareNoduriArboreExpresiePeLiniiFractie(a->st, linieCurenta, linieUrmatoareaFractieSt, 1, amPredecesorFractie);
			repartizareNoduriArboreExpresiePeLiniiFractie(a->dr, linieCurenta, linieUrmatoareaFractieDr, -1, amPredecesorFractie);
		}
		else
		{
			repartizareNoduriArboreExpresiePeLiniiFractie(a->st, linieCurenta, linieUrmatoareaFractieSt, deUndeVin, amPredecesorFractie);
			repartizareNoduriArboreExpresiePeLiniiFractie(a->dr, linieCurenta, linieUrmatoareaFractieDr, deUndeVin, amPredecesorFractie);
		}
		if (a->info != '/')
			a->linie = min(linieUrmatoareaFractieSt, linieUrmatoareaFractieDr);
	}
	else
		linieUrmatoareFractie = INFINIT;
}

int inaltimeEcuatieLaNumitori(arboreE a)
{
	if (a)
	{
		int nr_st = inaltimeEcuatieLaNumitori(a->st);
		int nr_dr = inaltimeEcuatieLaNumitori(a->dr);
		if (esteOperatorSlash(a->info))
			return inaltimeEcuatie(a->dr);
		else
			return max(nr_st, nr_dr);
	}
	else
		return 0;
}

int inaltimeEcuatieLaNumaratori(arboreE a)
{
	if (a)
	{
		int nr_st = inaltimeEcuatieLaNumaratori(a->st);
		int nr_dr = inaltimeEcuatieLaNumaratori(a->dr);
		if (esteOperatorSlash(a->info))
			return inaltimeEcuatie(a->st);
		else
			return max(nr_st, nr_dr);
	}
	else
		return 0;
}

void repartizareNoduriArboreExpresiePeLiniiFractie(arboreE& a, int linieAnterioaraFractie, int& linieUrmatoareFractie,
	int deUndeVin, bool amPredecesorFractie)
{
	if (a != NULL)
	{
		int linieCurenta = linieAnterioaraFractie, linieUrmatoareaFractieSt, linieUrmatoareaFractieDr;
		if (esteOperatorSlash(a->info))
		{
			if (amPredecesorFractie)
				if (deUndeVin <= 0)
				{
					linieCurenta += inaltimeEcuatieLaNumaratori(a) + 1;
				}
				else
				{
					linieCurenta -= inaltimeEcuatieLaNumitori(a) + 1;
				}
			a->linie = linieCurenta;
			linieUrmatoareFractie = linieCurenta;
			amPredecesorFractie = true;
		}
		else
			linieUrmatoareFractie = INFINIT;
		if (esteOperatorSlash(a->info))
		{
			repartizareNoduriArboreExpresiePeLiniiFractie(a->st, linieCurenta, linieUrmatoareaFractieSt, 1, amPredecesorFractie);
			repartizareNoduriArboreExpresiePeLiniiFractie(a->dr, linieCurenta, linieUrmatoareaFractieDr, -1, amPredecesorFractie);
		}
		else
		{
			repartizareNoduriArboreExpresiePeLiniiFractie(a->st, linieCurenta, linieUrmatoareaFractieSt, deUndeVin, amPredecesorFractie);
			repartizareNoduriArboreExpresiePeLiniiFractie(a->dr, linieCurenta, linieUrmatoareaFractieDr, deUndeVin, amPredecesorFractie);
		}
		if (!esteOperatorSlash(a->info))
			a->linie = min(linieUrmatoareaFractieSt, linieUrmatoareaFractieDr);
	}
	else
		linieUrmatoareFractie = INFINIT;
}

void repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(arbore& a, int linieCurenta)
{
	if (a != NULL)
	{
		if (a->linie == INFINIT)
			a->linie = linieCurenta;
		if (a->info == '/')
		{
			repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(a->st, a->linie - 1);
			repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(a->dr, a->linie + 1);
		}
		else
		{
			repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(a->st, a->linie);
			repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(a->dr, a->linie);
		}
	}
}

void repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(arboreE& a, int linieCurenta)
{
	if (a != NULL)
	{
		if (a->linie == INFINIT)
			a->linie = linieCurenta;
		if (esteOperatorSlash(a->info))
		{
			repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(a->st, a->linie - 1);
			repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(a->dr, a->linie + 1);
		}
		else
		{
			repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(a->st, a->linie);
			repartizareNoduriArboreExpresiePeLiniiNumaratorNumitor(a->dr, a->linie);
		}
	}
}

void repartizareNoduriArboreExpresiePeLinii(arboreE& a, arboreE nodPredecesorFractie, int deUndeVin)
{
	if (a != NULL)
	{
		int linieCurenta;
		if (nodPredecesorFractie)
		{
			linieCurenta = nodPredecesorFractie->linie;
			if (deUndeVin < 0)
				linieCurenta += inaltimeEcuatieLaNumaratori(nodPredecesorFractie->dr) + 1;
			if (deUndeVin > 0)
				linieCurenta -= inaltimeEcuatieLaNumitori(nodPredecesorFractie->st) + 1;
		}
		else
			linieCurenta = 0;

		a->linie = linieCurenta;

		if (esteOperatorSlash(a->info))
		{
			repartizareNoduriArboreExpresiePeLinii(a->st, a, 1);
			repartizareNoduriArboreExpresiePeLinii(a->dr, a, -1);
		}
		else
		{
			repartizareNoduriArboreExpresiePeLinii(a->st, nodPredecesorFractie, deUndeVin);
			repartizareNoduriArboreExpresiePeLinii(a->dr, nodPredecesorFractie, deUndeVin);
		}
	}
}

void repartizareNoduriArboreExpresiePeColoane(arbore& a, int coloanaCurenta)
{
	if (a != NULL)
	{
		int lungimeDr, lungimeSt, lungimeNumarator, lungimeNumitor;
		a->coloana = coloanaCurenta;
		if (a->info == '/')
		{
			repartizareNoduriArboreExpresiePeColoane(a->st, coloanaCurenta);
			repartizareNoduriArboreExpresiePeColoane(a->dr, coloanaCurenta);
		}
		else
		{
			if (a->st)
				if (a->st->info == '/')
				{
					lungimeNumarator = lungimeEcuatie(a->st->st);

					lungimeNumitor = lungimeEcuatie(a->st->dr);

					lungimeDr = max(lungimeNumarator, lungimeNumitor) / 2;
				}
				else
					lungimeDr = lungimeEcuatie(a->st->dr);
			else
				lungimeDr = 0;

			repartizareNoduriArboreExpresiePeColoane(a->st, coloanaCurenta - lungimeDr - 1);

			if (a->dr)
				if (a->dr->info == '/')
				{
					lungimeNumarator = lungimeEcuatie(a->dr->st);

					lungimeNumitor = lungimeEcuatie(a->dr->dr);

					lungimeSt = max(lungimeNumarator, lungimeNumitor) / 2;
				}
				else
					lungimeSt = lungimeEcuatie(a->dr->st);
			else
				lungimeSt = 0;
			repartizareNoduriArboreExpresiePeColoane(a->dr, coloanaCurenta + lungimeSt + 1);
		}
	}
}

void repartizareNoduriArboreExpresiePeColoane(arboreE& a, float coloanaCurenta)
{
	if (a != NULL)
	{
		float lungimeDr, lungimeSt;
		int lungimeNumarator, lungimeNumitor;
		a->coloana = coloanaCurenta;
		if (esteOperator(a->info))
			if (esteOperatorSlash(a->info))
			{
				if (esteOperatorSlash(a->st->info))
					repartizareNoduriArboreExpresiePeColoane(a->st, coloanaCurenta);
				else
				{
					lungimeSt = lungimeEcuatie(a->st->st);
					lungimeDr = lungimeEcuatie(a->st->dr);

					repartizareNoduriArboreExpresiePeColoane(a->st, coloanaCurenta + (lungimeSt - lungimeDr) / 2);
				}
				if (esteOperatorSlash(a->dr->info))
					repartizareNoduriArboreExpresiePeColoane(a->dr, coloanaCurenta);
				else
				{
					lungimeSt = lungimeEcuatie(a->dr->st);
					lungimeDr = lungimeEcuatie(a->dr->dr);

					repartizareNoduriArboreExpresiePeColoane(a->dr, coloanaCurenta + (lungimeSt - lungimeDr) / 2);
				}
			}
			else
			{
				if (esteOperatorSlash(a->st->info))
				{
					lungimeNumarator = lungimeEcuatie(a->st->st);

					lungimeNumitor = lungimeEcuatie(a->st->dr);

					lungimeDr = (float)max(lungimeNumarator, lungimeNumitor) / 2;

					repartizareNoduriArboreExpresiePeColoane(a->st, coloanaCurenta - lungimeDr - 0.5);
				}
				else
				{
					lungimeDr = lungimeEcuatie(a->st->dr);
					repartizareNoduriArboreExpresiePeColoane(a->st, coloanaCurenta - lungimeDr - (float)strlen(a->st->info) / 2 - 0.5);
				}

				if (esteOperatorSlash(a->dr->info))
				{
					lungimeNumarator = lungimeEcuatie(a->dr->st);

					lungimeNumitor = lungimeEcuatie(a->dr->dr);

					lungimeSt = (float)max(lungimeNumarator, lungimeNumitor) / 2;

					repartizareNoduriArboreExpresiePeColoane(a->dr, coloanaCurenta + lungimeSt + 0.5);
				}
				else
				{
					lungimeSt = lungimeEcuatie(a->dr->st);
					repartizareNoduriArboreExpresiePeColoane(a->dr, coloanaCurenta + lungimeSt + (float)strlen(a->dr->info) / 2 + 0.5);
				}
			}
		else
		{
			if (a->st)
				repartizareNoduriArboreExpresiePeColoane(a->st, a->coloana - (float)strlen(a->info) / 2 - (float)strlen(a->st->info) / 2);
			if (a->dr)
				repartizareNoduriArboreExpresiePeColoane(a->dr, a->coloana + (float)strlen(a->info) / 2 + 0.5);

		}
	}
}

void determinareAbatereAfisareEcuatie(arbore a, int& minimNegativLinie, int& minimNegativColoana)
{
	if (a)
	{
		minimNegativLinie = min(minimNegativLinie, a->linie);
		minimNegativColoana = min(minimNegativColoana, a->coloana);
		determinareAbatereAfisareEcuatie(a->st, minimNegativLinie, minimNegativColoana);
		determinareAbatereAfisareEcuatie(a->dr, minimNegativLinie, minimNegativColoana);
	}
}

void determinareAbatereAfisareEcuatie(arboreE a, int& minimNegativLinie, float& minimNegativColoana)
{
	if (a)
	{
		minimNegativLinie = min(minimNegativLinie, a->linie);
		minimNegativColoana = min(minimNegativColoana, a->coloana - (float)strlen(a->info) / 2);
		determinareAbatereAfisareEcuatie(a->st, minimNegativLinie, minimNegativColoana);
		determinareAbatereAfisareEcuatie(a->dr, minimNegativLinie, minimNegativColoana);
	}
}

void corectieAbatereAfisareEcuatie(arbore& a, int minimNegativLinie, int minimNegativColoana)
{
	if (a)
	{
		a->linie += abs(minimNegativLinie);
		a->coloana += abs(minimNegativColoana);
		corectieAbatereAfisareEcuatie(a->st, minimNegativLinie, minimNegativColoana);
		corectieAbatereAfisareEcuatie(a->dr, minimNegativLinie, minimNegativColoana);
	}
}

void corectieAbatereAfisareEcuatie(arboreE& a, int minimNegativLinie, float minimNegativColoana)
{
	if (a)
	{
		a->linie += abs(minimNegativLinie);
		a->coloana += fabs(minimNegativColoana);
		corectieAbatereAfisareEcuatie(a->st, minimNegativLinie, minimNegativColoana);
		corectieAbatereAfisareEcuatie(a->dr, minimNegativLinie, minimNegativColoana);
	}
}

void actualizareNumarColoaneFractieInArboreExpresie(arbore& a)
{
	if (a)
	{
		if (a->info == '/')
			a->numarColoaneLinieFractie = max(lungimeEcuatie(a->st), lungimeEcuatie(a->dr));
		actualizareNumarColoaneFractieInArboreExpresie(a->st);
		actualizareNumarColoaneFractieInArboreExpresie(a->dr);
	}
}

void actualizareNumarColoaneFractieInArboreExpresie(arboreE& a)
{
	if (a)
	{
		if (esteOperatorSlash(a->info))
			a->numarColoaneLinieFractie = max(lungimeEcuatie(a->st), lungimeEcuatie(a->dr));
		actualizareNumarColoaneFractieInArboreExpresie(a->st);
		actualizareNumarColoaneFractieInArboreExpresie(a->dr);
	}
}

#endif // MATRIX_CONSTRUCTION_H_INCLUDED
