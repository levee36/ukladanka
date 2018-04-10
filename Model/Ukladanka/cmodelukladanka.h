#ifndef CMODELUKLADANKA_H
#define CMODELUKLADANKA_H

#include "iukladanka.h"
#include "heurystyki/cheurystyka.h"
#include <array>
#include <QTime>

///
/// @defgroup model Model
///
/// @brief
/// Klasy realizujące wzorzec architektoniczny Model
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///


///
/// @ingroup model
/// @brief
/// klasa realizująca model układanki
/// @details
/// klasa przechowuje aktualny układ elementów układanki (planszę) w obiekcie klasy CArray2D <br>
/// oraz aktualny status w zmiennej typu wyliczeniowego EStan <br>
/// klasa zawiera metody statyczne umożliwiające operacje na dowolnym układzie elementów przekazanym jako argument metody <br>
/// metody statyczne są przeciążone - mają swoją odmianę działającą na planszy przechowywanej w instancji <br>
/// klasa przechowuje i umożliwia odczyt statystyk (czas ułożenia, liczba ruchów) <br>
/// część metod statycznych jest częścią realizacji algorytmu przeszukiwania A* - funkcja oceny, generator stanów-następników <br>
/// metody wykorzystywane przez kontroler umieszczone zostały w interfejsie IUkladanka <br>
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///
class CModelUkladanka : public IUkladanka
{
public:
    ///
    /// @brief konstruktor ustawiający rozmiar planszy <br>
    /// wszystkie elementy planszy zostaną wyzerowane
    ///
    /// @param[in] N liczba kolumn
    /// @param[in] M liczba wierszy
    ///
    CModelUkladanka(int N, int M);

    ///
    /// @brief konstruktor ustawiający rozmiar planszy i przypisujący przekazane rozmieszczenie elementów
    ///
    /// @param[in] N liczba kolumn
    /// @param[in] M liczba wierszy
    /// @param[in] tbl wektor liczb int określających kolejne numery elementów do umieszczenia na planszy <br>
    /// (w odczycie liniowym poczynając od elementu (0,0))
    /// jeśli wektor tbl zawiera mniej elementów niż rozmiar planszy N*M, pozostałe elementy zostaną wyzerowane
    /// jeśli wektor tbl zawiera więcej elementów niż rozmiar planszy N*M, pozostałe elementy zostaną pominięte
    ///
    CModelUkladanka(std::vector<int> tbl, int N, int M);

    ///
    /// @brief metoda resetująca model układanki - ustawiająca nową planszę o podanym rozmiarze z ułożeniem końcowym (rozwiązaniem)
    ///
    /// @param[in] N nowa liczba kolumn
    /// @param[in] M nowa liczba wierszy
    /// @return zwraca wartość true gdy reset planszy się powiódł
    ///
    bool resetuj(int N, int M);

    ///
    /// @brief metoda zwracająca wskaźnik na obiekt planszy przechowywany w modelu
    ///
    /// @return wskaźnik na obiekt planszy przechowywany w modelu
    ///
    CArray2D<int> *getPlansza();

    ///
    /// @brief metoda podmieniająca obiekt planszy w modelu układanki na wskazany przez wskaźnik przekazany jako argument
    ///
    /// @param[in] plansza wskaźnik na obiekt planszy do ustawienia w modelu układanki
    ///
    void setPlansza(CArray2D<int>* plansza);

    ///
    /// @brief metoda ustawiająca elementy planszy zgodnie z podanym wektorem liczb
    ///
    /// @details metoda numeruje kolejne elementy układanki według numeracji przekazanej w postaci wektora liczb <br>
    /// (przy odczycie liniowym planszy wierszami poczynając od elementu (0,0))
    ///
    /// @param[in] tbl wektor liczb int określających kolejne numery elementów do umieszczenia na planszy <br>
    /// (w odczycie liniowym poczynając od elementu (0,0))
    /// jeśli wektor tbl zawiera mniej elementów niż rozmiar planszy N*M, pozostałe elementy zostaną wyzerowane
    /// jeśli wektor tbl zawiera więcej elementów niż rozmiar planszy N*M, pozostałe elementy zostaną pominięte
    ///
    void setPlansza(std::vector<int> tbl);

    ///
    /// @brief metoda sprawdzająca czy wskazany ruch jest możliwy do wykonania
    ///
    /// @details ruch jest wskazywany przez podanie numeru pola planszy z którego ma zostać przesunięty element <br>
    /// ruch jest możliwy do wykonania, gdy: <br>
    ///  - na wskazanym polu znajduje się element układanki (nie jest to pole puste) <br>
    ///  - w sąsiedztwie pola (góra,dół,lewo,prawo) znajduje się pole puste <br>
    ///
    /// @param[in] nrPola numer pola planszy z którego ma zostać przesunięty element
    /// @return true jeśli ruch jest możliwy do wykonania
    ///
    bool sprawdzRuch(int nrPola);

    ///
    /// @brief metoda wykonująca wskazany ruch i aktualizująca rozstawienie na planszy
    ///
    /// @details ruch jest wskazywany przez podanie numeru pola planszy z którego ma zostać przesunięty element <br>
    /// ruch jest możliwy do wykonania, gdy: <br>
    ///  - na wskazanym polu znajduje się element układanki (nie jest to pole puste) <br>
    ///  - w sąsiedztwie pola (góra,dół,lewo,prawo) znajduje się pole puste <br>
    /// Jeśli ruch jest możliwy do wykonania metoda wykonuje ten ruch przez aktualizację rozstawienia elementów układanki <br>
    /// Dodatkowo aktualizowana jest zmienna prywatna obiektu pamiętająca ostatni wykonany ruch
    ///
    /// @param[in] nrPola numer pola planszy z którego ma zostać przesunięty element
    /// @return nr pola na który został przesunięty wskazany do wykonania ruchu element <br>
    /// jeśli ruch nie był możliwy do wykonania zwracany jest nr pola wskazanego jako argument
    ///
    int wykonajRuch(int nrPola);

    ///
    /// @brief metoda zwracająca ostatni wykonany ruch na planszy (w postaci pary wartości - nr pola z którego przesunięto element i nr pola na który przesunięto element)
    ///
    /// @return para liczb - nr pola z którego przesunięto element i nr pola na który przesunięto element
    ///
    std::array<int,2> getOstatniRuch();

    ///
    /// @brief metoda sprawdzająca czy rozstawienie elementów na planszy jest ustawieniem końcowym (rozwiązaniem)
    ///
    /// @details metoda zwraca informację opartą na aktualnym statusie modelu
    ///
    /// @return true - jeśli rozstawienie elementów na planszy jest ustawieniem końcowym (rozwiązaniem)
    ///
    bool czyUlozona();

    ///
    /// @brief metoda zwracająca aktualny czas rozwiązywania układanki lub czas rozwiązania układanki
    ///
    /// @details metoda zwraca aktualny czas rozwiązywania, gdy status modelu układanki to EStan::rozwiazywany <br>
    /// metoda zwraca końcowy czas rozwiązania, gdy status modelu układanki to EStan::rozwiazany
    ///
    /// @return liczba milisekund - czas rozwiązywania (jeśli nadal trwa) lub końcowy czas rozwiązania (jeśli układanka zostałą rozwiązana)
    ///
    int getCzas();

    ///
    /// @brief metoda zwracająca liczbę wykonanych ruchów w czasie rozwiązywania układanki
    ///
    /// @details metoda zwraca liczbę wykonanych ruchów, gdy status modelu układanki to EStan::rozwiazywany lub EStan::rozwiazany <br>
    /// w pozostałych statusach zwraca 0
    ///
    /// @return liczba wykonanych ruchów
    ///
    int getLiczbaRuchow();

    ///
    /// @brief metoda zwraca aktualny status modelu układanki EStan
    ///
    /// @return aktualny status modelu układanki
    ///
    EStan getStan();

    ///
    /// @brief metoda włącza lub wyłącza status ręcznego ustawiania rozmieszczenia elementów układanki
    ///
    /// @param[in] ustawianie jeśli true - ustawiany jest status EStan::ustawianie <br> jeśli false - ustawiany jest status EStan::wolny lub EStan::rozwiazany (jeśli rozmieszczenie na planszy jest rozwiązaniem)
    ///
    void setReczneUstawianie(bool ustawianie);

    ///
    /// @brief metoda losowo rozmieszczająca elementy układanki
    ///
    /// @details losowe rozmieszczenie elementów ukłądanki polega na wykonaniu parzystej liczby zamian sąsiednich elementów układanki (tylko parzysta liczba takich zamian gwearantuje, że układ jest rozwiązywalny) <br>
    /// Elementy są zamieniane korzystając z liniowej reprezentacji planszy (w postaci wektora). Ostatni element nie jest modyfikowany - jest przypisany do elementu pustego (tak by pusty element zawsze znajdował się w prawym dolnym rogu układanki) <br>
    /// Liczba losowań jest równa liczbie elementów układanki (zaokrąglonej do najbliższej liczby parzystej) <br>
    /// Do generowania liczb pseudolosowych wykorzystano metodę statyczną bounded klasy QRandomGenerator
    ///
    void wygenerujLosoweUstawienie();


    ///
    /// @brief metoda statyczna sprawdzająca czy wskazany ruch jest możliwy do wykonania na wskazanym rozstawieniu elementów układanki
    ///
    /// @details ruch jest wskazywany przez podanie numeru pola planszy z którego ma zostać przesunięty element <br>
    /// ruch jest możliwy do wykonania, gdy: <br>
    ///  - na wskazanym polu znajduje się element układanki (nie jest to pole puste) <br>
    ///  - w sąsiedztwie pola (góra,dół,lewo,prawo) znajduje się pole puste <br>
    ///
    /// @param[in] nrPola numer pola planszy z którego ma zostać przesunięty element
    /// @param[in] stan wektor dwuwymiarowy przedstawiający rozmieszczenie elementów na układance
    /// @return true jeśli ruch jest możliwy do wykonania na wskazanym rozstawieniu układanki
    ///
    static bool sprawdzRuch(int nrPola, CArray2D<int> &stan);

    ///
    /// @brief metoda statyczna wykonująca wskazany ruch na wskazanym przez referencję rozstawieniu elementów układanki i aktualizująca to rozstawienie
    ///
    /// @details ruch jest wskazywany przez podanie numeru pola planszy z którego ma zostać przesunięty element <br>
    /// ruch jest możliwy do wykonania, gdy: <br>
    ///  - na wskazanym polu znajduje się element układanki (nie jest to pole puste) <br>
    ///  - w sąsiedztwie pola (góra,dół,lewo,prawo) znajduje się pole puste <br>
    /// Jeśli ruch jest możliwy do wykonania metoda wykonuje ten ruch przez aktualizację rozstawienia elementów układanki wskazanego przez referencję <br>
    ///
    /// @param[in] nrPola numer pola planszy z którego ma zostać przesunięty element
    /// @param[in,out] stan wektor dwuwymiarowy przedstawiający rozmieszczenie elementów na układance
    /// @return nr pola na który został przesunięty wskazany do wykonania ruchu element <br>
    /// jeśli ruch nie był możliwy do wykonania zwracany jest nr pola wskazanego jako argument
    ///
    static int wykonajRuch(int nrPola, CArray2D<int> &stan);

    ///
    /// @brief metoda statyczna sprawdzająca czy przekazane przez argument rozstawienie elementów jest ustawieniem końcowym (rozwiązaniem)
    ///
    /// @details metoda zwraca informację sprawdzając czy każdy element znajduje się na polu mu odpowiadającym
    ///
    /// @param[in] stan wskaźnik na wektor dwuwymiarowy przedstawiający rozmieszczenie elementów na układance
    /// @return true - jeśli rozstawienie elementów na wskazanej planszy jest ustawieniem końcowym (rozwiązaniem)
    ///
    static bool czyUlozona(CArray2D<int> *stan);

    ///
    /// @brief metoda statyczna podająca ocenę wskazanego rozstawienia elementów układanki wg wskazanej heurystyki
    ///
    /// @details metoda uruchamia metodę CHeurystyka::policzOcene wskazanego obiektu heurytyski
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

private:
    EStan stan;
    int N;
    int M;
    CArray2D<int> *plansza;
    std::array<int,2> ostatniRuch;
    QTime *timer;
    int licznikRuchow;
    int czasUlozenia;
};

#endif // CMODELUKLADANKA_H
