#ifndef COKNOGLOWNE_H
#define COKNOGLOWNE_H

#include <QMainWindow>
#include <QCloseEvent>
#include <map>
#include <vector>
#include <array>
#include <string>
#include "GUI/igui.h"
#include "GUI/cplansza.h"
#include "Kontroler/ikontroler.h"

///
/// @defgroup view GUI
///
/// @brief
/// Klasy realizujące wzorzec architektoniczny View, czyli graficzny interfejs użytkownika
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///

namespace Ui {
class COknoGlowne;
}

///
/// @ingroup view
///
/// @brief
/// główna klasa gui - realizuje główne okno aplikacji, dziedziczy z klasy QMainWindow
/// @details
/// zawiera metody umozliwiające kontrolerowi sterowanie informacjami wyświetlanymi w gui na podstawie akcji użytkownika i odpowiedzi modelu
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class COknoGlowne : public QMainWindow, public IGUI
{
    Q_OBJECT

public:
    ///
    /// @brief konstruktor inicjujący kontrolki okna (obiekt CPlansza)
    ///
    /// @details konstruktor inicjuje obiekt planszy (CPlansza) z domyślnym rozmiarem 1x1
    ///
    explicit COknoGlowne(QWidget *parent = 0);

    ///
    /// @brief destruktor
    ///
    /// @details niszczy obiekt planszy i ui
    ///
    ~COknoGlowne();

    ///
    /// @brief metoda ustawiająca wskaźnik na obiekt kontrolera (przez interfejs IKontroler)
    ///
    /// @param[in] kontroler wskaźnik na obiekt kontrolera
    ///
    void setKontroler(IKontroler *kontroler);

    ///
    /// @brief metoda ustawiająca rozmiar planszy i układająca elementy zgodnie z podanym wektorem 1-wymiarowym (odczyt liniowy wierszami poczynając od elementu (0,0))
    ///
    /// @details metoda usuwa dotychczasowy obiekt CPlansza, tworzy nowy obiekt tej klasy przekazując konstruktorowi otrzymane jako parametry: rozmiar i wektor opisujący rozmieszczenie elementów
    /// po czym wstawia utworzony obiekt CPlansza do layoutu swojego central Widgeta i zapamiętuje wskaźnik do tego obiektu
    ///
    /// @param[in] tbl 1-wymiarowy wektor przedstawiający docelowy układ elementów układanki (odczyt liniowy wierszami poczynając od elementu (0,0))
    /// @param[in] N liczba kolumn planszy
    /// @param[in] M liczba wierszy planszy
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool rysujPlansze(std::vector<int> tbl, int N, int M);

    ///
    /// @brief metoda zamieniająca miejscami wskazane pola na planszy
    ///
    /// @details metoda otrzymuje jako parametr wektor par liczb, liczby w każdej parze określają nr pól do zamiany miejscami.
    /// Nr pola określa położenie pola w odczycie liniowym wierszami poczynając od elementu (0,0)
    ///
    /// @param[in] pary wektor par liczb - liczby w każdej parze określają nr pól do zamiany miejscami.
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool zamienPola(std::vector<std::array<int,2>> pary);

    ///
    /// @brief metoda ustawiająca opcję Ustawienie Ręczne z menu okna
    ///
    /// @param[in] ustawienie jeśli true - opcja Ustawienie Ręczne z menu okna zostanie zaznaczona, jeśli false - wyłączona
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool setUstawianieReczne(bool ustawianie);

    ///
    /// @brief metoda wyświetlająca okno konfiguracji (okno modalne) i ustawiająca parametry wyświetlane w tym oknie zgodnie z przekazanym słownikiem (mapą)
    ///
    /// @details poszczególne parametry identyfikowane są po ustalonych wartościach klucza - jeśli w przekazanej mapie nie występuje dana wartość przyjmowana jest wartość domyślna określona w metodzie
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool wyswietlKonfiguracje(std::map<std::string,std::string> param);

    ///
    /// @brief metoda wyświetlająca przekazany jako parametr tekst w StatusBarze okna głównego
    ///
    /// @param[in] status tekst do wyświetlenia w StatusBarze okna głównego
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool wyswietlStatus(std::string status);

    ///
    /// @brief metoda zamykająca okno główne
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool zamknijOkno();

    ///
    /// @brief metoda wyświetlająca okno O programie (okno modalne) z informacjami przekazanymi przez parametr
    ///
    /// @details poszczególne parametry (tytuł, podtytuł, autor) identyfikowane są po ustalonych wartościach klucza - jeśli w przekazanej mapie nie występuje dana wartość przyjmowana jest wartość domyślna określona w metodzie
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool wyswietlOprogramie(std::map<std::string,std::string> param);

    ///
    /// @brief metoda wyświetlająca okno Instrukcje (okno modalne) z informacjami przekazanymi przez parametr
    ///
    /// @details poszczególne parametry (instrukcje) identyfikowane są po ustalonych wartościach klucza - jeśli w przekazanej mapie nie występuje dana wartość przyjmowana jest wartość domyślna określona w metodzie
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool wyswietlInstrukcje(std::map<std::string,std::string> param);

private slots:
    void on_actionKonfiguracja_triggered(); ///< slot powiązany z sygnałem wysyłanym po wybraniu opcji Ustawienia w menu, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość CGUIMsgZadanieKonfiguracji
    void on_actionWyjscie_triggered(); ///< slot powiązany z sygnałem wysyłanym po wybraniu opcji Wyjście w menu lub po kliknięciu przycisku zamykającego okno, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość CGUIMsgWyjscie
    void on_actionTasuj_triggered(); ///< slot powiązany z sygnałem wysyłanym po wybraniu opcji Tasuj w menu, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość CGUIMsgTasuj
    void on_actionRozwiaz_triggered(); ///< slot powiązany z sygnałem wysyłanym po wybraniu opcji Rozwiąż w menu, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość CGUIMsgRozwiaz
    void on_actionResetuj_triggered(); ///< slot powiązany z sygnałem wysyłanym po wybraniu opcji Resetuj w menu, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość CGUIMsgResetuj
    void on_actionReczneUstawianie_triggered(bool checked); ///< slot powiązany z sygnałem wysyłanym po ustawieniu/wyłączeniu opcji Ręczne Ustawienia w menu, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość CGUIMsgUstawianieReczne
    void on_actionInstrukcje_triggered(); ///< slot powiązany z sygnałem wysyłanym po wybraniu opcji Instrukcje w menu, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość CGUIMsgInstrukcja
    void on_actionOprogramie_triggered(); ///< slot powiązany z sygnałem wysyłanym po wybraniu opcji O programie w menu, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość CGUIMsgOprogramie

private:
    void closeEvent(QCloseEvent *event);

    Ui::COknoGlowne *ui;
    CPlansza *plansza;
    IKontroler *kontroler;
};

#endif // COKNOGLOWNE_H
