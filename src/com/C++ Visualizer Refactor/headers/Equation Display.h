#ifndef EQUATION_DISPLAY_H_INCLUDED
#define EQUATION_DISPLAY_H_INCLUDED

void afisareExpresie(arbore nodCurent, int lungimeCelula, int inaltimeCelula)
{
	if (nodCurent != NULL)
	{
		int x = nodCurent->coloana * lungimeCelula + lungimeCelula / 2;
		int y = nodCurent->linie * inaltimeCelula + inaltimeCelula / 2;
		int marimeFont = 7;

		settextstyle(8, 0, marimeFont);
		char element[50];
		element[0] = nodCurent->info;
		element[1] = '\0';
		if (nodCurent->info != '/')
			outtextxy(x - textwidth(element) / 2, y - textheight(element) / 2, element);
		else
		{
			line(x - (float)nodCurent->numarColoaneLinieFractie / 2 * lungimeCelula, y, x + (float)nodCurent->numarColoaneLinieFractie / 2 * lungimeCelula, y);///NOU
		}
		afisareExpresie(nodCurent->st, lungimeCelula, inaltimeCelula);
		afisareExpresie(nodCurent->dr, lungimeCelula, inaltimeCelula);
	}
}

void afisareExpresie(arboreE nodCurent, float lungimeCelula, float inaltimeCelula)
{
	if (nodCurent != NULL)
	{
		float x = nodCurent->coloana * lungimeCelula;
		float y = nodCurent->linie * inaltimeCelula + inaltimeCelula / 2;
		int marimeFont;
		marimeFont = min(min((int)lungimeCelula, (int)inaltimeCelula) / 8, 10);
		settextstyle(8, 0, marimeFont);
		if (!esteOperatorSlash(nodCurent->info))
		{
			outtextxy(x - (float)textwidth(nodCurent->info) / 2, y - (float)textheight(nodCurent->info) / 2, nodCurent->info);
		}
		else
		{
			line(x - (float)nodCurent->numarColoaneLinieFractie / 2 * lungimeCelula, y, x + (float)nodCurent->numarColoaneLinieFractie / 2 * lungimeCelula, y);
		}
		afisareExpresie(nodCurent->st, lungimeCelula, inaltimeCelula);
		afisareExpresie(nodCurent->dr, lungimeCelula, inaltimeCelula);
	}
}

#endif // EQUATION_DISPLAY_H_INCLUDED
