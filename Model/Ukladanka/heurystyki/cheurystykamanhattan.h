#ifndef CHEURYSTYKAMANHATTAN_H
#define CHEURYSTYKAMANHATTAN_H

#include "cheurystyka.h"

///
/// @ingroup heurystyki
/// @brief
/// klasa realizująca heurystykę opartą na sumie odległości (w metryce miejskiej) każdego elementu układanki od jego domyślnej pozycji
///
/// @details wartośc tej funkcji heurystyki jest równa sumie odległości (w metryce miejskiej) każdego elementu układanki od jego domyślnej pozycji (nie uwzględniając połozenia pola pustego)
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///
class CHeurystykaManhattan : public CHeurystyka
{
public:
    ///
    /// @brief konstruktor ustawiający nazwę heurystyki w polu opisowym
    ///
    CHeurystykaManhattan();

    ///
    /// @brief metoda wyliczająca wartość heurystyki dla wskazanego rozstawienia elementów układanki
    ///
    /// @param[in] stan wskaźnik na wektor dwuwymiarowy przedstawiający rozmieszczenie elementów na układance
    /// @return suma odległości (w metryce miejskiej) każdego elementu układanki od jego domyślnej pozycji (nie uwzględniając połozenia pola pustego)
    ///
    double policzOcene(CArray2D<int> *stan);
protected:
    double odleglosc(size_t t1, size_t t2, size_t N);
    double odleglosc(size_t n1, size_t m1, size_t n2, size_t m2);
};

#endif // CHEURYSTYKAMANHATTAN_H
