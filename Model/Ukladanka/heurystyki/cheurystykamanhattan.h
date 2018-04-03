#ifndef CHEURYSTYKAMANHATTAN_H
#define CHEURYSTYKAMANHATTAN_H

#include "cheurystyka.h"

class CHeurystykaManhattan : public CHeurystyka
{
public:
    CHeurystykaManhattan();
    double policzOcene(CArray2D<int> *stan);
protected:
    double odleglosc(size_t t1, size_t t2, size_t N);
    double odleglosc(size_t n1, size_t m1, size_t n2, size_t m2);
};

#endif // CHEURYSTYKAMANHATTAN_H
