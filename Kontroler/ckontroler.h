#ifndef CKONTROLER_H
#define CKONTROLER_H

#include "Kontroler/ikontroler.h"
#include "GUI/igui.h"
#include "GUI/GUImsg/cguimsg.h"
#include "Model/Ukladanka/iukladanka.h"

class CKontroler : public IKontroler
{
public:
    CKontroler(IGUI *gui);
    ~CKontroler();
    void wyslijWiadomosc(CGUIMsg *wiadomosc);

private:
    IGUI *gui;
    IUkladanka *ukladanka;

    void scZamknij();
    void scKonfiguruj(CGUIMsg *wiadomosc);
    void scTasuj();
    void scRozwiazuj();
    void scResetuj();
    void scReczneUstawianie(CGUIMsg *wiadomosc);
    void scWykonajRuch(CGUIMsg *wiadomosc);
    void scObsluzStan();
};

#endif // CKONTROLER_H
