#ifndef CGUIMSGROZWIAZ_H
#define CGUIMSGROZWIAZ_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik wybierze z menu pozycję Rozwiąż (żadanie uruchomienia algorytmu rozwiązującego aktualny stan układanki)
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgRozwiaz : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym
    ///
    CGUIMsgRozwiaz();
};

#endif // CGUIMSGROZWIAZ_H
