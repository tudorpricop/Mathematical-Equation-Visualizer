#ifndef INFIX_PREFIX_CONVERSION_H_INCLUDED
#define INFIX_PREFIX_CONVERSION_H_INCLUDED

int prioritate(char c)
{
	if (c == '-' || c == '+')
		return 1;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '^')
		return 3;
	return 0;
}

int prioritate(entitate c)
{
	if (esteOperatorPlus(c) || esteOperatorMinus(c))
		return 1;
	else if (esteOperatorAsterisc(c) || esteOperatorSlash(c))
		return 2;
	else if (esteOperatorControl(c))
		return 3;
	return 0;
}


string infixCatrePostfix(string infix)
{
	infix = '(' + infix + ')';
	int l = infix.size();
	stiva s;
	intializareStiva(s);
	string output;

	for (int i = 0; i < l; i++)
	{
		// Daca caracterul curent este un operand, atunci il vom adauga la output
		if (isalpha(infix[i]) || isdigit(infix[i]))
			output += infix[i];
		// Daca caracterul curent este '(', atunci il vom adauga la stiva
		else if (infix[i] == '(')
			push(s, '(');
		// Daca caracterul curent este ')', atunci vom sterge din stiva pana cand dam de '('
		else if (infix[i] == ')')
		{
			while (top(s) != '(')
			{
				output += top(s);
				pop(s);
			}
			// Eliminam '(' din stiva
			pop(s);
		}
		else
		{
			if (esteOperator(top(s)))
			{
				if (infix[i] == '^')
				{
					while (prioritate(infix[i]) <= prioritate(top(s)))
					{
						output += top(s);
						pop(s);
					}
				}
				else
				{
					while (prioritate(infix[i]) < prioritate(top(s)))
					{
						output += top(s);
						pop(s);
					}
				}
				push(s, infix[i]);
			}
		}
	}
	while (s.varf != NULL)
	{
		output += top(s);
		pop(s);
	}

	return output;
}

void adaugareEntitateLaInceput(matriceDeCaractere& T, const entitate entitate)
{
	int i;
	for (i = T.dimensiuneTablouEntitati - 1; i >= 0; i--)
		strcpy(T.tablouEntitati[i + 1], T.tablouEntitati[i]);
	strcpy(T.tablouEntitati[0], entitate);
	T.dimensiuneTablouEntitati++;
}

void adaugareEntitateLaSfarsit(matriceDeCaractere& T, const entitate entitate)
{
	T.dimensiuneTablouEntitati++;
	strcpy(T.tablouEntitati[T.dimensiuneTablouEntitati - 1], entitate);
}


void infixCatrePostfix(matriceDeCaractere infix, matriceDeCaractere& postfix)
{
	matriceDeCaractere infixCopie;
	infixCopie.dimensiuneTablouEntitati = infix.dimensiuneTablouEntitati;
	for (int i = 0; i < infix.dimensiuneTablouEntitati; i++)
		strcpy(infixCopie.tablouEntitati[i], infix.tablouEntitati[i]);
	adaugareEntitateLaInceput(infixCopie, _parantezaRotundaDeschisa);
	adaugareEntitateLaSfarsit(infixCopie, _parantezaRotundaInchisa);
	int l = infixCopie.dimensiuneTablouEntitati;
	stivaE s;
	intializareStiva(s);
	postfix.dimensiuneTablouEntitati = 0;

	for (int i = 0; i < l; i++)
	{
		if (!esteOperator(infixCopie.tablouEntitati[i]) && !esteParanteza(infixCopie.tablouEntitati[i]))
		{
			adaugareEntitateLaSfarsit(postfix, infixCopie.tablouEntitati[i]);
		}
		else if (esteParantezaRotundaDeschisa(infixCopie.tablouEntitati[i]))
			push(s, _parantezaRotundaDeschisa);

		else if (esteParantezaRotundaInchisa(infixCopie.tablouEntitati[i]))
		{
			while (!esteParantezaRotundaDeschisa(*top(s)))
			{
				adaugareEntitateLaSfarsit(postfix, *top(s));
				pop(s);
			}
			pop(s);
		}

		else
		{
			if (esteOperator(*top(s)) || esteParanteza(*top(s)))
			{
				if (esteOperatorControl(infixCopie.tablouEntitati[i]))
				{
					while (prioritate(infixCopie.tablouEntitati[i]) <= prioritate(*top(s)))
					{
						adaugareEntitateLaSfarsit(postfix, *top(s));
						pop(s);
					}
				}
				else
				{
					while (prioritate(infixCopie.tablouEntitati[i]) < prioritate(*top(s)))
					{
						adaugareEntitateLaSfarsit(postfix, *top(s));
						pop(s);
					}
				}
				push(s, infixCopie.tablouEntitati[i]);
			}
		}
	}
	while (s.varf != NULL)
	{
		adaugareEntitateLaSfarsit(postfix, *top(s));
		pop(s);
	}
}

string infixCatrePrefix(string infix)
{
	/**
	 Pasii determinarii notatiei prefixate
	 1. Inversam String
	 2. Inlocuim '(' cu ')' si vice versa
	 3. Determinam Postfix
	 4. Inversam postfix
	*/
	int l = infix.size();
	/// Inversam infix
	reverse(infix.begin(), infix.end());
	/// Inlocuim '(' cu ')' si vice versa
	for (int i = 0; i < l; i++)
	{
		if (infix[i] == '(')
			infix[i] = ')';
		else if (infix[i] == ')')
			infix[i] = '(';
	}
	/// Determinam Postfix
	string prefix = infixCatrePostfix(infix);
	/// Inversam postfix
	reverse(prefix.begin(), prefix.end());
	return prefix;
}

void infixCatrePrefix(matriceDeCaractere infix, matriceDeCaractere& prefix)
{
	/**
	 Pasii determinarii notatiei prefixate
	 1. Inversam infix
	 2. Inlocuim "(" cu ")" si vice versa
	 3. Determinam postfix
	 4. Inversam postfix
	*/

	matriceDeCaractere infixCopie; // Fiind matrice de caractere, modificarile asupra infix-ului raman dupa apelul functiei
	infixCopie.dimensiuneTablouEntitati = infix.dimensiuneTablouEntitati;
	for (int i = 0; i < infix.dimensiuneTablouEntitati; i++)
		strcpy(infixCopie.tablouEntitati[i], infix.tablouEntitati[i]);

	int l = infixCopie.dimensiuneTablouEntitati;
	/// Inversam infixCopie
	int st = 0, dr = l - 1;
	while (st < dr)
	{
		entitate aux;
		strcpy(aux, infixCopie.tablouEntitati[st]);
		strcpy(infixCopie.tablouEntitati[st], infixCopie.tablouEntitati[dr]);
		strcpy(infixCopie.tablouEntitati[dr], aux);
		st++;
		dr--;
	}
	/// Inlocuim "(" cu ")" si vice versa
	for (int i = 0; i < l; i++)
	{
		if (esteParantezaRotundaDeschisa(infixCopie.tablouEntitati[i]))
			strcpy(infixCopie.tablouEntitati[i], _parantezaRotundaInchisa);
		else if (esteParantezaRotundaInchisa(infixCopie.tablouEntitati[i]))
			strcpy(infixCopie.tablouEntitati[i], _parantezaRotundaDeschisa);
	}
	/// Determinam postfix
	prefix.dimensiuneTablouEntitati = 0;
	infixCatrePostfix(infixCopie, prefix);
	l = prefix.dimensiuneTablouEntitati;
	/// Inversam postfix
	st = 0, dr = l - 1;
	while (st < dr)
	{
		entitate aux;
		strcpy(aux, prefix.tablouEntitati[st]);
		strcpy(prefix.tablouEntitati[st], prefix.tablouEntitati[dr]);
		strcpy(prefix.tablouEntitati[dr], aux);
		st++;
		dr--;
	}
}

#endif // INFIX_PREFIX_CONVERSION_H_INCLUDED
