#ifndef TREE_DISPLAY_H_INCLUDED
#define TREE_DISPLAY_H_INCLUDED

void afisareArbore(arbore nodCurent, arbore nodParinte, int lungimeCelula, int inaltimeCelula, int razaCerc)
{
	if (nodCurent != NULL)
	{
		ostringstream str1;
		str1 << nodCurent->info;
		string str2 = str1.str();
		char* str = &str2[0];
		int x = (nodCurent->coloana - 1) * lungimeCelula + lungimeCelula / 2;
		int y = (nodCurent->linie - 1) * inaltimeCelula + inaltimeCelula / 2;
		setcolor(1);
		circle(x, y, razaCerc);
		settextstyle(8, 0, 3);
		setcolor(3);
		outtextxy(x - 10, y - 7, str);
		if (nodParinte != NULL)
		{
			int x_Parinte = (nodParinte->coloana - 1) * lungimeCelula + lungimeCelula / 2;
			int y_Parinte = (nodParinte->linie - 1) * inaltimeCelula + inaltimeCelula / 2;
			setcolor(4);
			line(x, y, x_Parinte, y_Parinte);
		}
		afisareArbore(nodCurent->st, nodCurent, lungimeCelula, inaltimeCelula, razaCerc);
		afisareArbore(nodCurent->dr, nodCurent, lungimeCelula, inaltimeCelula, razaCerc);
	}
}

void afisareArbore(arboreE nodCurent, arboreE nodParinte, int lungimeCelula, int inaltimeCelula, int razaCerc)
{
	if (nodCurent != NULL)
	{
		int x = (nodCurent->coloana - 1) * lungimeCelula + lungimeCelula / 2;
		int y = (nodCurent->linie - 1) * inaltimeCelula + inaltimeCelula / 2;

		circle(x, y, razaCerc);

		if (nodParinte != NULL)
		{
			int x_Parinte = (nodParinte->coloana - 1) * lungimeCelula + lungimeCelula / 2;
			int y_Parinte = (nodParinte->linie - 1) * inaltimeCelula + inaltimeCelula / 2;

			line(x, y, x_Parinte, y_Parinte);
		}

		afisareArbore(nodCurent->st, nodCurent, lungimeCelula, inaltimeCelula, razaCerc);
		afisareArbore(nodCurent->dr, nodCurent, lungimeCelula, inaltimeCelula, razaCerc);

        settextstyle(8, 0, 3);
		setcolor(COLOR(71, 255, 10));
		setbkcolor(BLACK);
		outtextxy(x - textwidth(nodCurent->info) / 2, y - textheight(nodCurent->info) / 2, nodCurent->info);
		setcolor (Culori[index_culoareArbore].culoare);
	}
}

#endif // TREE_DISPLAY_H_INCLUDED
