#include "cguimsg.h"

CGUIMsg::CGUIMsg() {}

CGUIMsg::CGUIMsg(std::string opis)
{
    this->opis = opis;
}

std::string CGUIMsg::getOpis()
{
    return opis;
}
