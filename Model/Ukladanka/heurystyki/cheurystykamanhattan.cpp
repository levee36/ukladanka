#include "cheurystykamanhattan.h"

CHeurystykaManhattan::CHeurystykaManhattan() :
    CHeurystyka("heurystyka Manhattan")
{

}

double CHeurystykaManhattan::policzOcene(CArray2D<int> *stan)
{
    double suma_odleglosci = 0.0;
    for(int t=0;t<stan->getN()*stan->getM();t++)
        if (stan->dostepLiniowy(t)>0 && t!=stan->dostepLiniowy(t)-1)
            suma_odleglosci+=odleglosc(t,stan->dostepLiniowy(t)-1,stan->getN());
    return suma_odleglosci;
}

double CHeurystykaManhattan::odleglosc(size_t t1, size_t t2, size_t N)
{
    return odleglosc(t1%N, t1/N, t2%N, t2/N);
}

double CHeurystykaManhattan::odleglosc(size_t n1, size_t m1, size_t n2, size_t m2)
{
    int n = (n1 < n2) ? n2-n1 : n1-n2;
    int m = (m1 < m2) ? m2-m1 : m1-m2;
    return n+m;
}
