#ifndef IKONTROLER_H
#define IKONTROLER_H

#include "GUI\GUImsg\cguimsg.h"

class IKontroler
{

public:
    virtual void wyslijWiadomosc(CGUIMsg *wiadomosc) = 0;
};

#endif // IKONTROLER_H
