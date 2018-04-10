#ifndef CGUIMSGZADANIEKONFIGURACJI_H
#define CGUIMSGZADANIEKONFIGURACJI_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik wybierze z menu pozycję Ustawienia (żadanie wyświetlenia okna konfiguracyjnego)
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgZadanieKonfiguracji : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym
    ///
    CGUIMsgZadanieKonfiguracji();
};

#endif // CGUIMSGZADANIEKONFIGURACJI_H
