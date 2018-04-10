#ifndef CGUIMSGINSTRUKCJA_H
#define CGUIMSGINSTRUKCJA_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik wybierze z menu pozycję Instrukcje (żadanie wyświetlenia okna z instrukcjami)
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgInstrukcja : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym
    ///
    CGUIMsgInstrukcja();
};

#endif // CGUIMSGINSTRUKCJA_H
