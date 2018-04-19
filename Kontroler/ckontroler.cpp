
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
#include "GUI/GUImsg/cguimsgrozwiaz.h"
#include "GUI/GUImsg/cguimsgpopup.h"
#include "Model/Ukladanka/cmodelukladanka.h"
#include "Model/Algorytm/calgorytmastar.h"

#include "Model/Algorytm/cwezelcompare.h"

#include <iostream>

CKontroler::CKontroler(IGUI *gui) :
    gui(gui),
    timer(new QTimer())
{
    //twórz model układanki z domyślnym rozmiarem
    ukladanka = new CModelUkladanka(4,4);
    gui->setKontroler(this); //przekaż wskaźnik na siebie do gui (do przesyłania wiadomości)

    //przerysuj planszę zgodnie z modelem;
    gui->rysujPlansze(ukladanka->getPlansza()->wektor(),ukladanka->getPlansza()->getN(),ukladanka->getPlansza()->getM());
    scObsluzStan();

    algorytm = 0;
    watek.setAlgorytm(algorytm);

    timer->setSingleShot(true); //ustawienie timera jako singleshot (zatrzymuje działanie po pierwszym timeoucie i wymaga ponownego zainicjowania metodą start)

    //powiąż sygnały wysyłane z wątku algorytmu z obsługującymi je slotami kontrolera
    QObject::connect(&watek, SIGNAL(krokWykonany(QString)), this, SLOT(krokAlgorytmu(QString)));
    QObject::connect(&watek, SIGNAL(rozwiazanieZnalezione()), this, SLOT(koniecAlgorytmu()));
    QObject::connect(&watek, SIGNAL(przerwaneDzialanie()), this, SLOT(przerwanyAlgorytm()));

    //powiąż sygnał timeout QTimera ze slotem obsługującym sekwencyjną prezentację znalezionego rozwiązania
    QObject::connect(timer,SIGNAL(timeout()),SLOT(krokPrezentacjiRozwiazania()));

}

CKontroler::~CKontroler()
{
    if (algorytm!=0) delete algorytm;
    delete timer;
    delete ukladanka;
}

void CKontroler::wyslijWiadomosc(CGUIMsg *wiadomosc)
{
    //wyłącz prezentację, jeśli trwa
    if (prezentacjaTrwa) prezentacjaTrwa=false;

    //eykonaj odpowiedni scenariusz na podstawie typu wiadomości (dynamicznie rzutując CGUIMsg na klasy pochodne i sprawdzając rezultat)
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
        scZadanieKonfiguracji();
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
        scWyswietlInstrukcje();
    }
    else if (dynamic_cast<CGUIMsgOprogramie*>(wiadomosc)!=0) {
        scWyswietlOprogramie();
    }
    else if (dynamic_cast<CGUIMsgRozwiaz*>(wiadomosc)!=0) {
        scRozwiazuj();
    }
    else if (dynamic_cast<CGUIMsgWyjscie*>(wiadomosc)!=0) {
        scZamknij();
    }
    else if (dynamic_cast<CGUIMsgPopup*>(wiadomosc)!=0) {
        CGUIMsgPopup *wiadomoscPopup=dynamic_cast<CGUIMsgPopup*>(wiadomosc);
        //obsługa wiadomości wysłanej z okienka popup - identyfikacja na podstawie napisu na przycisku OK
        if (wiadomoscPopup->getPrzycisk()==std::string("Przerwij") && watek.isRunning())
            watek.przerwij();
        else if (wiadomoscPopup->getPrzycisk()==std::string("Pokaż!"))
            scPrezentujRozwiazanie();
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
    if (!watek.isRunning()) {
        if (ukladanka->czyUlozona()) { //zakończ jeśli bieżący układ jest rozwiązaniem, pokaż okienko popup z informacją
            std::map<std::string,std::string> parametry;
            parametry.insert(std::pair<std::string,std::string>("tytul","Szukanie rozwiązania"));
            parametry.insert(std::pair<std::string,std::string>("tresc","Podany układ jest układem końcowym!"));
            parametry.insert(std::pair<std::string,std::string>("przycisk","Oj!"));
            gui->wyswietlOknoPopup(parametry);
            return;
        }
        if (algorytm==0) algorytm = new CAlgorytmAStar(new CArray2D<int>(*(ukladanka->getPlansza())),new CHeurystykaManhattan()); //pierwsze uruchomienie algorytmu - twórz CAlgorytmAStar i przekaż kopię aktualnej planszy pobranej z modelu układanki
        else algorytm->wyczysc(new CArray2D<int>(*(ukladanka->getPlansza()))); //czyść dane w obiekcie algorytm i przekaż kopię aktualnego stanu planszy przekazanego z modelu układanki
        watek.setAlgorytm(algorytm);
        watek.start();
        std::map<std::string,std::string> parametry;
        parametry.insert(std::pair<std::string,std::string>("tytul","Szukanie rozwiązania"));
        parametry.insert(std::pair<std::string,std::string>("tresc","Trwa działanie algorytmu A*"));
        parametry.insert(std::pair<std::string,std::string>("przycisk","Przerwij"));
        gui->wyswietlOknoPopup(parametry);
    }
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
        /* sprawdza czy wykonano jakieś ruchy prowadzące do rozwiązania
         * - ma to na celu wyświetlanie okienka popup tylko wtedy, gdy rzeczywiście zmaleziono rozwiązanie, a nie np. zresetowano planszę
         * sprawdza też, czy nie trwa właśnie prezentacja znaelzionego rozwiązania przez algorytm
         * - wtedy też końcowe okienko się nie pokazuje (nie ma sensu podawać czasu rozwiązania - bo to czas animacji, a statystyki były pokazane w poprzednim okienku popup
         */
        if (ukladanka->getLiczbaRuchow()>0 && !prezentacjaTrwa) {
            gui->wyswietlStatus("Rozwiązany!  liczba ruchów: " + std::to_string(ukladanka->getLiczbaRuchow()) + ", czas: " + std::to_string(ukladanka->getCzas()/1000)+"."+std::to_string(ukladanka->getCzas()%1000)+"s");
            std::map<std::string,std::string> parametry;
            parametry.insert(std::pair<std::string,std::string>("tytul","Sukces!"));
            parametry.insert(std::pair<std::string,std::string>("tresc","Układanka została rozwiązana!\nLiczba wykonanych ruchów: "+std::to_string(ukladanka->getLiczbaRuchow())+"\nCałkowity czas: "+ std::to_string(ukladanka->getCzas()/1000)+"."+std::to_string(ukladanka->getCzas()%1000)+"s"));
            parametry.insert(std::pair<std::string,std::string>("przycisk","Hura!"));
            gui->wyswietlOknoPopup(parametry);
        }
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

void CKontroler::scZadanieKonfiguracji()
{
    std::map<std::string, std::string> parametry;
    parametry.insert(std::pair<std::string,std::string>("N",std::to_string(ukladanka->getPlansza()->getN())));
    parametry.insert(std::pair<std::string,std::string>("N_min","2"));
    parametry.insert(std::pair<std::string,std::string>("N_max","8"));
    parametry.insert(std::pair<std::string,std::string>("M",std::to_string(ukladanka->getPlansza()->getM())));
    parametry.insert(std::pair<std::string,std::string>("M_min","2"));
    parametry.insert(std::pair<std::string,std::string>("M_max","8"));
    gui->wyswietlKonfiguracje(parametry);
}

void CKontroler::scWyswietlInstrukcje()
{
    std::map<std::string,std::string> parametry;
    parametry.insert(std::pair<std::string,std::string>("instrukcje","Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."));
    gui->wyswietlInstrukcje(parametry);
}

void CKontroler::scWyswietlOprogramie()
{
    std::map<std::string,std::string> parametry;
    parametry.insert(std::pair<std::string,std::string>("tytul","Układanka"));
    parametry.insert(std::pair<std::string,std::string>("podtytul","Program zaliczeniowy - Zaawansowane C++"));
    parametry.insert(std::pair<std::string,std::string>("autor","Robert Płatkowski, OKNO, IP, 2018"));
    gui->wyswietlOprogramie(parametry);
}

void CKontroler::scPrzerwijPrezentacje()
{
    prezentacjaTrwa = false;
}

void CKontroler::scPrezentujRozwiazanie()
{
    prezentacjaTrwa = true;
    timer->start(czasKrokuPrezentacji);
}

void CKontroler::krokAlgorytmu(QString status)
{
    gui->wyswietlStatus("Odwiedzonych: "+status.toStdString()+"; heur = "+std::to_string(algorytm->getAktHeur()));
}

void CKontroler::koniecAlgorytmu()
{
    gui->wyswietlStatus("Koniec!");
    gui->zamknijOknoPopup();
    sciezka = algorytm->zwrocSciezke();
    std::map<std::string,std::string> parametry;
    parametry.insert(std::pair<std::string,std::string>("tytul","Sukces!"));
    parametry.insert(std::pair<std::string,std::string>("tresc","Algorytm znalazł rozwiązanie w " + std::to_string((algorytm->zwrocSciezke()).size()) + " krokach\nodwiedzając " + std::to_string(algorytm->getLiczbaOdwiedzonych()) + " węzłów"));
    parametry.insert(std::pair<std::string,std::string>("przycisk","Pokaż!"));
    gui->wyswietlOknoPopup(parametry);
}

void CKontroler::przerwanyAlgorytm()
{
    gui->wyswietlStatus("działanie algorytmu przeszukującego zostało przerwane");
}

void CKontroler::krokPrezentacjiRozwiazania()
{
    if (prezentacjaTrwa) {
        //wykonaj ruch zapisany na aktualnie ostatnim miejscu w wektorze sciezka
        int ruch = sciezka.back();
        if (ruch>-1 && ukladanka->wykonajRuch(ruch)>-1) {
            std::vector<std::array<int,2>> v;
            v.push_back(ukladanka->getOstatniRuch());
            gui->zamienPola(v);
        }
        sciezka.pop_back(); //usuń ostatni element wektora
        if (sciezka.size()>0) timer->start(czasKrokuPrezentacji);
    }
}
