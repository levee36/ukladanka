#ifndef CKONTROLER_H
#define CKONTROLER_H

#include "Kontroler/ikontroler.h"
#include "GUI/igui.h"
#include "GUI/GUImsg/cguimsg.h"
#include "Model/Ukladanka/iukladanka.h"

///
/// @defgroup controller Kontroler
///
/// @brief
/// Klasy realizujące wzorzec architektoniczny Controller
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///


///
/// @ingroup controller
/// @brief klasa realizująca główny obiekt aplikacji - kontroler
///
/// @details klasa kontrolera odpowiada za sterowanie aplikacją na podstawie wykonanych przez użytkownika na obiektach gui akcjach <br>
/// główną i jedyną metodą dostępną publicznie jest metoda umożliwiająca przekazywanie z gui do kontrolera informacji o wykonanej przez użytkownika akcji na interfejscie graficznym aplikacji
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///
class CKontroler : public IKontroler
{
public:
    ///
    /// @brief konstruktor przekazujący wskaźnik na obiekt gui (COknoGlowne przez interfejs IGUI)
    ///
    /// @details konstruktor kontrolera tworzy obiekt modelu CModelUkladanka, inicjalizuje go domyślnymi wartościami parametrów, oraz przekazuje dane odczytane z obiektu modelu do gui w celu wyświetlenia stanu planszy zgodnego z zapamiętanym w modelu
    ///
    CKontroler(IGUI *gui);

    ///
    /// @brief destruktor - usuwa obiekty modelu
    ///
    ~CKontroler();

    ///
    /// @brief metoda przesyłająca z gui do kontrolera obiekt z hierarchii klas wyprowadzonej z klasy bazowej CGUIMsg
    ///
    /// @details główna metoda sterująca aplikacji <br>
    /// na podstawie klasy przekazanego w argumencie obiektu z hierarchii klas wyprowadzonej z klasy bazowej CGUIMsg wywoływana jest jedna metod realizujących zadany scenariusz
    ///
    /// @param[in] wiadomosc wskaźnik na obiekt z hierarchii klas wyprowadzonej z klasy bazowej CGUIMsg
    ///
    void wyslijWiadomosc(CGUIMsg *wiadomosc);

protected: ///< metody realizujące scenariusze są chronione - dostępne tylko z wewnątrz klasy oraz ewentualnych klas pochodnych

    ///
    /// @brief metoda - scenariusz kończący działanie aplikacji
    ///
    /// @details metoda sprzątająca - usuwa obiekt modelu (destrukcja obiektów gui jest przeprowadzana przez tamte obiekty)
    ///
    void scZamknij();

    ///
    /// @brief metoda - scenariusz parametryzująca obiekt modelu na podstawie danych otrzymancyh z gui (poprzez obiekt klasy CGUIMsgKonfiguracja)
    ///
    /// @details metoda dynamicznie rzutuje wiadomosc na klasę pochodną CGUIMsgKonfiguracja,
    /// odczytuje z niej parametry (metody CGUIMsgKonfiguracja::getN i CGUIMsgKonfiguracja::getM),
    /// wykonuje reset planszy w modelu z podanymi nowymi wymiarami (CModelUkladanka::resetuj)
    /// i przekazuje do gui (metoda COknoGlowne::rysujPlansze) odczytane z modelu: układ planszy w postaci 1-wymiarowego wektora (metoda CModelUkladanka::wektor) oraz wymiary (metody CModelUkladanka::getN i CModelUkladanka::getM)
    ///
    /// @param[in] wiadomosc wskaźnik na obiekt klasy CGUIMsgKonfiguracja - wiadomość przekazana z gui (nowy rozmiar planszy)
    ///
    void scKonfiguruj(CGUIMsg *wiadomosc);

    ///
    /// @brief metoda - scenariusz wykonujący losowe rozłożenie elementów układanki dla obecnego rozmiaru modelu układanki
    ///
    /// @details metoda zleca modelowi wygenerowanie losowego rozłożenia elementów na planszy o obecnych wymiarach (metoda CModelUkladanka::wygenerujLosoweUstawienie),
    /// i przekazuje do gui (metoda COknoGlowne::rysujPlansze) odczytane z modelu: układ planszy w postaci 1-wymiarowego wektora (metoda CModelUkladanka::wektor) oraz wymiary (metody CModelUkladanka::getN i CModelUkladanka::getM)
    ///
    void scTasuj();

    ///
    /// @brief metoda - scenariusz znajdujący rozwiązanie za pomocą algorytmu A*
    ///
    /// @details TODO
    ///
    void scRozwiazuj();

    ///
    /// @brief metoda - scenariusz resetujący model układanki - dla obecnego rozmiaru planszy elementy układanki są rozmieszczane w porządku zgodnym z numeracją pól (układ końcowy - rozwiązanie)
    ///
    /// @details metoda ustawia wszystkie elementy układanki zgodnie z ich domyślnymi pozycjami (numery elementów odpowiadają numerom pól)
    /// wykonuje reset planszy w modelu z podanymi nowymi wymiarami (CModelUkladanka::resetuj)
    /// i przekazuje do gui (metoda COknoGlowne::rysujPlansze) odczytane z modelu: układ planszy w postaci 1-wymiarowego wektora (metoda CModelUkladanka::wektor) oraz wymiary (metody CModelUkladanka::getN i CModelUkladanka::getM)
    ///
    void scResetuj();

    ///
    /// @brief metoda - scenariusz włączający/wyłączający w modelu status ręcznego ustawiania pozycji startowej
    ///
    /// @details metoda dynamicznie rzutuje wiadomosc na klasę pochodną CGUIMsgUstawianieReczne,
    /// odczytuje z niej parametr (metoda CGUIMsgUstawianieReczne::getWlaczone) - informację czy status ma być włączony (true), czy wyłączony (false)
    /// i wywołuje odpowiednią metodę w modelu układanki (CModelUkladanka::setReczneUstawianie) w celu ustawienia aktualnego statusu modelu: <br>
    /// włączenie statusu polega na ustawieniu w modelu układanki stanu EStan::ustawianie, gdy z gui przekazano informację o włączeniu tego statusu
    /// wyłączenie statusu polega na ustawieniu w modelu układanki stanu EStan::wolny, pod warunkiem, że poprzedni status był równy EStan::ustawianie oraz informacja z gui mówi o wyłączeniu tego statusu
    ///
    /// @param[in] wiadomosc wskaźnik na obiekt klasy CGUIMsgUstawianieReczne - wiadomość przekazana z gui (włączenie/wyłączenie ręcznego ustawiania)
    ///
    void scReczneUstawianie(CGUIMsg *wiadomosc);

    ///
    /// @brief metoda - scenariusz sprawdzający możliwość wykonania przekazanego z gui ruchu oraz realizujący go (jeśli wykonanie jest możliwe)
    ///
    /// @details metoda dynamicznie rzutuje wiadomosc na klasę pochodną CGUIMsgWcisnietePole,
    /// odczytuje z niej parametr (metoda CGUIMsgWcisnietePole::getPole) - nr pola, które zostało kliknięte w gui (nr w liniowym odczycie planszy wierszami poczynając od lewego górnego rogu - pole (0,0))
    /// i wywołuje odpowiednią metodę w modelu układanki (CModelUkladanka::wykonajRuch) w celu sprawdzenia możliwości i ewentualnego wykonania ruchu <br>
    /// jesli metoda zwróci wartość różną od -1:
    ///   - ruch został wykonany (przez wywołaną metodę, aktualizuje ona układ planszy w modelu),
    ///   - pobierana jest informacja z modelu o ostatnim ruchu (CModelUkladanka::getOstatniRuch)
    ///   - w gui wywoływana jest metoda aktualizująca tylko dwa pola układanki - kliknięte i puste (metoda CModelUkladanka::zamienPola)
    /// jesli metoda zwróci wartość równą -1 - ruch nie jest możliwy i układ planszy nie jest zmieniany (w modelu układanki oraz w gui)
    ///
    /// @param[in] wiadomosc wskaźnik na obiekt klasy CGUIMsgWcisnietePole - wiadomość przekazana z gui  (nr klikniętego pola)
    ///
    void scWykonajRuch(CGUIMsg *wiadomosc);

    ///
    /// @brief metoda - scenariusz pomocniczy - odpowiedzialny za wyświetlanie informacji w StatusBarze okna głównego gui
    ///
    /// @details metoda uruchamiana po zrealizowaniu innych scenariuszy - tych, w wyniku których może zmienić się status modelu układanki
    /// metoda sprawdza status modelu (metoda CModelUkladanka::getStan) i na jego podstawie wywołuje w gui metodę wyświetlającą odpowiedni opis w StatusBarze (metoda COknoGlowne::wyswietlStatus)
    ///
    void scObsluzStan();

    ///
    /// @brief metoda - scenariusz zlecająca gui wyświetlenie okna konfiguracji z danymi pobranymi z modelu
    ///
    /// @details metoda pobiera z modelu rozmiar planszy (CModelUkladanka::getN i CModelUkladanka::getM) i przekazuje go do gui (COknoGlowne::wyswietlKonfiguracje)
    ///
    void scZadanieKonfiguracji();

    ///
    /// @brief metoda - scenariusz zlecająca gui wyświetlenie okna z instrukcjami
    ///
    /// @details metoda wywołuję metodę gui (COknoGlowne::wyswietlInstrukcje) i przekazuje za pomocą słownika parametry (tekst do wyświetlenia w oknie)
    ///
    void scWyswietlInstrukcje();

    ///
    /// @brief metoda - scenariusz zlecająca gui wyświetlenie okna z infromacjami o programie
    ///
    /// @details metoda wywołuję metodę gui (COknoGlowne::wyswietlOprogramie) i przekazuje za pomocą słownika parametry (tytuł, podtytuł i autora aplikacji)
    ///
    void scWyswietlOprogramie();

private:
    IGUI *gui; ///< wskaźnik na obiekt gui (obiekt klasy COknoGlowne realizujący interfejs IGUI)
    IUkladanka *ukladanka; ///< wskaźnik na obiekt modelu układanki (obiekt klasy CModelUkladanka realizujący interfejs IUkladanka)

};

#endif // CKONTROLER_H
