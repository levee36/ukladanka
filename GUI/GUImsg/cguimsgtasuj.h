#ifndef CGUIMSGTASUJ_H
#define CGUIMSGTASUJ_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik wybierze z menu pozycję Tasuj (żadanie losowego rozmieszczenia elementów układanki bez zmiany rozmiaru planszy)
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgTasuj : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym
    ///
    CGUIMsgTasuj();
};

#endif // CGUIMSGTASUJ_H
