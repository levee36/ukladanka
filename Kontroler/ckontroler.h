#ifndef CKONTROLER_H
#define CKONTROLER_H

#include "Kontroler/ikontroler.h"
#include "GUI/igui.h"
#include "GUI/GUImsg/cguimsg.h"


class CKontroler : public IKontroler
{
public:
    CKontroler();
    ~CKontroler();
    setGUI(IGUI *gui);
    void wyslijWiadomosc(CGUIMsg *wiadomosc);

private:
    IGUI *gui;
};

#endif // CKONTROLER_H
