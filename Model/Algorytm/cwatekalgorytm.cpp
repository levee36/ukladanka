#include "cwatekalgorytm.h"
#include <QMutexLocker>

CWatekAlgorytm::CWatekAlgorytm() :
    QThread(),
    przerwanie(false)
{
}

CWatekAlgorytm::~CWatekAlgorytm()
{
    if (algorytm!=0) delete algorytm;
}

void CWatekAlgorytm::przerwij()
{
    QMutexLocker locker(&mutex); //blokuj dostęp do zmiennych dla innych wątków
    this->przerwanie = true;
}

void CWatekAlgorytm::setAlgorytm(IAlgorytm *algorytm)
{
    QMutexLocker locker(&mutex); //blokuj dostęp do zmiennych dla innych wątków
    this->algorytm = algorytm;
}

IAlgorytm* CWatekAlgorytm::getAlgorytm()
{
    QMutexLocker locker(&mutex);
    return algorytm;
}

void CWatekAlgorytm::run()
{
    for(;;) {
        {
            QMutexLocker locker(&mutex); //blokuj dostęp do zmiennych dla innych wątków e tym bloku
            if (przerwanie) {
                emit przerwaneDzialanie();
                przerwanie=false;
                break;
            }
            if (algorytm->wykonajKrokAlgorytmu()) {
                emit rozwiazanieZnalezione();
                przerwanie=false;
                break;
            }
        }
        //tu dostęp nie jest blokowany
        emit krokWykonany(QString::number(algorytm->getLiczbaOdwiedzonych()));
    }
}

