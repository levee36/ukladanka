#ifndef CGUIMSGUSTAWIANIERECZNE_H
#define CGUIMSGUSTAWIANIERECZNE_H

#include "cguimsg.h"


///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik wybierze z menu pozycję Ręczne ustawianie (włączenie lub wyłączenie stanu rozstawiania elementów układanki)
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsgUstawianieReczne : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym
    ///
    CGUIMsgUstawianieReczne(bool wlaczone);

    ///
    /// @brief metoda zwracająca aktualne zaznaczenie opcji Ręczne Ustawianie w gui
    ///
    /// @return aktualne zaznaczenie opcji Ręczne Ustawianie w gui (true - zaznaczone, false - brak zaznaczenia)
    ///
    bool getWlaczone();
protected:
    bool wlaczone; ///< aktualne zaznaczenie opcji Ręczne Ustawianie w gui
};

#endif // CGUIMSGUSTAWIANIERECZNE_H
