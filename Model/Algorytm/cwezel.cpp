#include "cwezel.h"
#include "Model/Ukladanka/cmodelukladanka.h"


CWezel::CWezel(CArray2D<int> *stan) :
    stan(stan),
    ocena(0),
    koszt(0),
    poprzednik(0),
    ruch(-1)
{ }

CWezel::~CWezel()
{
    if (stan!=0) delete stan;
}

double CWezel::getOcena()
{
    return ocena;
}

double CWezel::getKoszt()
{
    return koszt;
}

double CWezel::szacujOdleglosc(CHeurystyka *heurystyka)
{
    return heurystyka->policzOcene(stan);
}

CArray2D<int> *CWezel::getStan()
{
    return stan;
}

void CWezel::aktualizujOceneKoszt(double ocena, double koszt, CWezel *poprzednik, int ruch)
{
    this->ocena = ocena;
    this->koszt = koszt;
    this->poprzednik = poprzednik;
    this->ruch = ruch;
}

CWezel *CWezel::getPoprzednik()
{
    return poprzednik;
}

std::vector<CWezel *> CWezel::getNastepniki()
{
    std::vector<CWezel *> wynik;
    std::vector<int> mozliweRuchy = CModelUkladanka::zwrocMozliweRuchy(stan); //pobierz z układanki nry pól możliwych ruchów dla stanu z przekazanego węzła
    for(typename std::vector<int>::iterator it=mozliweRuchy.begin();it!=mozliweRuchy.end();it++) {
        //dla każdego ruchu utwórz nowy obiekt CArray2D<int> wyliczony z przekazanego przez wykonanie ruchu
        CArray2D<int> *nowyStan = new CArray2D<int>(*stan);
        int nowyRuch = CModelUkladanka::wykonajRuch(*it,*nowyStan);
        if (nowyRuch!=-1) {
            CWezel *nowyWezel = new CWezel(nowyStan);
            nowyWezel->aktualizujOceneKoszt(0.0,0.0,this,nowyRuch);
            wynik.push_back(nowyWezel);
        }
    }
    return wynik;
}

int CWezel::getRuch()
{
    return ruch;
}

