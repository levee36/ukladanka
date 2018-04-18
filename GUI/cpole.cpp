#include "cpole.h"


CPole::CPole(int pozycja, int numer) :
    QPushButton(QString::number(numer)),
    pozycja(pozycja),
    numer(numer)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);
    this->setNumer(numer);
}

void CPole::setNumer(int numer)
{
    this->numer = numer;
    //zarządzanie widocznością i dostepnowścią w zależności od wartości "numer"
    switch (numer) {
    case -1: //pole niedostępne
        this->setVisible(true);
        this->setEnabled(false);
        break;
    case 0: //pole puste
        this->setVisible(false);
        break;
    default: //pola z numerami - elementy układanki
        this->setVisible(true);
        this->setEnabled(true);
        this->setText(QString::number(numer));
        break;
    }
}

int CPole::getNumer()
{
    return numer;
}

int CPole::getPozycja()
{
    return pozycja;
}
