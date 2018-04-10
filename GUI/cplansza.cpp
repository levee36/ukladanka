#include "cplansza.h"
#include <string>
#include <QGridLayout>
#include "GUImsg/cguimsgwcisnietepole.h"

CPlansza::CPlansza(std::vector<int> tbl, int N, int M, IKontroler *kontroler, QWidget *parent)
    : QFrame(parent), N(N), M(M), kontroler(kontroler)
{
    QGridLayout *layout = new QGridLayout();
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    CPole *p;
    listaPol = std::vector<CPole*>();
    int i = 0;
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    for(std::vector<int>::iterator it=tbl.begin();it!=tbl.end() && i<N*M;it++) {
        p=new CPole(i,*it);
        p->setSizePolicy(sizePolicy);
        layout->addWidget(p,i / N,i % N);
        listaPol.push_back(p);
        connect(p,SIGNAL(pressed()),this,SLOT(on_actionPole_pressed()));
        i++;
    }
    setLayout(layout);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

CPlansza::~CPlansza()
{
    delete [] listaPol;
}

bool CPlansza::zamienPola(std::vector<std::array<int, 2>> pary)
{
    for(std::vector<std::array<int, 2>>::iterator it=pary.begin();it!=pary.end();it++) {
        int zamienianePole = listaPol[(*it)[0]]->getNumer(); //nr elementu z pierwszej pozycji w parze do zamiany
        listaPol[(*it)[0]]->setNumer(listaPol[(*it)[1]]->getNumer()); //wpisanie do pierwszego pola nr elementu z drugiego pola z pary do zamiany
        listaPol[(*it)[1]]->setNumer(zamienianePole);
    }
    return true;
}

bool CPlansza::ustawKolejnosc(std::vector<int> tbl)
{
    std::vector<int>::iterator it=tbl.begin(); //iterator dla wejsciowego wektora liczb-nr elementów
    for(std::vector<CPole*>::iterator itPola=listaPol.begin();itPola!=listaPol.end() && it!=tbl.end();itPola++) { //warunek końca pętli ustawiony na dotarcie do ostatniego elementu któregokolwiek z wektorów
        (*itPola)->setNumer(*it); //ustaw na kolejnym polu element z nr podanym na kolejnym miejscu wektora wejściowego
        it++;
    }
    return true;
}

void CPlansza::on_actionPole_pressed()
{
    kontroler->wyslijWiadomosc(new CGUIMsgWcisnietePole(((CPole*)sender())->getPozycja()));
}
