#ifndef OPERAND_FUNCTIONS_H_INCLUDED
#define OPERAND_FUNCTIONS_H_INCLUDED

const entitate _plus = "+";
const entitate _minus = "-";
const entitate _asterisc = "*";
const entitate _slash = "/";
const entitate _control = "^";
const entitate _parantezaRotundaDeschisa = "(";
const entitate _parantezaRotundaInchisa = ")";

const entitate _sin = "sin";
const entitate _cos = "cos";
const entitate _tg = "tg";
const entitate _ctg = "ctg";

bool esteOperator(char c)
{
	return (!isalpha(c) && !isdigit(c));
}

bool esteOperatorPlus(entitate c)
{
	return strcmp(c, _plus) == 0;
}

bool esteOperatorMinus(entitate c)
{
	return strcmp(c, _minus) == 0;
}

bool esteOperatorAsterisc(entitate c)
{
	return strcmp(c, _asterisc) == 0;
}

bool esteOperatorSlash(entitate c)
{
	return strcmp(c, _slash) == 0;
}

bool esteOperatorControl(entitate c)
{
	return strcmp(c, _control) == 0;
}

bool esteOperator(entitate c)
{
	return esteOperatorPlus(c) || esteOperatorMinus(c) || esteOperatorAsterisc(c) || esteOperatorSlash(c) || esteOperatorControl(c);
}

bool esteFunctieSin(entitate c)
{
	return strcmp(c, _sin) == 0;
}

bool esteFunctieCos(entitate c)
{
	return strcmp(c, _cos) == 0;
}

bool esteFunctieTg(entitate c)
{
	return strcmp(c, _tg) == 0;
}

bool esteFunctieCtg(entitate c)
{
	return strcmp(c, _ctg) == 0;
}

bool esteFunctie(entitate c)
{
	return esteFunctieSin(c) || esteFunctieCos(c) || esteFunctieTg(c) || esteFunctieCtg(c);
}

bool esteParantezaRotundaDeschisa(entitate c)
{
	return strcmp(c, _parantezaRotundaDeschisa) == 0;
}

bool esteParantezaRotundaInchisa(entitate c)
{
	return strcmp(c, _parantezaRotundaInchisa) == 0;
}

bool esteParanteza(entitate c)
{
	return esteParantezaRotundaDeschisa(c) || esteParantezaRotundaInchisa(c);
}

bool esteOperand(entitate c)
{
	return !esteOperator(c) && !esteParanteza(c) && !esteFunctie(c);
}

#endif // OPERAND_FUNCTIONS_H_INCLUDED
