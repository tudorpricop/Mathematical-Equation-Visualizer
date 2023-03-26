#ifndef GLOBAL_VARIABLES_H_INCLUDED
#define GLOBAL_VARIABLES_H_INCLUDED

const int INFINIT = 1000000000;

int index_culoareEcuatie=0;
int index_culoareArbore=0;

butonCuloare Culori[]= {{"Alb",WHITE}, {"Rosu Deschis",LIGHTRED},  {"Albastru Deschis",LIGHTBLUE},  {"Verde",GREEN},  {"Galben",YELLOW},  {"Mov Deschis",LIGHTMAGENTA}};


	arbore a = NULL, aExpresie = NULL;
	arbore b = NULL, bExpresie = NULL;

	arboreE _a = NULL, _aExpresie = NULL;
	arboreE _b = NULL, _bExpresie = NULL;

	int lungimePlansa = 900, inaltimePlansa = 600;

	int lungimeCelula, inaltimeCelula, razaCerc;
	int lungimeCelulaArboreCuParanteze, inaltimeCelulaArboreCuParanteze, razaCercArboreCuParanteze;
	int lungimeCelulaExpresie, inaltimeCelulaExpresie;
	int T[10000], fiu_st[10000], fiu_dr[10000];
	char arboreTablou[10000] = { 0 };
	int dimensiuneTablouri;

	int _lungimeCelula, _inaltimeCelula, _razaCerc;
	int _lungimeCelulaArboreCuParanteze, _inaltimeCelulaArboreCuParanteze, _razaCercArboreCuParanteze;
	float _lungimeCelulaExpresie, _inaltimeCelulaExpresie;
	float _lungimeCelulaExpresieCuParanteze, _inaltimeCelulaExpresieCuParanteze;

	string infix;
	string postfix;
	string prefix;

	matriceDeCaractere _infix;
	char infixString[NUMAR_ENTITATI * LUNGIME_ENTITATE];
	matriceDeCaractere _postfix;
	matriceDeCaractere _prefix;

	int nrLiniiEcuatie, nrColoaneEcuatie;
	int _nrLiniiEcuatie, _nrColoaneEcuatie;
	int _nrLiniiEcuatieCuParanteze, _nrColoaneEcuatieCuParanteze;

	int linieUrmatoareaFractie;
	int _linieUrmatoareaFractie;

	int minimNegativLinie, minimNegativColoana;
	int maxPozitivLinie, maxPozitivColoana, numarLiniiPlansaEcuatie, numarColoanePlansaEcuatie;

	int _minimNegativLinie;
	float _minimNegativColoana;
	int _maxPozitivLinie, _numarLiniiPlansaEcuatie, _numarColoanePlansaEcuatie;
	float _maxPozitivColoana;

	int _minimNegativLinieEcuatieCuParanteze;
	float _minimNegativColoanaEcuatieCuParanteze;
	int _maxPozitivLinieEcuatieCuParanteze, _numarLiniiPlansaEcuatieCuParanteze, _numarColoanePlansaEcuatieCuParanteze;
	float _maxPozitivColoanaEcuatieCuParanteze;

#endif // GLOBAL_VARIABLES_H_INCLUDED
