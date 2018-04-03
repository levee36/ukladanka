#include "cheurystykaliczbaroznic.h"

CHeurystykaLiczbaRoznic::CHeurystykaLiczbaRoznic() :
    CHeurystyka("heurystyka Liczba Różnic")
{

}

double CHeurystykaLiczbaRoznic::policzOcene(CArray2D<int> *stan)
{
    int liczba_roznic = 0.0;
    for(int t=0;t<stan->getN()*stan->getM();t++)
        if (stan->dostepLiniowy(t)>0 && t!=stan->dostepLiniowy(t)) liczba_roznic++;
    return liczba_roznic;
}
