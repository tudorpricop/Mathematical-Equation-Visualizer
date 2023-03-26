#ifndef STACK_OPERATIONS_H_INCLUDED
#define STACK_OPERATIONS_H_INCLUDED

void intializareStiva(stiva& s)
{
	s.varf = NULL;
	s.nrElem = 0;
}
void intializareStiva(stivaE& s)
{
	s.varf = NULL;
	s.nrElem = 0;
}
void push(stiva& s, int x)
{
	nod* nNou = new nod;
	nNou->info = x;
	nNou->urm = s.varf;
	s.varf = nNou;
	s.nrElem++;
}
void push(stivaE& s, const entitate x)
{
	nodE* nNou = new nodE;
	strcpy(nNou->info, x);
	nNou->urm = s.varf;
	s.varf = nNou;
	s.nrElem++;
}
void pop(stiva& s)
{
	nod* aux = s.varf;
	s.varf = s.varf->urm;
	delete aux;
	s.nrElem--;
}
void pop(stivaE& s)
{
	nodE* aux = s.varf;
	s.varf = s.varf->urm;
	delete aux;
	s.nrElem--;
}
int top(stiva s)
{
	return s.varf->info;
}
entitate* top(stivaE s)
{
	return &(s.varf->info);
}

#endif // STACK_OPERATIONS_H_INCLUDED
