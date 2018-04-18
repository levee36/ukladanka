#ifndef IALGORYTM_H
#define IALGORYTM_H

#include "Model/Algorytm/cwezel.h"
#include <vector>

///
/// @ingroup algorytm
/// @brief
/// interfejs klasy CAlgorytmAStar na potrzeby klasy CKontroler
/// @details
/// interfejs zawiera metody zrealizowane w klasie CAlgorytmAStar na potrzeby klasy CKontroler
///
/// @author Robert Płatkowski
/// @date 2018-04-11
///
class IAlgorytm
{

public:
    ///
    /// @brief metoda resetująca model układanki - ustawiająca nową planszę o podanym rozmiarze z ułożeniem końcowym (rozwiązaniem)
    ///
    /// @details metoda wykonuje jeden krok algorytmu (przejrzenie następników aktualnego węzła i wybór najlepszego pod względem oceny) <br>
    /// na koniec sprawdzany jest stan układanki – jeśli jest ułożona, zwracana jest wartość true
    ///
    /// @return zwraca wartość true gdy po wykonaniu kroku algorytmu układanka jest ułożona
    ///
    virtual bool wykonajKrokAlgorytmu() = 0;

    ///
    /// @brief metoda zwracająca ścieżkę od węzła startowego do aktualnego w postaci wektora wskaźników na kolejno odwiedzane węzły
    ///
    /// @details metoda zwracająca ścieżkę od węzła startowego do aktualnego w postaci wektora wskaźników na kolejno odwiedzane węzły
    /// gdy węzeł końcowy jest rozwiązaniem ukłądanki - zwrócona ścieżka jest szukaną drogą
    ///
    /// @return ścieżka od węzła startowego do aktualnego w postaci wektora liczb określających nr pól kolejnych ruchów (kolejność od węzła końcowego do początkowego)
    ///
    virtual std::vector<int> zwrocSciezke() = 0;

    ///
    /// @brief metoda zwracająca liczbę dotychczas odwiedzonych węzłów grafu przeszukiwań (liczność zbioru CLOSED)
    ///
    /// @return liczba dotychczas odwiedzonych węzłów grafu przeszukiwań (liczność zbioru CLOSED)
    ///
    virtual int getLiczbaOdwiedzonych() = 0;

    ///
    /// @brief metoda ustawiająca heurystykę wykorzystywaną przy szacowaniu oceny wezłów
    ///
    /// @param[in] heurystyka wskaźnik na obiekt heurystyki zawierający metodę wyliczającą ocenę
    ///
    virtual void setHeurystyka(CHeurystyka *heurystyka) = 0;

    ///
    /// @brief metoda zwracająca wskaźnik na obiekt heurystyki wykorzystywanej przy szacowaniu oceny wezłów
    ///
    /// @return wskaźnik na obiekt heurystyki zawierający metodę wyliczającą ocenę
    ///
    virtual CHeurystyka* getHeurystyka() = 0;

    ///
    /// @brief metoda resetująca obiekt - czyszcząca zbiory OPEN i CLOSED, zerująca wskaźnik na aktualny węzeł oraz zerująca statystyki
    ///
    virtual void wyczysc() = 0;


    virtual double getAktHeur()=0;

};


#endif // IALGORYTM_H
