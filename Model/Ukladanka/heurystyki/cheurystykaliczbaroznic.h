#ifndef CHEURYSTYKALICZBAROZNIC_H
#define CHEURYSTYKALICZBAROZNIC_H

#include "cheurystyka.h"

class CHeurystykaLiczbaRoznic : public CHeurystyka
{
public:
    CHeurystykaLiczbaRoznic();
    double policzOcene(CArray2D<int> *stan);
};

#endif // CHEURYSTYKALICZBAROZNIC_H
