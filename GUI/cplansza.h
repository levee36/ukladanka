#ifndef CPLANSZA_H
#define CPLANSZA_H

#include <QObject>
#include <QFrame>
#include <QPushButton>
#include <vector>
#include <array>
#include "Kontroler/ikontroler.h"
#include "GUI/cpole.h"

namespace Ui {
class CPlansza;
}

class CPlansza : public QFrame
{
    Q_OBJECT

public:
    CPlansza(std::vector<int> tbl, int N, int M, IKontroler *kontroler, QWidget *parent = 0);
    ~CPlansza();
    bool zamienPola(std::vector<std::array<int,2>> pary);
    bool ustawKolejnosc(std::vector<int> tbl);

public slots:
    void on_actionPole_pressed();

private:
    IKontroler *kontroler;
    QWidget *m_parent;
    std::vector<CPole*> listaPol;
    int N;
    int M;
    int rozmiarPola;
};

#endif // CPLANSZA_H
