#ifndef CWEZELCOMPARE_H
#define CWEZELCOMPARE_H

#include "Model/Algorytm/cwezel.h"

///
/// @ingroup algorytm
/// @brief
/// struktura z przeciążonym operatorem () służącym do porównywania obiektów klasy CWezel
///
/// @details struktura z przeciążonym operatorem () służącym do porównywania obiektów klasy CWezel <br>
/// porównywanie obiektów CWezel polega na porównywaniu nr elementów z kolejnych pól planszy - za obiekt mniejszy uznawany jest ten, który: <br>
/// 1. na i-tym polu ma element o mniejszym nr niż drugi obiekt (gdzie i = 0,...,N*M-1) <br>
/// 2. na polach o nr 0,...,i-1 numery elementów w obydwu obiektach są identyczne <br>
///
/// @author Robert Płatkowski
/// @date 2018-04-12
///
struct CWezelCompare
{
public:
    ///
    /// @brief przeciążony operator () służący do porównywania obiektów klasy CWezel - zwraca true, gdy lewy operand jest mniejszy od prawego
    ///
    /// @details porównywanie obiektów CWezel polega na porównywaniu nr elementów z kolejnych pól planszy - za obiekt mniejszy uznawany jest ten, który: <br>
    /// 1. na i-tym polu ma element o mniejszym nr niż drugi obiekt (gdzie i = 0,...,N*M-1) <br>
    /// 2. na polach o nr 0,...,i-1 numery elementów w obydwu obiektach są identyczne <br>
    /// oba obiekty pwoinny mieć ten sam rozmiar planszy (N i M)
    /// w przypadku różnych rozmiarów porównanie jest również wykonywane - ale wynik nie ma rozsądnego zastosowania <br>
    /// Porównanie polega na porównywaniu w pętli kolejno odczytanych (odczyt liniowy) nr elementów - w przypadku, gdy elementy się różnią i:
    /// - operand lewy ma mniejszy nr elementu - zwracana jest wartość true (lewy operand jest mniejszy od prawego)
    /// - operand prawy ma mniejszy nr elementu - zwracana jest wartość false (lewy operand jest większy od prawego)
    /// Jeśli wszystkie nr elementów się zgadzają - zwracana jest wartość false (operandy są równe)
    ///
    /// @return true, jeśli lewyOperand jest mniejszy od prawyOperand
    ///
    bool operator() (CWezel *lewyOperand, CWezel *prawyOperand) const;
};

#endif // CWEZELCOMPARE_H
