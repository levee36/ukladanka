#include "cguimsgpopup.h"

CGUIMsgPopup::CGUIMsgPopup(std::string przycisk)
    : CGUIMsg(std::string("Popup")),
      przycisk(przycisk)
{
}

std::string CGUIMsgPopup::getPrzycisk()
{
    return przycisk;
}


