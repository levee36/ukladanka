#ifndef CWEZEL_H
#define CWEZEL_H

#include "Model/carray2d.h"
#include "Model/Ukladanka/heurystyki/cheurystyka.h"

///
/// @ingroup algorytm
/// @brief
/// klasa reprezentująca pojedynczy węzeł drzewa przeszukiwań algorytmu A*
///
/// @details klasa realizuje węzeł drzewa przeszukiwań w modelu algorytmu A* wiążąc algorytm z problemem znajdowania rozwiązania układanki
/// obiekt tej klasy przechowuje konkretny stan układanki - w postaci obiektu klasy CArray2D - opisującej rozłożenie elementów łamigłówki oraz rozmiar planszy
/// metody klasy pozwalają sprawdzić poprzedni stan układanki, ruch jaki został wykonany, by z poprzednika znaleźć się w aktualnym stanie (ruch jest to numer pola, z którego został przesunięty element),
/// wyliczyć dotychczasowy koszt dojścia do tego układu z układu startowego, szacowany koszt dojścia do układu końcowego (wartość heurystyki)
/// oraz podać listę następników - układów możliwych do osiągnięcia z aktualnego przez wykonanie jednego ruchu
///
/// @author Robert Płatkowski
/// @date 2018-04-11
///
class CWezel
{
public:
    ///
    /// @brief konstruktor tworzący obiekt węzła grafu przeszukiwań reprezentujący stan układanki przekazany przez parametr
    ///
    /// @details konstruktor inicjuje jedynie wektor reprezentujący układ elementów na planszy układanki, pozostałe atrybuty są zerowane - muszą być ustawione metodą aktualizujOceneKoszt
    ///
    /// @param[in] stan wskaźnik na wektor dwuwymiarowy reprezentujący układ elementów układanki oraz jej rozmiary
    ///
    CWezel(CArray2D<int> *stan);

    ///
    /// @brief destruktor
    ///
    /// @details niszczy obiekt reprezentujący rozkład elementów planszy układanki
    ///
    ~CWezel();

    ///
    /// @brief metoda zwracająca zapamiętaną w węźle wartość funkcji oceny (suma kosztu dojścia do węzła i szacowanej odłegłości do węzła końcowego)
    ///
    /// @return zapamiętana w węźle wartość funkcji oceny (suma kosztu dojścia do węzła i szacowanej odłegłości do węzła końcowego)
    ///
    double getOcena();

    ///
    /// @brief metoda zwracająca zapamiętaną w węźle wartość funkcji kosztu dojścia (długość scieżki od węzła startowego)
    ///
    /// @return zapamiętana w węźle wartość funkcji kosztu dojścia (długość scieżki od węzła startowego)
    ///
    double getKoszt();

    ///
    /// @brief metoda wyliczająca wg podanej w parametrze heurystyki szacowaną odległość do węzła końcowego
    ///
    /// @return szacowana odległość do węzła końcowego wyliczona wg podanej w parametrze heurystyki
    ///
    double szacujOdleglosc(CHeurystyka *heurystyka);

    ///
    /// @brief metoda zwracająca stan układanki reprezentowany przez ten węzeł
    ///
    /// @details metoda zwraca wskaźnik na układ elementów na planszy układanki w postaci wektora dwuwymiarowego
    ///
    /// @return wskaźnik na stan układanki reprezentowany przez ten węzeł - układ elementów na planszy układanki w postaci wektora dwuwymiarowego
    ///
    CArray2D<int>* getStan();

    ///
    /// @brief metoda aktualizuje wartość fukncji oceny i funkcji kosztu na podane wartości liczbowe oraz wskaźnik na węzeł poprzedający w drzewie przeszukiwania
    ///
    /// @details metoda jest wywoływana, gdy została znaleziona lepsza ścieżka (o lepszej, czyli mniejszej wartości funkcji oceny) <br>
    /// aktualizowane są zapamiętane wartości funkcji kosztu i funkcji oceny oraz zmieniany jest wskaźnik na węzeł poprzedzający oraz nr pola, z którego wykonano ostatni ruch
    ///
    /// @param[in] ocena nowa wartość funkcji oceny (koszt dotarcia + heurystyka) do zapamiętania w tym węźle
    /// @param[in] koszt nowa wartość funkcji kosztu dotarcia do zapamiętania w tym węźle
    /// @param[in] poprzednik wskaźnik na węzeł poprzedzający (z którego po wykonaniu ostatniego ruchu uzyskano aktualny węzeł)
    /// @param[in] ruch nr pola (w odczycie liniowym) na planszy, z którego wykonano ostatni ruch
    ///
    void aktualizujOceneKoszt(double ocena, double koszt, CWezel *poprzednik, int ruch);

    ///
    /// @brief metoda zwracająca wskaźnik na węzeł-poprzednik
    ///
    /// @details metoda zwracająca wskaźnik na węzeł-poprzednik, czyli rozkład układanki, z którego uzyskano rozkład zapamiętany w tym węźle po wykonaniu ruchu z pola o nr zapamiętanym w polu ruch
    ///
    /// @return wskaźnik na węzeł-poprzednik tego węzła w drzewie przeszukiwań
    ///
    CWezel *getPoprzednik();

    ///
    /// @brief metoda zwracająca wektor wskaźników na węzły-następniki tego węzła
    ///
    /// @details metoda zwracająca wektor wskaźników na węzły-następniki tego węzła, czyli węzły przedstawiające wszystkie rozkłady układanki
    /// możliwe do uzyskania z rozkładu zapamiętanego w tym węźle po wykonaniu jednego ruchu
    ///
    /// @return wektor wskaźników na węzły-następniki tego węzła
    ///
    std::vector<CWezel *> getNastepniki();

    ///
    /// @brief metoda zwracająca nr pola z którego wykonano ostatni ruch (prowadzący do układu elementów planszy zapamiętanego w tym węźle)
    ///
    /// @return nr pola (w odczycie liniowym) na planszy, z którego wykonano ostatni ruch
    ///
    int getRuch();

private:
    CArray2D<int> *stan;
    double ocena;
    double koszt;
    CWezel *poprzednik;
    int ruch;
};

#endif // CWEZEL_H
