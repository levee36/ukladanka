#ifndef CGUIMSGOPROGRAMIE_H
#define CGUIMSGOPROGRAMIE_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik wybierze z menu pozycję O programie (żadanie wyświetlenia okna z informacjami o programie)
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgOprogramie : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym
    ///
    CGUIMsgOprogramie();
};


#endif // CGUIMSGOPROGRAMIE_H
