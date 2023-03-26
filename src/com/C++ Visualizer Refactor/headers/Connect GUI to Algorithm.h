#ifndef CONNECT_GUI_TO_ALGORITHM_H_INCLUDED
#define CONNECT_GUI_TO_ALGORITHM_H_INCLUDED

#include "Global Variables.h"
#include "Matrix Construction.h"

void main2()
{
	ecuatieStringCatreTablouDeEntitati(infixString, _infix);
	CrearePostfixPrefix(_infix, _postfix, _prefix);

	construireSiActualizareArbore(_a, lungimePlansa, inaltimePlansa, _lungimeCelula, _inaltimeCelula, _razaCerc, _prefix);

	duplicareArbore(_a, _b);

	adaugareParanteze(_b, NULL);

	actualizareArboreCuParanteze(_b, lungimePlansa, inaltimePlansa, _lungimeCelulaArboreCuParanteze, _inaltimeCelulaArboreCuParanteze, _razaCercArboreCuParanteze);



	_nrLiniiEcuatie = inaltimeEcuatie(_b);

	_nrColoaneEcuatie = lungimeEcuatie(_b);

	duplicareArbore(_a, _aExpresie);

	repartizareNoduriArboreExpresiePeLinii(_aExpresie, NULL, 0);

	actualizareNumarColoaneFractieInArboreExpresie(_aExpresie);

	repartizareNoduriArboreExpresiePeColoane(_aExpresie, 0);

	_minimNegativLinie = _minimNegativColoana = INFINIT;
	determinareAbatereAfisareEcuatie(_aExpresie, _minimNegativLinie, _minimNegativColoana);

	corectieAbatereAfisareEcuatie(_aExpresie, _minimNegativLinie, _minimNegativColoana);

	_maxPozitivLinie = _maxPozitivColoana = -INFINIT;
	determinareNumarLiniiColoanePlansaEcuatie(_aExpresie, _maxPozitivLinie, _maxPozitivColoana);
	_numarLiniiPlansaEcuatie = _maxPozitivLinie + 1;
	_numarColoanePlansaEcuatie = _maxPozitivColoana + 1;


	_lungimeCelulaExpresie = (float)lungimePlansa / _numarColoanePlansaEcuatie;
	_inaltimeCelulaExpresie = (float)inaltimePlansa / _numarLiniiPlansaEcuatie;

	duplicareArbore(_a, _bExpresie);

	repartizareNoduriArboreExpresiePeLinii(_bExpresie, NULL, 0);

	adaugareParanteze(_bExpresie, NULL);

	actualizareNumarColoaneFractieInArboreExpresie(_bExpresie);

	actualizareArboreExpresieCuFunctii(_bExpresie, NULL, NULL);
	actualizareArboreExpresieCuFuctiiInRadacina(_bExpresie);

	repartizareNoduriArboreExpresiePeColoane(_bExpresie, 0);

	_minimNegativLinieEcuatieCuParanteze = _minimNegativColoanaEcuatieCuParanteze = INFINIT;
	determinareAbatereAfisareEcuatie(_bExpresie, _minimNegativLinieEcuatieCuParanteze, _minimNegativColoanaEcuatieCuParanteze);

	corectieAbatereAfisareEcuatie(_bExpresie, _minimNegativLinieEcuatieCuParanteze, _minimNegativColoanaEcuatieCuParanteze);

	_maxPozitivLinieEcuatieCuParanteze = _maxPozitivColoanaEcuatieCuParanteze = -INFINIT;
	determinareNumarLiniiColoanePlansaEcuatie(_bExpresie, _maxPozitivLinieEcuatieCuParanteze, _maxPozitivColoanaEcuatieCuParanteze);
	_numarLiniiPlansaEcuatieCuParanteze = _maxPozitivLinieEcuatieCuParanteze + 1;
	_numarColoanePlansaEcuatieCuParanteze = ceil(_maxPozitivColoanaEcuatieCuParanteze) + 1;


	_lungimeCelulaExpresieCuParanteze = (float)lungimePlansa / _numarColoanePlansaEcuatieCuParanteze;
	_inaltimeCelulaExpresieCuParanteze = (float)inaltimePlansa / _numarLiniiPlansaEcuatieCuParanteze;
}

#endif // CONNECT_GUI_TO_ALGORITHM_H_INCLUDED
