#ifndef CGUIMSGRESETUJ_H
#define CGUIMSGRESETUJ_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik wybierze z menu pozycję Resetuj (żadanie zresetowania ułożenia elementów układanki bez zmiany rozmiaru planszy)
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgResetuj : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym
    ///
    CGUIMsgResetuj();
};

#endif // CGUIMSGRESETUJ_H
