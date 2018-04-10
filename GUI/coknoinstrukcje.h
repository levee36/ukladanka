#ifndef COKNOINSTRUKCJE_H
#define COKNOINSTRUKCJE_H

#include <QDialog>
#include <QLabel>
#include "Kontroler/ikontroler.h"
#include <map>
#include <string>

namespace Ui {
class COknoInstrukcje;
}

///
/// @ingroup view
///
/// @brief
/// klasa gui realizująca okno modalne do wyświetlania instrukcji, dziedziczy z klasy QDialog
///
/// @author Robert Płatkowski
/// @date 2018-04-10
///
class COknoInstrukcje : public QDialog
{
    Q_OBJECT

public:
    ///
    /// @brief konstruktor obiektu okna z instrukcjami
    ///
    /// @details konstruktor inicjuje obiekt ui oraz ustawia na etykiecie tekst przekazany w słowniku/mapie dla klucza instrukcje, jeśli brak takiego klucza, to ustawiany jest tekst domyślny
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    /// @param[in] kontroler - wskaźnik na obiekt kontrolera - do ewentualnego przesyłania informacji o akcji uzytkownika za pomocą metody CKontroler::wyslijWiadomosc
    ///
    explicit COknoInstrukcje(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent = 0);


    ///
    /// @brief destruktor
    ///
    /// @details niszczy obiekt ui
    ///
    ~COknoInstrukcje();

private:
    Ui::COknoInstrukcje *ui;
    IKontroler *kontroler;
    //wskaźniki na kontrolki modyfikowane przez konstruktor
    QLabel *label_tekst;
};

#endif // COKNOINSTRUKCJE_H
