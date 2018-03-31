#ifndef CGUIMSGUSTAWIANIERECZNE_H
#define CGUIMSGUSTAWIANIERECZNE_H

#include "cguimsg.h"

class CGUIMsgUstawianieReczne : public CGUIMsg {

public:
    CGUIMsgUstawianieReczne(bool wlaczone);
    bool getWlaczone();
protected:
    bool wlaczone;
};

#endif // CGUIMSGUSTAWIANIERECZNE_H
