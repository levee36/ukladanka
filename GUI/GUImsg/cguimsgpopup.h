#ifndef CGUIMSGPOPUP_H
#define CGUIMSGPOPUP_H

#include "cguimsg.h"

///
/// @ingroup msg
/// @brief
/// klasa realizująca typ wiadomości przesyłany z gui do kontrolera w sytuacji, gdy użytkownik zamknie okno COknoPopup
///
/// @author Robert Płatkowski
/// @date 2018-04-14
///
class CGUIMsgPopup : public CGUIMsg {

public:
    ///
    /// @brief konstruktor ustawiający nazwę typu wiadomości w polu opisowym oraz przekazujący tekst z przycisku (służy do identyfikacji rodzaju wiadomości wyświetlonej w okienku)
    ///
    /// @param[in] przycisk tekst z przycisku
    ///
    CGUIMsgPopup(std::string przycisk);

    ///
    /// @brief metoda zwracająca tekst z przycisku OK okienka popup (na tej podstawie kontroler identyfikuje rodzaj wiadomości wyświetlonej w okienku)
    ///
    /// @return tekst z przycisku OK okienka popup
    ///
    std::string getPrzycisk();

private:
    std::string przycisk;
};

#endif // CGUIMSGPOPUP_H
