#ifndef CHEURYSTYKA_H
#define CHEURYSTYKA_H

#include <string>
#include "Model/Ukladanka/carray2d.h"

class CHeurystyka
{
public:
    CHeurystyka(std::string nazwa);
    virtual double policzOcene(CArray2D<int> *stan) = 0;
    std::string getNazwa();
protected:
    std::string nazwa;
};

#endif // CHEURYSTYKA_H

