#ifndef IUKLADANKA_H
#define IUKLADANKA_H

#include "Model/carray2d.h"
#include "Model/Ukladanka/heurystyki/cheurystyka.h"
#include <vector>
#include <array>

///
/// @ingroup modelukladanka
/// @brief
/// typ wyliczeniowy określający aktualny status modelu układanki
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///
enum EStan {
    wolny, ///< układanka oczekuje na rozpoczęcie rozwiązywania lub rozpoczęcie ręcznego ustawiania pozycji startowej
    rozwiazywanie, ///< układanka jest w trakcie rozwiązywania
    ustawianie, ///< układanka jest w trakcie ręcznego ustawiania pozycji startowej
    rozwiazany ///< układanka właśnie została rozwiązana i przedstawia układ końcowy (wszystkie elementy na swoich pozycjach)
};

///
/// @ingroup model
/// @brief
/// interfejs klasy CModelUkladanka na potrzeby klasy CKontroler
/// @details
/// interfejs zawiera metody zrealizowane w klasie CModelUkladanka na potrzeby klasy CKontroler
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///
class IUkladanka
{

public:
    ///
    /// @brief metoda resetująca model układanki - ustawiająca nową planszę o podanym rozmiarze z ułożeniem końcowym (rozwiązaniem)
    ///
    /// @param[in] N nowa liczba kolumn
    /// @param[in] M nowa liczba wierszy
    /// @return zwraca wartość true gdy reset planszy się powiódł
    ///
    virtual bool resetuj(int N, int M) = 0;

    ///
    /// @brief metoda zwracająca wskaźnik na obiekt planszy przechowywany w modelu
    ///
    /// @return wskaźnik na obiekt planszy przechowywany w modelu
    ///
    virtual CArray2D<int> *getPlansza() = 0;

    ///
    /// @brief metoda podmieniająca obiekt planszy w modelu układanki na wskazany przez wskaźnik przekazany jako argument
    ///
    /// @param[in] plansza wskaźnik na obiekt planszy do ustawienia w modelu układanki
    ///
    virtual void setPlansza(CArray2D<int>*) = 0;

    ///
    /// @brief metoda ustawiająca elementy planszy zgodnie z podanym wektorem liczb
    ///
    /// @param[in] tbl wektor liczb int określających kolejne numery elementów do umieszczenia na planszy <br>
    /// (w odczycie liniowym poczynając od elementu (0,0))
    /// jeśli wektor tbl zawiera mniej elementów niż rozmiar planszy N*M, pozostałe elementy zostaną wyzerowane
    /// jeśli wektor tbl zawiera więcej elementów niż rozmiar planszy N*M, pozostałe elementy zostaną pominięte
    ///
    virtual void setPlansza(std::vector<int> tbl) = 0;

    ///
    /// @brief metoda sprawdzająca czy wskazany ruch jest możliwy do wykonania
    ///
    /// @param[in] nrPola numer pola planszy z którego ma zostać przesunięty element
    /// @return true jeśli ruch jest możliwy do wykonania
    ///
    virtual bool sprawdzRuch(int nrPola) = 0;

    ///
    /// @brief metoda wykonująca wskazany ruch i aktualizująca rozstawienie na planszy
    ///
    /// @param[in] nrPola numer pola planszy z którego ma zostać przesunięty element
    /// @return nr pola na który został przesunięty wskazany do wykonania ruchu element <br>
    /// jeśli ruch nie był możliwy do wykonania zwracany jest nr pola wskazanego jako argument
    ///
    virtual int wykonajRuch(int nrPola) = 0;

    ///
    /// @brief metoda zwracająca ostatni wykonany ruch na planszy (w postaci pary wartości - nr pola z którego przesunięto element i nr pola na który przesunięto element)
    ///
    /// @return para liczb - nr pola z którego przesunięto element i nr pola na który przesunięto element
    ///
    virtual std::array<int,2> getOstatniRuch() = 0;

    ///
    /// @brief metoda sprawdzająca czy rozstawienie elementów na planszy jest ustawieniem końcowym (rozwiązaniem)
    ///
    /// @return true - jeśli rozstawienie elementów na planszy jest ustawieniem końcowym (rozwiązaniem)
    ///
    virtual bool czyUlozona() = 0;

    ///
    /// @brief metoda zwracająca aktualny czas rozwiązywania układanki lub czas rozwiązania układanki
    ///
    /// @return liczba milisekund - czas rozwiązywania (jeśli nadal trwa) lub końcowy czas rozwiązania (jeśli układanka zostałą rozwiązana)
    ///
    virtual int getCzas() = 0;

    ///
    /// @brief metoda zwracająca liczbę wykonanych ruchów w czasie rozwiązywania układanki
    ///
    /// @return liczba wykonanych ruchów
    ///
    virtual int getLiczbaRuchow() = 0;

    ///
    /// @brief metoda zwraca aktualny status modelu układanki EStan
    ///
    /// @return aktualny status modelu układanki
    ///
    virtual EStan getStan() = 0;

    ///
    /// @brief metoda włącza lub wyłącza status ręcznego ustawiania rozmieszczenia elementów układanki
    ///
    /// @param[in] ustawianie jeśli true - ustawiany jest status EStan::ustawianie <br> jeśli false - ustawiany jest status EStan::wolny lub EStan::rozwiazany (jeśli rozmieszczenie na planszy jest rozwiązaniem)
    ///
    virtual void setReczneUstawianie(bool ustawianie) = 0;

    ///
    /// @brief metoda losowo rozmieszczająca elementy układanki
    ///
    virtual void wygenerujLosoweUstawienie() = 0;


    ///
    /// @brief metoda statyczna sprawdzająca czy wskazany ruch jest możliwy do wykonania na wskazanym rozstawieniu elementów układanki
    ///
    /// @param[in] nrPola numer pola planszy z którego ma zostać przesunięty element
    /// @param[in] stan referencja do wektora dwuwymiarowego przedstawiającego rozmieszczenie elementów na układance
    /// @return true jeśli ruch jest możliwy do wykonania na wskazanym rozstawieniu układanki
    ///
    static bool sprawdzRuch(int nrPola, CArray2D<int> &stan);

    ///
    /// @brief metoda statyczna wykonująca wskazany ruch na wskazanym przez referencję rozstawieniu elementów układanki i aktualizująca to rozstawienie
    ///
    /// @param[in] nrPola numer pola planszy z którego ma zostać przesunięty element
    /// @param[in,out] stan referencja do wektora dwuwymiarowego przedstawiającego rozmieszczenie elementów na układance
    /// @return nr pola na który został przesunięty wskazany do wykonania ruchu element <br>
    /// jeśli ruch nie był możliwy do wykonania zwracany jest nr pola wskazanego jako argument
    ///
    static int wykonajRuch(int nrPola, CArray2D<int> &stan);

    ///
    /// @brief metoda statyczna sprawdzająca czy przekazane przez argument rozstawienie elementów jest ustawieniem końcowym (rozwiązaniem)
    ///
    /// @param[in] stan referencja do wektora dwuwymiarowego przedstawiającego rozmieszczenie elementów na układance
    /// @return true - jeśli rozstawienie elementów na wskazanej planszy jest ustawieniem końcowym (rozwiązaniem)
    ///
    static bool czyUlozona(CArray2D<int> *stan);

    ///
    /// @brief metoda statyczna podająca ocenę wskazanego rozstawienia elementów układanki wg wskazanej heurystyki
    ///
    /// @param[in] stan wskaźnik na wektor dwuwymiarowy przedstawiający rozmieszczenie elementów na układance
    /// @param[in] heurystyka wskaźnik na obiekt heurystyki zawierający metodę wyliczającą ocenę
    /// @return wartość oceny - szacowania liczby ruchów potrzebnych do rozwiązania układanki
    ///
    static double podajOcene(CArray2D<int> *stan, CHeurystyka *heurystyka);

    ///
    /// @brief metoda statyczna zwracająca możliwe do wykonania ruchy we wskazanym rozstawieniu elementów układanki
    ///
    /// @param[in] stan wskaźnik na wektor dwuwymiarowy przedstawiający rozmieszczenie elementów na układance
    /// @return wektor liczb - nr pól z których można przesunąć element (czyli sąsiedztwo pola pustego)
    ///
    static std::vector<int> zwrocMozliweRuchy(CArray2D<int> *stan);
};

#endif // IUKLADANKA_H
