
#include "Kontroler/ckontroler.h"
#include <QString>
#include <string>
#include "GUI/GUImsg/cguimsgwcisnietepole.h"
#include "GUI/GUImsg/cguimsgwyjscie.h"
#include "GUI/GUImsg/cguimsgzadaniekonfiguracji.h"
#include "GUI/GUImsg/cguimsgkonfiguracja.h"
#include "GUI/GUImsg/cguimsginstrukcja.h"
#include "GUI/GUImsg/cguimsgoprogramie.h"

#include <iostream>

CKontroler::CKontroler()
{

}

CKontroler::~CKontroler()
{

}

CKontroler::setGUI(IGUI *gui)
{
    this->gui=gui;
}

void CKontroler::wyslijWiadomosc(CGUIMsg *wiadomosc)
{
    std::cout << wiadomosc->getOpis() <<std::endl;

    if (dynamic_cast<CGUIMsgWcisnietePole*>(wiadomosc)!=0) {
        CGUIMsgWcisnietePole *wiadomoscWcisnietePole=dynamic_cast<CGUIMsgWcisnietePole*>(wiadomosc);
        std::cout << wiadomoscWcisnietePole->getPole() << std::endl;
        std::array<int,2> para = {wiadomoscWcisnietePole->getPole(),(wiadomoscWcisnietePole->getPole()-1)%36};
        std::vector<std::array<int,2>> v;
        v.push_back(para);
        gui->zamienPola(v);
    }
    else if (dynamic_cast<CGUIMsgZadanieKonfiguracji*>(wiadomosc)!=0) {
        std::map<std::string, std::string> parametry;
        parametry.insert(std::pair<std::string,std::string>("N","3"));
        parametry.insert(std::pair<std::string,std::string>("N_min","2"));
        parametry.insert(std::pair<std::string,std::string>("N_max","8"));
        parametry.insert(std::pair<std::string,std::string>("M","3"));
        parametry.insert(std::pair<std::string,std::string>("M_min","2"));
        parametry.insert(std::pair<std::string,std::string>("M_max","8"));
        gui->wyswietlKonfiguracje(parametry);
    }
    if (dynamic_cast<CGUIMsgKonfiguracja*>(wiadomosc)!=0) {
        CGUIMsgKonfiguracja *wiadomoscKonfiguracja=dynamic_cast<CGUIMsgKonfiguracja*>(wiadomosc);
        std::cout << "N: " << wiadomoscKonfiguracja->getN() << " M: " << wiadomoscKonfiguracja->getM() << std::endl;
        std::vector<int> ciag;
        for (int i = 0;i<wiadomoscKonfiguracja->getN()*wiadomoscKonfiguracja->getM();i++)
            ciag.push_back((i+1)%(wiadomoscKonfiguracja->getN()*wiadomoscKonfiguracja->getM()));
        gui->rysujPlansze(ciag,wiadomoscKonfiguracja->getN(),wiadomoscKonfiguracja->getM());
    }
    else if (dynamic_cast<CGUIMsgInstrukcja*>(wiadomosc)!=0) {
        std::map<std::string,std::string> parametry;
        parametry.insert(std::pair<std::string,std::string>("instrukcje","Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."));
        gui->wyswietlInstrukcje(parametry);
    }
    else if (dynamic_cast<CGUIMsgOprogramie*>(wiadomosc)!=0) {
        std::map<std::string,std::string> parametry;
        parametry.insert(std::pair<std::string,std::string>("tytul","Układanka"));
        parametry.insert(std::pair<std::string,std::string>("podtytul","Program zaliczeniowy - Zaawansowane C++"));
        parametry.insert(std::pair<std::string,std::string>("autor","Robert Płatkowski, OKNO, IP, 2018"));
        gui->wyswietlOprogramie(parametry);

    }
    else if (dynamic_cast<CGUIMsgWyjscie*>(wiadomosc)!=0) {
        gui->zamknijOkno();
    }
    else {

    }
}
