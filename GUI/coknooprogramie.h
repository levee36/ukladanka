#ifndef COKNOOPROGRAMIE_H
#define COKNOOPROGRAMIE_H

#include <QDialog>
#include <QLabel>
#include "Kontroler/ikontroler.h"
#include <map>
#include <string>

namespace Ui {
class COknoOprogramie;
}

///
/// @ingroup view
///
/// @brief
/// klasa gui realizująca okno modalne do wyświetlania informacji o programie, dziedziczy z klasy QDialog
///
/// @author Robert Płatkowski
/// @date 2018-04-10
///
class COknoOprogramie : public QDialog
{
    Q_OBJECT

public:
    ///
    /// @brief konstruktor obiektu okna o programie
    ///
    /// @details konstruktor inicjuje obiekt ui oraz
    /// ustawia teksty na etykietach tytuł, podtytuł i autor zgodnie z wartościami odpowiadającymi kluczom w mapie przekazanej jako parametr
    /// jeśli któryś z kluczy nie zostanie odnaleziony w mapie- nadawana jest wartość domyślna
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    /// @param[in] kontroler - wskaźnik na obiekt kontrolera - do ewentualnego przesyłania informacji o akcji uzytkownika za pomocą metody CKontroler::wyslijWiadomosc
    ///
    explicit COknoOprogramie(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent = 0);

    ///
    /// @brief destruktor
    ///
    /// @details niszczy obiekt ui
    ///
    ~COknoOprogramie();

private:
    Ui::COknoOprogramie *ui;
    IKontroler *kontroler;
};

#endif // COKNOOPROGRAMIE_H
