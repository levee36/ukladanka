#ifndef CHEURYSTYKALICZBAROZNIC_H
#define CHEURYSTYKALICZBAROZNIC_H

#include "cheurystyka.h"

///
/// @ingroup heurystyki
/// @brief
/// klasa realizująca heurystykę opartą na liczbie elementów znajdujących się na niewłaściwej pozycji
///
/// @details wartośc tej funkcji heurystyki jest równa liczbie elementów układanki, które znajdują się na niewłaściwych pozycjach (nie uwzględniając połozenia pola pustego)
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///
class CHeurystykaLiczbaRoznic : public CHeurystyka
{
public:
    ///
    /// @brief konstruktor ustawiający nazwę heurystyki w polu opisowym
    ///
    CHeurystykaLiczbaRoznic();

    ///
    /// @brief metoda wyliczająca wartość heurystyki dla wskazanego rozstawienia elementów układanki
    ///
    /// @param[in] stan wskaźnik na wektor dwuwymiarowy przedstawiający rozmieszczenie elementów na układance
    /// @return liczba elementów układanki, które znajdują się na niewłaściwych pozycjach (nie uwzględniając połozenia pola pustego)
    ///
    double policzOcene(CArray2D<int> *stan);
};

#endif // CHEURYSTYKALICZBAROZNIC_H
