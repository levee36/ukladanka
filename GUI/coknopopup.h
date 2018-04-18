#ifndef COKNOPOPUP_H
#define COKNOPOPUP_H

#include <QDialog>
#include <QLabel>
#include <QCloseEvent>
#include "Kontroler/ikontroler.h"
#include <map>
#include <string>

namespace Ui {
class COknoPopup;
}

///
/// @ingroup view
///
/// @brief
/// klasa gui realizująca okno modalne do wyświetlania krótkich wiadomości (rozwiązanie, działanie algorytmu przeszukującego), dziedziczy z klasy QDialog
///
/// @author Robert Płatkowski
/// @date 2018-04-10
///
class COknoPopup : public QDialog
{
    Q_OBJECT

public:
    ///
    /// @brief konstruktor obiektu okna popup z krótką wiadomością
    ///
    /// @details konstruktor inicjuje obiekt ui oraz ustawia: <br>
    /// - tytuł okna <br>
    /// - treść wyświetlanej na etykiecie wiadomości <br>
    /// - tekst na przycisku <br>
    /// powyższe dane pobierane są z przekazanego jako parametr słownika-mapy przez szukanie odpowiednich kluczy (tytul,tresc,przycisk)
    /// jeśli któryś z kluczy nie zostanie odnaleziony w mapie- nadawana jest wartość domyślna
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    /// @param[in] kontroler - wskaźnik na obiekt kontrolera - do ewentualnego przesyłania informacji o akcji uzytkownika za pomocą metody CKontroler::wyslijWiadomosc
    ///
    explicit COknoPopup(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent = 0);

    ///
    /// @brief destruktor
    ///
    /// @details niszczy obiekt ui
    ///
    ~COknoPopup();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

signals:
    void zamykany(); ///< sygnał emitowany po wywołaniu zdarzenia zamykania okna (do komunikowania tego faktu oknu głównemu COknoGlowne)


private:
    Ui::COknoPopup *ui;
    IKontroler *kontroler;
    void closeEvent(QCloseEvent *event);
};

#endif // COKNOPOPUP_H
