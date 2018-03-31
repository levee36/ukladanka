#ifndef CGUIMSGWCISNIETEPOLE_H
#define CGUIMSGWCISNIETEPOLE_H

#include "cguimsg.h"

class CGUIMsgWcisnietePole : public CGUIMsg {

public:
    CGUIMsgWcisnietePole(int pole);
    int getPole();
protected:
    int pole;
};

#endif // CGUIMSGWCISNIETEPOLE_H
