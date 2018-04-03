
#include "Kontroler/ckontroler.h"
#include <QString>
#include <string>
#include "GUI/GUImsg/cguimsgwcisnietepole.h"
#include "GUI/GUImsg/cguimsgwyjscie.h"
#include "GUI/GUImsg/cguimsgzadaniekonfiguracji.h"
#include "GUI/GUImsg/cguimsgkonfiguracja.h"
#include "GUI/GUImsg/cguimsginstrukcja.h"
#include "GUI/GUImsg/cguimsgoprogramie.h"
#include "GUI/GUImsg/cguimsgresetuj.h"
#include "GUI/GUImsg/cguimsgtasuj.h"
#include "GUI/GUImsg/cguimsgustawieniareczne.h"
#include "Model/Ukladanka/cmodelukladanka.h"

#include <iostream>

CKontroler::CKontroler(IGUI *gui) :
    gui(gui)
{
    //twórz model układanki z domyślnym rozmiarem
    ukladanka = new CModelUkladanka(4,4);
    gui->setKontroler(this); //przekaż wskaźnik na siebie do gui (do przesyłania wiadomości)
    //przerysuj planszę zgodnie z modelem;
    gui->rysujPlansze(ukladanka->getPlansza()->wektor(),ukladanka->getPlansza()->getN(),ukladanka->getPlansza()->getM());
    scObsluzStan();
}

CKontroler::~CKontroler()
{

}

void CKontroler::wyslijWiadomosc(CGUIMsg *wiadomosc)
{
    if (dynamic_cast<CGUIMsgWcisnietePole*>(wiadomosc)!=0) {
        scWykonajRuch(wiadomosc);
        scObsluzStan();
    }
    else if (dynamic_cast<CGUIMsgResetuj*>(wiadomosc)!=0) {
        scResetuj();
        scObsluzStan();
    }
    else if (dynamic_cast<CGUIMsgTasuj*>(wiadomosc)!=0) {
        scTasuj();
        scObsluzStan();
    }
    else if (dynamic_cast<CGUIMsgZadanieKonfiguracji*>(wiadomosc)!=0) {
        std::map<std::string, std::string> parametry;
        parametry.insert(std::pair<std::string,std::string>("N",std::to_string(ukladanka->getPlansza()->getN())));
        parametry.insert(std::pair<std::string,std::string>("N_min","2"));
        parametry.insert(std::pair<std::string,std::string>("N_max","8"));
        parametry.insert(std::pair<std::string,std::string>("M",std::to_string(ukladanka->getPlansza()->getM())));
        parametry.insert(std::pair<std::string,std::string>("M_min","2"));
        parametry.insert(std::pair<std::string,std::string>("M_max","8"));
        gui->wyswietlKonfiguracje(parametry);
    }
    else if (dynamic_cast<CGUIMsgKonfiguracja*>(wiadomosc)!=0) {
        scKonfiguruj(wiadomosc);
        scObsluzStan();
    }
    else if (dynamic_cast<CGUIMsgUstawianieReczne*>(wiadomosc)!=0) {
        scReczneUstawianie(wiadomosc);
        scObsluzStan();
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
        scZamknij();
    }
    else {

    }
}

void CKontroler::scZamknij()
{
    //usuń model
    delete ukladanka;
}

void CKontroler::scKonfiguruj(CGUIMsg *wiadomosc)
{
    CGUIMsgKonfiguracja *wiadomoscKonfiguracja=dynamic_cast<CGUIMsgKonfiguracja*>(wiadomosc);
    ukladanka->resetuj(wiadomoscKonfiguracja->getN(),wiadomoscKonfiguracja->getM());
    gui->rysujPlansze(ukladanka->getPlansza()->wektor(),ukladanka->getPlansza()->getN(),ukladanka->getPlansza()->getM());
}

void CKontroler::scTasuj()
{
    ukladanka->wygenerujLosoweUstawienie();
    gui->rysujPlansze(ukladanka->getPlansza()->wektor(),ukladanka->getPlansza()->getN(),ukladanka->getPlansza()->getM());
}

void CKontroler::scRozwiazuj()
{

}

void CKontroler::scResetuj()
{
    ukladanka->resetuj(ukladanka->getPlansza()->getN(),ukladanka->getPlansza()->getM());
    gui->rysujPlansze(ukladanka->getPlansza()->wektor(),ukladanka->getPlansza()->getN(),ukladanka->getPlansza()->getM());
}

void CKontroler::scReczneUstawianie(CGUIMsg *wiadomosc)
{
    CGUIMsgUstawianieReczne *wiadomoscUstawianieReczne=dynamic_cast<CGUIMsgUstawianieReczne*>(wiadomosc);
    ukladanka->setReczneUstawianie(wiadomoscUstawianieReczne->getWlaczone());
}

void CKontroler::scWykonajRuch(CGUIMsg *wiadomosc)
{
    CGUIMsgWcisnietePole *wiadomoscWcisnietePole=dynamic_cast<CGUIMsgWcisnietePole*>(wiadomosc);
    if (ukladanka->wykonajRuch(wiadomoscWcisnietePole->getPole())>-1) {
        std::vector<std::array<int,2>> v;
        v.push_back(ukladanka->getOstatniRuch());
        gui->zamienPola(v);
    }
}

void CKontroler::scObsluzStan() {
    switch(ukladanka->getStan()) {
    case EStan::rozwiazany:
        if (ukladanka->getLiczbaRuchow()>0) gui->wyswietlStatus("Rozwiązany!  liczba ruchów: " + std::to_string(ukladanka->getLiczbaRuchow()) + ", czas: " + std::to_string(ukladanka->getCzas()/1000)+"."+std::to_string(ukladanka->getCzas()%1000)+"s");
        else gui->wyswietlStatus("");
        break;
    case EStan::ustawianie:
        gui->wyswietlStatus("Ręczne ustawianie pozycji - aby rozpocząć układanie wyłącz tę opcję w menu->układanka");
        gui->setUstawianieReczne(true);
        break;
    case EStan::wolny:
        gui->wyswietlStatus("Dowolny ruch rozpocznie liczenie czasu");
        break;
    case EStan::rozwiazywanie:
        gui->wyswietlStatus("Liczba ruchów: " + std::to_string(ukladanka->getLiczbaRuchow()));
        break;
    }
}
