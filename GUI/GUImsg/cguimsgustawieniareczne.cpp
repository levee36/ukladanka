#include "cguimsgustawieniareczne.h"

CGUIMsgUstawianieReczne::CGUIMsgUstawianieReczne(bool wlaczone)
    : CGUIMsg(std::string("UstawianieReczne"))
{
    this->wlaczone=wlaczone;
}

bool CGUIMsgUstawianieReczne::getWlaczone()
{
    return wlaczone;
}
