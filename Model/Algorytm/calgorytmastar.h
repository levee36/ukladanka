#ifndef CALGORYTMASTAR_H
#define CALGORYTMASTAR_H

#include <QObject>
#include <set>
#include "Model/Algorytm/ialgorytm.h"
#include "Model/Algorytm/cwezel.h"
#include "Model/Algorytm/cwezelcompare.h"
#include "Model/carray2d.h"
#include "Model/Ukladanka/heurystyki/cheurystyka.h"

///
/// @defgroup algorytm AlgorytmAStar
/// @ingroup model
///
/// @brief
/// Klasy realizujące model układanki
///
/// @author Robert Płatkowski
/// @date 2018-04-15
///

///
/// @ingroup algorytm
/// @brief
/// klasa realizująca model algorytmu A*
///
/// @details
/// klasa realizuje model algorytmu A*
/// implementacja algorytmu jest odseparowana od problemu, co oznacza, że metody klasy nie są powiązane z problemem, którego przestrzeń stanów ma być przeszukiwana
/// do powiązania algorytmu z problemem służy klasa CWezel
///
/// @author Robert Płatkowski
/// @date 2018-04-15
///
class CAlgorytmAStar : public QObject, public IAlgorytm
{
    Q_OBJECT
public:
    ///
    /// @brief konstruktor
    ///
    /// @details na podstawie przekazanego wskaźnika na obiekt CArray2D<int> tworzy obiekt klasy CWezel
    /// i wykonuje inicjalizację algorytmu - wstawia węzeł do zbioru CLOSED
    ///
    /// @param[in] stanPoczatkowy wskaźnik na obiekt CArray2D<int> reprezentujący startowy układ elementów układanki
    ///
    CAlgorytmAStar(CArray2D<int> *stanPoczatkowy, CHeurystyka *heurystyka);

    ///
    /// @brief destruktor
    ///
    /// @details usuwa węzeł początkowy i czyści zbiory OPEN i CLOSED (poprzez usunięcie obiektów węzłów na które wskazują wskaźniki przechowywane w tych zbiorach)
    ///
    ~CAlgorytmAStar();

    ///
    /// @brief metoda wykonuje jeden krok algorytmu
    ///
    /// @details działanie metody (jeden krok algorytmu) polega na wykonaniu w kolejności czynności: <br>
    /// 1. Pobierz ze zbioru OPEN węzeł o najmniejszej wartości funkcji oceny f, ustaw na nim wskaźnik aktualny i wstaw go do zbioru CLOSED <br>
    /// W tym celu pobierz pierwszy element ze zbioru OPENoceny<br>
    /// 2. Sprawdź, czy wskaźnik aktualny wskazuje na węzeł końcowy (wykonaj metodę statyczną CModelUkladanka::CzyUlozona dla planszy przechowywanej w tym węźle) <br>
    ///     - jeśli metoda zwróci wartość true - węzeł końcowy, zakończ działanie metody i zwróć wartość true <br>
    /// 3. Znajdź następniki węzła ze wskaźnika aktualny (za pomocą metody statycznej CModelUkladanka::zwrocMozliweRuchy) <br>
    /// 4. Dla każdego ze znalezionych następników: <br>
    ///     - oblicz koszt dojścia - jest równy kosztowi dojścia do obecnego węzła + 1 (koszt dla węzła aktualny to metoda CWezel::getKoszt) <br>
    ///     - oblicz wartość heurystyki (metoda CWezel::szacujOdleglosc dla sprawdzanego następnika) <br>
    ///     - oblicz wartość funkcji oceny - równą sumie kosztu i heurystyki <br>
    ///     - zapamiętaj wyliczone wartości w tym węźle oraz zapamiętaj jako poprzednik węzeł aktualny oraz ruch jaki został wykonany, by z węzła aktualnego uzyskać ten następnik <br>
    ///     (za pomocą metody CWezel::aktualizujOceneKoszt) <br>
    ///     - sprawdź, czy następnik NIE należy do zbioru OPEN lub CLOSED <br>
    ///     Jeśli warunek jest spełniony - dopisz go do zbioru OPEN (i OPENoceny) i przejdź do sprawdzania kolejnego następnika <br>
    ///     Jeśli warunek nie był spełnionu to: <br>
    ///     - sprawdź warunek: ((następnik należy do zbioru OPEN lub następnik należy do zbioru CLOSED) i jego ocena jest niższa (lepsza) niż węzła ze zbioru OPEN/CLOSED). <br>
    ///     Jeśli warunek jest spełniony to: <br>
    ///         - jeśli węzeł był w CLOSED - usuń ten węzeł z CLOSED <br>
    ///         - odnajdź ten węzeł w OPEN, usuń i wstaw do OPEN węzeł-następnik teraz sprawdzany <br>
    ///         - odnajdź ten węzeł w OPENoceny, usuń i wstaw do OPENoceny węzeł-następnik teraz sprawdzany <br>
    ///     Przejdź do sprawdzania kolejnego następnika <br>
    /// 5. Zwróć wartość false (w tym kroku nie znaleziono węzła końcowego) <br>
    ///
    /// @return true - jeśli w tym kroku algorytmu znaleziono rozwiązanie (osiągnięto cel - węzeł to rozwiązanie: ułożona układanka)
    ///
    bool wykonajKrokAlgorytmu();

    ///
    /// @brief metoda zwraca ścieżkę od węzła aktualnego do węzła początkowego w postaci wektora liczb - gdzie każda liczba oznacza nr pola z którego wykonano ruch w danym kroku
    ///
    /// @details metoda zwraca ścieżkę od węzła aktualnego do węzła początkowego w postaci wektora liczb - gdzie każda liczba oznacza nr pola z którego wykonano ruch w danym kroku <br>
    /// metoda wywołana po osiągnięciu węzła końcowego (rozwiązania) - podaje sekwencję ruchów, które należy wykonać (odczytując wektor w kierunku odwrotnym)
    ///
    /// @return wektor liczb oznaczających numery pól z których wykonano ruchy w danym kroku
    ///
    std::vector<int> zwrocSciezke();

    ///
    /// @brief metoda zwraca całkowitą liczbę węzłów odwiedzonych do tej pory przez algorytm przeszukujący
    ///
    /// @return liczba odwiedzonych węzłów
    ///
    int getLiczbaOdwiedzonych();

    ///
    /// @brief metoda ustawia atrybut - wskaźnik na obiekt heurystyki używany do szacowania odległości od węzła końcowego (liczby ruchów pozostałych do wykonania do ułożenia układanki)
    ///
    /// @param[in] heurystyka wskaźnik na obiekt heurystyki - klasy dziedziczącej z CHeurystyka
    ///
    void setHeurystyka(CHeurystyka *heurystyka);

    ///
    /// @brief metoda zwracająca wskaźnik na obiekt heurystyki używany do szacowania odległości od węzła końcowego
    ///
    /// @return wskaźnik na obiekt heurystyki - klasy dziedziczącej z CHeurystyka
    ///
    CHeurystyka* getHeurystyka();

    ///
    /// @brief metoda resetująca obiekt - czyszcząca zbiory OPEN i CLOSED, zerująca wskaźnik na aktualny węzeł oraz zerująca statystyki
    ///
    void wyczysc();

    double getAktHeur();

private:
    CWezel *najmniejszyOPEN(); ///<metoda zwraca element zbioru OPEN o najmniejszej ocenie

private:
    CWezel *aktualny;
    std::set<CWezel*,CWezelCompare> zbiorOPEN;
    std::set<CWezel*,CWezelCompare> zbiorCLOSED;
    int liczbaOdwiedzonych;
    CHeurystyka *heurystyka;
    double aktHeur=-1;
};

#endif // CALGORYTMASTAR_H
