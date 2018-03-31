#include "cguimsgwcisnietepole.h"

CGUIMsgWcisnietePole::CGUIMsgWcisnietePole(int pole)
    : CGUIMsg(std::string("WcisnietePole"))
{
    this->pole = pole;
}

int CGUIMsgWcisnietePole::getPole()
{
    return pole;
}

