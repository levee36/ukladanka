#ifndef CGUIMSGKONFIGURACJA_H
#define CGUIMSGKONFIGURACJA_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik ustawi parametry w oknie konfiguracyjnym i potwierdzi je wciskając przycisk OK
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgKonfiguracja : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym oraz ustawiający przekazywany wymiar planszy
    ///
    /// @param[in] N wybrana przez użytkownika liczba kolumn
    /// @param[in] M wybrana przez użytkownika liczba wierszy
    ///
    CGUIMsgKonfiguracja(int N, int M);

    ///
    /// @brief metoda zwracająca wybraną przez użytkownika liczbę kolumn
    ///
    /// @return wybrana przez użytkownika liczba kolumn
    ///
    int getN();

    ///
    /// @brief metoda zwracająca wybraną przez użytkownika liczbę wierszy
    ///
    /// @return wybrana przez użytkownika liczba wierszy
    ///
    int getM();

protected:
    int N; ///< wybrana przez użytkownika liczba kolumn
    int M; ///< wybrana przez użytkownika liczba wierszy
};

#endif // CGUIMSGKONFIGURACJA_H
