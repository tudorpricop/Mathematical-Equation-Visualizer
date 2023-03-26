#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "Tree Display.h"
#include "Equation Display.h"
#include "Connect GUI to Algorithm.h"

/// COD MENIU INCEPUT


bool ruleaza=true;
int  MeniuGraficaFereastra;
int pozitieCaracter=0;
const int background_color = COLOR(24,24,36); ///181824
const int button_color = COLOR(226,6,76); ///E2064C
const int text_color = COLOR(255,255,255);

enum TipFereastra
{
    MainMenu,
    Setari,
    Ajutor,
    Start,
    Afisari
};

TipFereastra fereastraCurenta;

void square(int x, int y, int latura)
{
    rectangle(x - latura/2, y - latura/2, x+latura/2, y + latura/2);
}

void clearScreen()
{
    cleardevice();
    setfillstyle(SOLID_FILL,background_color);
    bar(0,0,getmaxx(),getmaxy());
    setbkcolor(background_color);
}

bool peButon(int x1, int y1, int x2, int y2)
{
    int x=mousex();
    int y=mousey();

    if (x1>x2)
        swap (x1,x2);

    if (y1>y2)
        swap (y1,y2);


    if (x>x1 && x<x2 && y>y1 && y<y2)
        return true;

    return false;
}

void underlineText(int x, int y, char* text)
{
    // Obtine latimea textului in pixeli
    int text_width = textwidth(text);

    // Obtine inaltimea textului in pixeli
    int text_height = textheight(text);

    // Desenam textul in mijlocul dreptunghiului
    line(x-text_width/2, y+text_height+2, x+text_width/2, y+text_height+2);
}

void drawCenteredText(int left, int top, int right, int bottom, char* text)
{
    // Obtine latimea textului in pixeli
    int text_width = textwidth(text);

    // Calculam coordonata x pentru centrul dreptunghiului
    int x = (right - left - text_width) / 2 + left;

    // Calculam coordonata y pentru centrul dreptunghiului
    int y = (bottom - top) / 2 + top;

    // Desenam textul in mijlocul dreptunghiului
    setcolor(text_color);
    outtextxy(x, y, text);
}

void afisareTextAjutor()
{
    outtextxy(0,120, " !!! Reguli pentru introducerea expresiei:");
    outtextxy(0,160, "    --Toate caracterele vor fi litere mici, fara diacritice, ");
    outtextxy(0,180, " legate (fara spatii)");


    outtextxy(0,220, "   --Functiile si Operatiile suportate sunt inmultire, impartire,");
    outtextxy(0,240, " adunare, scadere, numere reale, sinus, cosinus, tangenta,");
    outtextxy(0,260, " cotangenta.");

    outtextxy(0,300, "   -- Exemple de expresii :  32+(0.5)*sin(x+2)/4/2+32");


    outtextxy(0,340, "   In interfeata Start veti vedea un camp destinat locului in care sa ");
    outtextxy(0,360, " introduceti ecuatia matematica.");

    setcolor(LIGHTRED);

    outtextxy(0,400, "   !!!!  Dupa ce ati introdus expresia, apasati tasta enter iar ");
    outtextxy(0,420, " ulterior butonul Confirm.");

    setcolor(WHITE);

    outtextxy(0,460, "   Dupa ce ati efectuat pasii de mai sus, puteti selecta sa vizualizati");
    outtextxy(0,480, " arborele asociat expresiei ( cu sau fara paranteze) sau afisarea");
    outtextxy(0,500, " expresiei matematice.");

}


/// *************************************************************************************

void setari()
{
    /// Buton setari
    setcolor(button_color);
    rectangle(50, getmaxy() - 50, 150, getmaxy() - 150);
    drawCenteredText(50, getmaxy() - 50, 150, getmaxy() - 150, "Settings");
}

bool peSetari()
{
    if (peButon(50, getmaxy() - 50, 150, getmaxy() - 150))
        return true;
    return false;
}

void quit ()
{
    /// Buton Quit
    setcolor(button_color);
    rectangle(getmaxx() - 50, getmaxy() - 50, getmaxx() - 150, getmaxy() - 150);
    drawCenteredText(getmaxx() - 50, getmaxy() - 50, getmaxx() - 150, getmaxy() - 150, "Quit");
}

bool peQuit()
{
    if (peButon(getmaxx() - 50, getmaxy() - 50, getmaxx() - 150, getmaxy() - 150))
        return true;
    return false;
}

void ajutor ()
{
    /// Buton Ajutor
    setcolor(button_color);
    int mijlocX = getmaxx() /2;
    rectangle(mijlocX-50, getmaxy() - 50, mijlocX + 50, getmaxy() - 150);
    drawCenteredText(mijlocX-50, getmaxy() - 50, mijlocX + 50, getmaxy() - 150, "Ajutor");
}

bool peAjutor()
{
    int mijlocX = getmaxx() /2;
    if (peButon(mijlocX-50, getmaxy() - 50, mijlocX + 50, getmaxy() - 150))
        return true;
    return false;
}

void start ()
{
    /// Buton Start
    setcolor(button_color);
    int mijlocX = getmaxx() /2;
    int mijlocY = getmaxy() /2;
    rectangle(mijlocX-50, mijlocY-50, mijlocX + 50, mijlocY+50);
    drawCenteredText(mijlocX-50, mijlocY-50, mijlocX + 50, mijlocY+50, "Start");
}

bool peStart()
{
    int mijlocX = getmaxx() /2;
    int mijlocY = getmaxy() /2;
    if (peButon(mijlocX-50, mijlocY-50, mijlocX + 50, mijlocY+50))
        return true;
    return false;
}

void titlu ()
{
    /// titlu proiect
    int text_width = textwidth("Editor Expresii Matematice");
    int x = (getmaxx() - text_width) / 2;
    outtextxy(x, 50, "Editor Expresii Matematice");
}

/// *************************************************************************************

void InapoiLaMeniu ()
{
    /// Inapoi La Meniu
    setcolor(button_color);
    rectangle(20,20,240,60);
    drawCenteredText(20,20,240,60, "<-- Inapoi La Meniu");
}

bool peInapoiLaMeniu()
{
    if (peButon(20,20,240,60))
        return true;
    return false;
}

void bifeazaSauDebifeazaEcuatie(int indexButon)
{
    for (int i =0; i<6; i++)
    {
        if (i==indexButon)
            setfillstyle(SOLID_FILL,Culori[i].culoare);
        else
            setfillstyle(SOLID_FILL,background_color);
        /// creez un patrat negru
        bar(490,230+i*40,510,250+i*40);
        /// creez conturu colorat
        setcolor(Culori[i].culoare);
        square(500,240+i*40,20);
    }
    setcolor(WHITE);
}

void butoaneCuloriEcuatie()
{
    drawCenteredText(600,180,600,180, "Culoare Ecuatie");
    underlineText(600,180,"Culoare Ecuatie");

    bifeazaSauDebifeazaEcuatie(index_culoareEcuatie);
    for (int i =0; i<6; i++)
    {
        setcolor(Culori[i].culoare);
        outtextxy(540,240+i*40-5,Culori[i].nume);
    }
    setcolor(WHITE);
}

/// verifica daca mouse ul e pe butoane si face actiunea butonului respectiv
void procesezButonCuloareEcuatie()
{
    for (int i =0; i<6; i++)
    {
        if(peButon(490,230+i*40,510,250+i*40))
        {
            /// !!! functia care mi seteaza culoarea ecuatiei: culoareaEcuatie=Culori[i].culoare;  ///setcolor (Culori[index_culoareEcuatie].culoare)
            index_culoareEcuatie =  i;
            cout << "Culoarea aleasa ecuatiei este culoarea: " << Culori[i].nume << endl;
            bifeazaSauDebifeazaEcuatie(i);
        }
    }
}


///===================================================================================

void bifeazaSauDebifeazaArbore(int indexButon)
{
    for (int i =0; i<6; i++)
    {
        if (i==indexButon)
            setfillstyle(SOLID_FILL,Culori[i].culoare);
        else
            setfillstyle(SOLID_FILL,background_color);
        /// creez un patrat negru
        bar(90,230+i*40,110,250+i*40);
        /// creez conturu colorat
        setcolor(Culori[i].culoare);
        square(100,240+i*40,20);
    }
    setcolor(WHITE);
}

void butoaneCuloriArbore()
{
    drawCenteredText(200,180,200,180, "Culoare Arbore");
    underlineText(200,180,"Culoare Arbore");

    bifeazaSauDebifeazaArbore(index_culoareArbore);
    for (int i =0; i<6; i++)
    {
        setcolor(Culori[i].culoare);
        outtextxy(140,240+i*40-5,Culori[i].nume);
    }
    setcolor(WHITE);
}

/// verifica daca mouse ul e pe butoane si face actionea butonului respectiv
void procesezButonCuloareArbore()
{
    for (int i =0; i<6; i++)
    {
        if(peButon(90,230+i*40,110,250+i*40))
        {
            /// !!! functia care mi seteaza culoarea arborelui: culoareaArborelui=Culori[i].culoare;
            index_culoareArbore =  i;
            cout << "Culoarea aleasa este culoarea: " << Culori[i].nume << endl;
            bifeazaSauDebifeazaArbore(i);
        }
    }
}

///===================================================================================

void deseneazaFereastraAjutor()
{
    fereastraCurenta = Ajutor;
    InapoiLaMeniu ();
    afisareTextAjutor();
}

void deseneazaFereastraSetari ()
{
    fereastraCurenta = Setari;
    butoaneCuloriArbore();
    butoaneCuloriEcuatie();
    InapoiLaMeniu ();
}

void ButonConfirm ()
{
    /// Buton Confirm
    setcolor(button_color);
    int mijlocX = getmaxx() /2;
    rectangle(mijlocX-50, 280, mijlocX + 50, 380);
    drawCenteredText(mijlocX-50, 280, mijlocX + 50, 380, "Confirm");
}

bool peButonConfirm()
{
    int mijlocX = getmaxx() /2;
    if (peButon(mijlocX-50, 280, mijlocX + 50, 380))
        return true;
    return false;
}

void CasutaText()
{
    int text_width = textwidth("Introduceti expresia matematica mai jos:");
    int x = (getmaxx() - text_width) / 2;
    outtextxy(x, 100, "Introduceti expresia matematica mai jos:");

    setcolor(button_color);
    rectangle(80,140,720,200);
}


void deseneazaFereastraStart ()
{
    fereastraCurenta = Start;
    InapoiLaMeniu ();
    CasutaText();
    ButonConfirm();
    int text_width=0;
    int nrCaractere=0;

    char c[2];
    c[1]='\0';
    while (c[0]!=13)
    {
        c[0]=getch();
        if (c[0]==13)
            break;
        if (c[0]==8 && nrCaractere>0)
        {
            pozitieCaracter=pozitieCaracter-text_width-2;
            infixString[strlen(infixString)-1]='\0';
            outtextxy(90+pozitieCaracter, 170, " ");
            nrCaractere--;
        }
        else if (c[0]!=8)
        {
            nrCaractere++;
            strncat(infixString,c,1);
            outtextxy(90+pozitieCaracter, 170, c);
            text_width=textwidth(c);
            pozitieCaracter=pozitieCaracter+text_width+2;
        }
    }
}


/// *************************************************************************************

void deseneazaFereastraMeniuPrincipal ()
{
    pozitieCaracter=0;
    memset(infixString, 0, 50);
    fereastraCurenta = MainMenu;
    titlu();
    start();
    ajutor();
    quit();
    setari();
}

void butonArboreFaraParanteze()
{
    /// Buton Arbore Fara Paranteze
    setcolor(button_color);
    rectangle(80,140,720,200);
    drawCenteredText(80,140,720,200, "Afiseaza arborele expresiei fara paranteze");
}

bool peButonArboreFaraParanteze()
{
    if (peButon(80,140,720,200))
        return true;
    return false;
}

void butonArboreCuParanteze()
{
    /// Buton Arbore Cu Paranteze
    setcolor(button_color);
    rectangle(80,250,720,310);
    drawCenteredText(80,250,720,310, "Afiseaza arborele expresiei cu paranteze");
}

bool peButonArboreCuParanteze()
{
    if (peButon(80,250,720,310))
        return true;
    return false;
}

void butonExpresie()
{
    /// Buton Expresie
    setcolor(button_color);
    rectangle(80,360,720,420);
    drawCenteredText(80,360,720,420, "Afiseaza expresia pe ecran");
}

bool peButonExpresie()
{
    if (peButon(80,360,720,420))
        return true;
    return false;
}

void deseneazaFereastraAfisari ()
{
    fereastraCurenta = Afisari;
    InapoiLaMeniu ();
    butonArboreFaraParanteze();
    butonArboreCuParanteze();
    butonExpresie();
}

void setariProiect()
{
    MeniuGraficaFereastra = initwindow(800, 600, "Meniu Principal");
    clearScreen();
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 100);
}

void cod_pt_arb_fara_paranteze ()
{
    int windowArbE;
    int lungimePlansa = 900, inaltimePlansa = 600; // Comune pentru iteratii noi si vechi
    windowArbE = initwindow(lungimePlansa, inaltimePlansa, "windowArbE");

    setcolor (Culori[index_culoareArbore].culoare);
    setcurrentwindow(windowArbE);
    afisareArbore(_a, NULL, _lungimeCelula, _inaltimeCelula, _razaCerc);
}

void cod_pt_arb_cu_paranteze ()
{
    int windowArbPE;
    int lungimePlansa = 900, inaltimePlansa = 600; // Comune pentru iteratii noi si vechi
    windowArbPE = initwindow(lungimePlansa, inaltimePlansa, "windowArbEP");

    setcolor (Culori[index_culoareArbore].culoare);
    setcurrentwindow(windowArbPE);
    afisareArbore(_b, NULL, _lungimeCelulaArboreCuParanteze, _inaltimeCelulaArboreCuParanteze, _razaCercArboreCuParanteze);
}

void cod_pt_afisare_expresie ()
{
    int  windowEcPE;
    int lungimePlansa = 900, inaltimePlansa = 600; // Comune pentru iteratii noi si vechi
    windowEcPE = initwindow(lungimePlansa, inaltimePlansa, "windowEcPE");

    setcolor (Culori[index_culoareEcuatie].culoare);
    setcurrentwindow(windowEcPE);
	afisareExpresie(_bExpresie, _lungimeCelulaExpresieCuParanteze, _inaltimeCelulaExpresieCuParanteze);
}

void verificaButoane()
{
    switch (fereastraCurenta)
    {
    case MainMenu:
        if (peStart())
        {
            cout << "Ai dat click pe Start" << endl;
            clearScreen();
            deseneazaFereastraStart();
        }

        if (peSetari())
        {
            cout << "Ai dat click pe Setari" << endl;
            clearScreen();
            deseneazaFereastraSetari();
        }

        if (peAjutor())
        {
            clearScreen();
            deseneazaFereastraAjutor();
            cout << "Ai dat click pe Ajutor" << endl;
        }

        if (peQuit())
        {
            cout << "Ai dat click pe Quit" << endl;
            clearScreen();
            ruleaza=0;
        }
        break;

    case Setari:
        if (peInapoiLaMeniu())
        {
            clearScreen();
            deseneazaFereastraMeniuPrincipal();
        }
        procesezButonCuloareArbore();
        procesezButonCuloareEcuatie();
        break;

    case Ajutor:
        if (peInapoiLaMeniu())
        {
            clearScreen();
            deseneazaFereastraMeniuPrincipal();
        }
        break;

    case Start:
        if (peInapoiLaMeniu())
        {
            clearScreen();
            deseneazaFereastraMeniuPrincipal();
        }
        if (peButonConfirm())
        {
            cout << infix << endl;
            clearScreen();
            deseneazaFereastraAfisari();
            main2();
        }
        break;

    case Afisari:
        if (peInapoiLaMeniu())
        {
            clearScreen();
            deseneazaFereastraMeniuPrincipal();
        }
        if (peButonArboreFaraParanteze())
        {
            cod_pt_arb_fara_paranteze();
        }
        if (peButonArboreCuParanteze())
        {
            cod_pt_arb_cu_paranteze();
        }
        if (peButonExpresie())
        {
            cod_pt_afisare_expresie();
        }
        break;

    }
}

/// COD MENIU TERMINAT

#endif // GUI_H_INCLUDED
