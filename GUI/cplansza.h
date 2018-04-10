#ifndef CPLANSZA_H
#define CPLANSZA_H

#include <QObject>
#include <QFrame>
#include <QPushButton>
#include <vector>
#include <array>
#include "Kontroler/ikontroler.h"
#include "GUI/cpole.h"

namespace Ui {
class CPlansza;
}

///
/// @ingroup view
///
/// @brief
/// klasa gui realizująca kontrolkę(widget) reprezentującą planszę układanki, dziedziczy z klasy QFrame
///
/// @details klasa stanowi kompozytowe rozszerzenie klasy QFrame przez dodanie zestawu przycisków QPushButton wraz z obsługą ich kliknięcia i rozpoznania, który został kliknięty
///
/// @author Robert Płatkowski
/// @date 2018-04-10
///
class CPlansza : public QFrame
{
    Q_OBJECT

public:
    ///
    /// @brief konstruktor kontrolki reprezentującej planszę
    ///
    /// @details konstruktor tworzy obiekt planszy jako zwykły obiekt QFrame
    /// tworzy layout typu siatkowego (QGridLayout) o liczbie kolumn i wierszy zgodnej z przekazanymi parametrami
    /// wypełnia komórki layoutu nowotworzonymi obiektami klasy CPole (reprezentującymi poszczególne pola układanki) <br>
    /// obiekty CPole są tworzone z parametrami (numerem elementu) zgodnymi z odczytanymi z dostarczonego wektora 1-wymiarowego będącego reprezentacją liniową planszy układanki
    /// (w odczycie liniowym wierszami poczynając od elementu (0,0)) <br>
    /// w wektorze listaPol pamiętane są wskaźniki do wszystkich utworzonych przycisków (na i-tej pozycji wektora pamiętany jest wskaźnik do i-tego pola układanki w odczycie liniowym)
    ///
    /// @param[in] tbl wektor 1-wymiarowy będący reprezentacją liniową planszy układanki (nr pól w odczycie liniowym wierszami poczynając od elementu (0,0))
    /// @param[in] N - liczba kolumn tworzonej planszy
    /// @param[in] M - liczba wierszy tworzonej planszy
    /// @param[in] kontroler - wskaźnik na obiekt kontrolera - do ewentualnego przesyłania informacji o akcji uzytkownika za pomocą metody CKontroler::wyslijWiadomosc
    ///
    CPlansza(std::vector<int> tbl, int N, int M, IKontroler *kontroler, QWidget *parent = 0);

    ///
    /// @brief destruktor
    ///
    /// @details niszczy wektor przycisków
    ///
    ~CPlansza();

    ///
    /// @brief metoda zamieniająca miejscami wskazane pola na graficznej reprezentacji planszy
    ///
    /// @details zamiana pól polega na zamianie wartości nrPola we wskazanych elementach każdej pary
    /// w tym celu wykorzystywana jest metoda CPole::getNumer do odczytu nr elementu w danym polu
    /// oraz metoda CPole::setNumer do ustawienia nr elementu w danym polu
    ///
    /// @param[in] pary wektor par liczb - liczby w każdej parze określają nr pól do zamiany miejscami.
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool zamienPola(std::vector<std::array<int,2>> pary);

    ///
    /// @brief metoda ustawiająca nr elementów na graficznej reprezentacji planszy zgodnie z przekazanym przez parametr porządkiem (w odczycie liniowym)
    ///
    /// @details za pomocą CPole::setNumer oraz iteratora po wektorze przekazanym przez parametr metoda ustawia w kolejnych polach graficznej reprezentacji planszy (do których wskaźniki przechowywane są w wektorze listaPol)
    /// nr elementów odczytane kolejno z przekazanego wektora
    /// Jesli w przekazanym wektorze jest mniej elementów niż w wektorze listaPol (mniej niż pól układanki) - pozostałe pola układanki są pomijane (zachowują poprzednie nr elementów)
    /// jeśli przekazany wektor ma więcej wartości niż pól planszy - nadwyżka jest pomijana
    ///
    /// @param[in] tbl wektor 1-wymiarowy będący reprezentacją liniową planszy układanki (nr pól w odczycie liniowym wierszami poczynając od elementu (0,0))
    ///
    /// @return true jeśli metoda się powiodła
    ///
    bool ustawKolejnosc(std::vector<int> tbl);

public slots:
    void on_actionPole_pressed(); ///< slot powiązany z sygnałem wysyłanym po wciśnięciu któregokolwiek przycisku reprezentującego element układanki, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość określającą nr wciśniętego pola (CGUIMsgWcisnietePole)

private:
    IKontroler *kontroler;
    QWidget *m_parent;
    std::vector<CPole*> listaPol;
    int N;
    int M;
    int rozmiarPola;
};

#endif // CPLANSZA_H
