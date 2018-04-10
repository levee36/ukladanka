#ifndef IKONTROLER_H
#define IKONTROLER_H

#include "GUI\GUImsg\cguimsg.h"

///
/// @ingroup controller
/// @brief
/// interfejs klasy CKontroler do komunikacji z gui - klasą COknoGlowne
/// @details
/// interfejs zawiera metodę umozliwiającą przesyłanie z gui do kontrolera informacji o akcjach użytkownika
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///
class IKontroler
{

public:
    ///
    /// @brief metoda przesyłająca z gui do kontrolera obiekt z hierarchii klas wyprowadzonej z klasy bazowej CGUIMsg
    ///
    /// @param[in] wiadomosc wskaźnik na obiekt z hierarchii klas wyprowadzonej z klasy bazowej CGUIMsg
    ///
    virtual void wyslijWiadomosc(CGUIMsg *wiadomosc) = 0;
};

#endif // IKONTROLER_H
