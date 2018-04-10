#ifndef CGUIMSG_H
#define CGUIMSG_H

#include <string>

///
/// @defgroup msg GUImsg
/// @ingroup view
///
/// @brief
/// Hierarchia klas do przekazywania z gui do kontrolera informacji o akcjach użytkownika
/// główna instrukcja kontrolera identyfikuje akcję użytkownika dzięki dynamicznemu rzutowaniu otrzymanego obiektu z tej hierarchii na poszczególne klasy pochodne
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///

///
/// @ingroup msg
/// @brief
/// klasa abstrakcyjna - bazowa klasa dla hierarchii wiadomości z gui
///
/// @author Robert Płatkowski
/// @date 2018-04-09
///
class CGUIMsg
{

public:
    ///
    /// @brief konstruktor ustawiający nazwę-opis typu wiadomości w polu opisowym
    ///
    /// @param[in] nazwa nazwa-opis typu wiadomości
    ///
    CGUIMsg(std::string opis);

    ///
    /// @brief metoda zwracająca nazwę-opis typu wiadomości
    ///
    /// @return nazwa-opis typu wiadomości reprezentowanej przez klasę
    ///
    virtual std::string getOpis();

protected:
    std::string opis; ///< nazwa-opis typu wiadomości
};

#endif // CGUIMSG_H
