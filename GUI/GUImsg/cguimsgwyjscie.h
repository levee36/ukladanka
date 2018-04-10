#ifndef CGUIMSGWYJSCIE_H
#define CGUIMSGWYJSCIE_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik wybierze z menu pozycję Zamknij lub kliknie przycisk zamykania głównego okna (żadanie zakończenia pracy aplikacji)
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgWyjscie : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym
    ///
    CGUIMsgWyjscie();
};

#endif // CGUIMSGWYJSCIE_H
