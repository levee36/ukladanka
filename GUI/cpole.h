#ifndef CPOLE_H
#define CPOLE_H

#include <QPushButton>

///
/// @ingroup view
///
/// @brief
/// klasa gui realizująca kontrolkę(widget) reprezentującą pojedynczy element układanki, dziedziczy z klasy QPushButton
///
/// @details klasa stanowi rozszerzenie klasy QPushButton przez dodanie pól do pamiętania własnej pozycji (nr pola w odczycie liniowym planszy) oraz własnego nr elementu
/// oraz metod umożliwiających odczyt tych danych oraz zmianę wartości nr elementu (pozycja nie może być zmieniona)
///
/// @author Robert Płatkowski
/// @date 2018-04-10
///
class CPole : public QPushButton
{
public:
    ///
    /// @brief konstruktor kontrolki reprezentującej element układanki
    ///
    /// @details konstruktor tworzy obiekt elementu układanki jako zwykły przycisk QPushButton
    /// zapamiętuje przekazaną przez parametry konstruktora pozycję na planszy (w odczycie liniowym planszy wierszami poczynając od elementu (0,0))
    /// oraz ustawia numer elementu znajdujący się an tej pozycji i wyświetlany w postaci tekstu na tym przycisku za pomocą metody setNumer <br>
    /// jeśli numer jest równy 0 - przycisk nie jest widoczny (visible=false), co symuluje puste pole układanki <br>
    /// jeśli numer jest równy -1 - przycisk jest wyświetlany, ale jest zablokowany (enabled = false), co symuluje nieaktywne pole układanki (dla plansz nie będących prostokątami jest to pole "brzegu") <br>
    ///
    /// @param[in] pozycja pozycja na planszy (w odczycie liniowym planszy wierszami poczynając od elementu (0,0))
    /// @param[in] numer numer elementu znajdujący się na tej pozycji i wyświetlany w postaci tekstu na tym przycisku
    ///
    CPole(int pozycja, int numer);

    ///
    /// @brief metoda ustawiająca numer elementu znajdującego się w tym polu
    ///
    /// @details zapamiętuje przekazaną przez parametr wartość w polu numer oraz na jej podstawie zarządza widocznością i dostępnością przycisku
    /// w tym celu wykorzystywana jest metoda CPole::getNumer do odczytu nr elementu w danym polu <br>
    /// jeśli numer jest równy 0 - przycisk nie jest widoczny (visible=false), co symuluje puste pole układanki
    /// jeśli numer jest równy -1 - przycisk jest wyświetlany, ale jest zablokowany (enabled = false), co symuluje nieaktywne pole układanki (dla plansz nie będących prostokątami jest to pole "brzegu")
    /// jeśli numer jest większy od 0 - przycisk jest wyświetlany i jest dostępny, tekst wyświetlany na nim odpowiada przekazanemu numerowi
    ///
    /// @param[in] numer numer elementu znajdujący się na tej pozycji i wyświetlany w postaci tekstu na tym przycisku
    ///
    void setNumer(int numer);

    ///
    /// @brief metoda zwracająca numer elementu znajdujący się w tym polu układanki
    ///
    /// @return numer elementu znajdujący się w tym polu
    ///
    int getNumer();

    ///
    /// @brief metoda zwracająca pozycję tego pola na planszy (w odczycie liniowym planszy wierszami poczynając od elementu (0,0))
    ///
    /// @return pozycję tego pola na planszy (w odczycie liniowym planszy wierszami poczynając od elementu (0,0))
    ///
    int getPozycja();
private:
    int pozycja;
    int numer;

};

#endif // CPOLE_H
