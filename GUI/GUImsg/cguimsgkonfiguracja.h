#ifndef CGUIMSGKONFIGURACJA_H
#define CGUIMSGKONFIGURACJA_H

#include "cguimsg.h"

class CGUIMsgKonfiguracja : public CGUIMsg {

public:
    CGUIMsgKonfiguracja(int N, int M);
    int getN();
    int getM();
protected:
    int N;
    int M;
};

#endif // CGUIMSGKONFIGURACJA_H
