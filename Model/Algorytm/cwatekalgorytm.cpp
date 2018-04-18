#include "cwatekalgorytm.h"
#include <QMutexLocker>

CWatekAlgorytm::CWatekAlgorytm() :
    QThread(),
    przerwanie(false)
{
}

CWatekAlgorytm::~CWatekAlgorytm()
{
}

void CWatekAlgorytm::przerwij()
{
    QMutexLocker locker(&mutex);
    this->przerwanie = true;
}

void CWatekAlgorytm::setAlgorytm(IAlgorytm *algorytm)
{
    QMutexLocker locker(&mutex);
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
            QMutexLocker locker(&mutex);
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
        emit krokWykonany(QString::number(algorytm->getLiczbaOdwiedzonych()));
    }
}

