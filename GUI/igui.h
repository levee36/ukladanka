#ifndef IGUI_H
#define IGUI_H

#include <vector>
#include <array>
#include <map>
#include <string>
#include "Kontroler/ikontroler.h"

///
/// @ingroup view
///
/// @brief
/// interfejs klasy COknoGlowne do komunikacji z kontrolerem - klasą CKontroler
/// @details
/// interfejs zawiera metody umozliwiające kontrolerowi sterowanie informacjami wyświetlanymi w gui na podstawie akcji użytkownika i odpowiedzi modelu
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class IGUI {
public:

    ///
    /// @brief metoda ustawiająca rozmiar planszy i układająca elementy zgodnie z podanym wektorem 1-wymiarowym (odczyt liniowy wierszami poczynając od elementu (0,0))
    ///
    /// @param[in] tbl 1-wymiarowy wektor przedstawiający docelowy układ elementów układanki (odczyt liniowy wierszami poczynając od elementu (0,0))
    /// @param[in] N liczba kolumn planszy
    /// @param[in] M liczba wierszy planszy
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool rysujPlansze(std::vector<int> tbl, int N, int M) = 0;

    ///
    /// @brief metoda zamieniająca miejscami wskazane pola na planszy
    ///
    /// @param[in] pary wektor par liczb - liczby w każdej parze określają nr pól do zamiany miejscami.
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool zamienPola(std::vector<std::array<int,2>> pary) = 0;

    ///
    /// @brief metoda ustawiająca opcję Ustawienie Ręczne z menu okna
    ///
    /// @param[in] ustawienie jeśli true - opcja Ustawienie Ręczne z menu okna zostanie zaznaczona, jeśli false - wyłączona
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool setUstawianieReczne(bool ustawianie) = 0;

    ///
    /// @brief metoda wyświetlająca okno konfiguracji (okno modalne) i ustawiająca parametry wyświetlane w tym oknie zgodnie z przekazanym słownikiem (mapą)
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool wyswietlKonfiguracje(std::map<std::string,std::string> param) = 0;

    ///
    /// @brief metoda wyświetlająca przekazany jako parametr tekst w StatusBarze okna głównego
    ///
    /// @param[in] status tekst do wyświetlenia w StatusBarze okna głównego
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool wyswietlStatus(std::string status) = 0;

    ///
    /// @brief metoda zamykająca okno główne
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool zamknijOkno() = 0;

    ///
    /// @brief metoda wyświetlająca okno O programie (okno modalne) z informacjami przekazanymi przez parametr
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool wyswietlOprogramie(std::map<std::string,std::string> param) = 0;

    ///
    /// @brief metoda wyświetlająca okno Instrukcje (okno modalne) z informacjami przekazanymi przez parametr
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool wyswietlInstrukcje(std::map<std::string,std::string> param) = 0;

    ///
    /// @brief metoda wyświetlająca okno popup (okno modalne) z informacjami przekazanymi przez parametr
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool wyswietlOknoPopup(std::map<std::string,std::string> param) = 0;

    ///
    /// @brief metoda zamykająca okno popup (jeśli otwarte)
    ///
    /// @return true jeśli metoda się powiodła
    ///
    virtual bool zamknijOknoPopup() = 0;

    ///
    /// @brief metoda ustawiająca wskaźnik na obiekt kontrolera (przez interfejs IKontroler)
    ///
    /// @param[in] kontroler wskaźnik na obiekt kontrolera
    ///
    virtual void setKontroler(IKontroler *kontroler) = 0;
};

#endif // IGUI_H

