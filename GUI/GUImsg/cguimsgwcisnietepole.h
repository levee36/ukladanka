#ifndef CGUIMSGWCISNIETEPOLE_H
#define CGUIMSGWCISNIETEPOLE_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik kliknął wybrane pole układanki
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgWcisnietePole : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym
    ///
    CGUIMsgWcisnietePole(int pole);

    ///
    /// @brief metoda zwracająca nr pola klikniętego przez użytkownika w gui
    ///
    /// @return nr pola klikniętego przez użytkownika w gui
    ///
    int getPole();
protected:
    int pole; ///< nr pola klikniętego przez użytkownika w gui
};

#endif // CGUIMSGWCISNIETEPOLE_H
