#ifndef CWATEKALGORYTM_H
#define CWATEKALGORYTM_H

#include <QThread>
#include <QMutex>
#include "ialgorytm.h"


///
/// @ingroup algorytm
/// @brief
/// Klasa pochodna QThread - do zarządzania wątkiem pobocznym do wykonywania algorytmu przeszukiwania w tle (by nie zamrażać wątku głównego odpowiedzialnego za gui)
///
/// @details
/// Klasa pochodna QThread - do zarządzania wątkiem pobocznym do wykonywania algorytmu przeszukiwania w tle. <br>
/// Klasa zarządza wątkiem, w którym wykonywany jest algorytm A*. <br>
///
///
/// @author Robert Płatkowski
/// @date 2018-04-16
///
class CWatekAlgorytm : public QThread
{
    Q_OBJECT
public:
    ///
    /// @brief konstruktor - tworzy standardowy obiekt klasy bazowej
    ///
    CWatekAlgorytm();

    ///
    /// @brief destruktor
    ///
    ~CWatekAlgorytm();

    ///
    /// @brief metoda wywoływana z wątku głównego, ustawiająca flagę przerwanie - umożliwiającą przerwanie działania algorytmu
    ///
    void przerwij();

    ///
    /// @brief metoda ustawiająca wskaźnik do obiektu algorytmu
    ///
    /// @details obiekt algorytmu - metody realizujące algorytm przeszukiwania są uruchamiane wewnątrz Watku pobocznego sterowanego przez tę klasę
    ///
    /// @param[in] algorytm wskaźnik do obiektu algorytmu (obiekt klasy CAlgorytmAStar poprzez interfejs IAlgorytm)
    ///
    void setAlgorytm(IAlgorytm *algorytm);

    ///
    /// @brief metoda zwracająca wskaźnik na obiekt algorytmu (obiekt klasy CAlgorytmAStar poprzez interfejs IAlgorytm)
    ///
    /// @return wskaźnik na obiekt algorytmu (obiekt klasy CAlgorytmAStar poprzez interfejs IAlgorytm)
    ///
    IAlgorytm* getAlgorytm();

signals:
    void krokWykonany(QString status); ///< sygnał emitowany po każdorazowym wykonaniu metody CAlgorytmAStar::krokAlgorytmu w głównej pętli wątku przekazujący podstawowe statystyki
    void rozwiazanieZnalezione(); ///< sygnał emitowany po "naturalnym" zakończeniu działania algorytmu - znalezieniu rozwiązania
    void przerwaneDzialanie(); ///< sygnał emitowany po wymuszeniu przerwania działania algorytmu otrzymanym z zewnątrz wątku

protected:
    ///
    /// @brief metoda run przesłaniająca metodę z klasy bazowej - główna pętla wątku do wykonywania obliczeń na potrzeby algorytmu przeszukiwania
    ///
    /// @details metoda składa się z nieskończonej pętli. W każdej iteracji: <br>
    /// - sprawdzany jest stan flagi przerwanie - jeśli flaga jest ustawiona emitowany jest sygnał przerwaneDzialanie, flaga zerowana, a pętla jest przerywana
    /// - wykonywany jest kolejny krok algorytmu przez wywołanie metody CAlgorytmAStar::krokAlgorytmu atrybutu algorytm
    /// - jeśli wywołana metoda zwraca wartość true (koniec działania algorytmu) - emitowany jest sygnał rozwiazanieZnalezione, pętla jest przerywana
    /// - emitowany jest sygnał krokWykonany z podanym napisem zawierającym statystyki (liczba wykonanych kroków, wartość heurystyki dla aktualnego węzła, liczba odwiedzonych węzłów)
    /// Instrukcje wymagające zabezpieczenia zasobów przed dostępem z zewnątrz wątku wykonywane są w bloku zabezpieczonym obiektem klasy QMutexLocker
    ///
    /// @param[in] algorytm wskaźnik do obiektu algorytmu (obiekt klasy CAlgorytmAStar poprzez interfejs IAlgorytm)
    ///
    void run();

private:
    IAlgorytm *algorytm;
    bool przerwanie;
    QMutex mutex;
};

#endif // CWATEKALGORYTM_H
