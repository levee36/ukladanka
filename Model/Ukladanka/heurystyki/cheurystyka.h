#ifndef CHEURYSTYKA_H
#define CHEURYSTYKA_H

#include <string>
#include "Model/Ukladanka/carray2d.h"

///
/// @defgroup heurystyki Heurystyki
/// @ingroup model
///
/// @brief
/// Hierarchia klas realizujących różne heurystyki - funkcje szacowania liczby ruchów potrzebnych do rozwiązania układanki
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///


///
/// @ingroup heurystyki
/// @brief
/// klasa abstrakcyjna - bazowa klasa dla klas realizujących konkretne funkcje heurystyk
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///
class CHeurystyka
{
public:
    ///
    /// @brief konstruktor ustawiający nazwę heurystyki w polu opisowym
    ///
    /// @param nazwa nazwa funkcji heurystyki realizowanej przez klasę
    ///
    CHeurystyka(std::string nazwa);

    ///
    /// @brief metoda wyliczająca wartość heurystyki dla wskazanego rozstawienia elementów układanki
    ///
    /// @param stan wskaźnik na wektor dwuwymiarowy przedstawiający rozmieszczenie elementów na układance
    ///
    virtual double policzOcene(CArray2D<int> *stan) = 0;

    ///
    /// @brief metoda zwracająca nazwę funkcji heurystyki realizowanej przez klasę
    ///
    /// @return nazwa funkcji heurystyki realizowanej przez klasę
    ///
    std::string getNazwa();

protected:
    std::string nazwa;
};

#endif // CHEURYSTYKA_H

