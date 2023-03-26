#include <bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include "graphics.h"

#include "All Headers.h"

using namespace std;

int main()
{
    setariProiect();
    deseneazaFereastraMeniuPrincipal();

    while (ruleaza)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            verificaButoane();
        }
        setcurrentwindow(MeniuGraficaFereastra);
    }

    closegraph();
    return 0;
}


/**

 ***** Exemple de ecuatii *****

1)     1/2+5/(1/3+1/(4+(1+6)/5))
2)     (1+2)/3+(6+7)/(1/2+5+1/(2+3))
3)     (1+2)/2+(1+2)/n
4)     (234/B+abc)/23+(1000+2)/n
5)     123/2+abc/(21/3400+1/(A+(1+645)/xyz))
6)     sin(345+a)/cos(235-b)+sin(a*b)
7)     ctg(123*a)/(21+xy+555)
8)     123+sin(24.55+abc)/cos(tg(90.99))
9)     sin(9.5+1)/(1+cos(8+ac))
*/
