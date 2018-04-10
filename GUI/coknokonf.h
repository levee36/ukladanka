#ifndef COKNOKONF_H
#define COKNOKONF_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include "Kontroler/ikontroler.h"
#include <map>
#include <string>

namespace Ui {
class COknoKonf;
}

///
/// @ingroup view
///
/// @brief
/// klasa gui realizująca okno modalne do wyświetlania i ustawiania przez użytkownika parametrów aplikacji (rozmiar planszy), dziedziczy z klasy QDialog
///
/// @author Robert Płatkowski
/// @date 2018-04-10
///
class COknoKonf : public QDialog
{
    Q_OBJECT

public:
    ///
    /// @brief konstruktor obiektu okna konfiguracyjnego
    ///
    /// @details konstruktor inicjuje obiekt ui oraz
    /// ustawia tekst na etykietach opisujących spinboxy z liczbą kolumn i liczbą wierszy (podając możliwą do ustawienia wartość minimalną i maksymalną) i
    /// parametryzuje kontrolki spinbox ustawiając ich wartości minimalne i maksymalne oraz aktualne wartości
    /// wszystkie dane odczytyuwane są z mapy przekazanej jako parametr za pomocą wyszukiwania odpowiednich kluczy
    /// jesli klucz nie zostanie znaleziony - nadawana jest wartość domyślna
    ///
    /// @param[in] param mapa parametrów - zarówno klucz jak i wartość są zmiennymi łańcuchowymi
    /// @param[in] kontroler - wskaźnik na obiekt kontrolera - do ewentualnego przesyłania informacji o akcji uzytkownika za pomocą metody CKontroler::wyslijWiadomosc
    ///
    explicit COknoKonf(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent = 0);

    ///
    /// @brief destruktor
    ///
    /// @details niszczy obiekt ui
    ///
    ~COknoKonf();

private slots:
    void on_buttonBox_accepted(); ///< slot powiązany z sygnałem wysyłanym po wciśnięciu przycisku OK, wysyła za pomocą metody CKontroler::wyslijWiadomosc do kontrolera wiadomość określającą nowe ustawienia (CGUIMsgKonfiguracja)

private:
    Ui::COknoKonf *ui;
    IKontroler *kontroler;
    //wskaźniki na kontrolki modyfikowane przez konstruktor
    QLabel *label_ogrN;
    QLabel *label_ogrM;
    QSpinBox *spinBox_N;
    QSpinBox *spinBox_M;

    //ograniczenia dla ustawianego rozmiaru planszy
    int Nmin;
    int Nmax;
    int Mmin;
    int Mmax;
};

#endif // COKNOKONF_H
