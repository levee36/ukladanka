#include "calgorytmastar.h"
#include "Model/Ukladanka/cmodelukladanka.h"

CAlgorytmAStar::CAlgorytmAStar(CArray2D<int> *stanPoczatkowy, CHeurystyka *heurystyka) :
    liczbaOdwiedzonych(1),
    heurystyka(heurystyka)
{
    //utwórz CWezel na podstawie parametru stanPoczatkowy i wstaw go do zbioru OPEN i OPENoceny
    aktualny = new CWezel(stanPoczatkowy);
    zbiorOPEN.insert(aktualny);
    //wyzeruj wskaźnik
    aktualny = 0;
}

CAlgorytmAStar::~CAlgorytmAStar()
{
    for (std::set<CWezel*,CWezelCompare>::iterator it = zbiorOPEN.begin(); it != zbiorOPEN.end(); it++)
        if (*it!=0) delete *it;
    for (std::set<CWezel*,CWezelCompare>::iterator it = zbiorCLOSED.begin(); it != zbiorCLOSED.end(); it++)
        if (*it!=0) delete *it;
    zbiorOPEN.clear();
    zbiorCLOSED.clear();
    if (aktualny!=0) delete aktualny;
}



bool CAlgorytmAStar::wykonajKrokAlgorytmu()
{
    // 1. Pobierz ze zbioru OPEN węzeł o najmniejszej wartości funkcji oceny f, ustaw na nim wskaźnik aktualny i wstaw go do zbioru CLOSED
    aktualny = najmniejszyOPEN();
    aktHeur = aktualny->getOcena()-aktualny->getKoszt();

    //usuń ten węzeł ze zbiorów OPEN
    zbiorOPEN.erase(aktualny);

    //wstaw do CLOSED
    zbiorCLOSED.insert(aktualny);

    // 2. Sprawdź, czy wskaźnik aktualny wskazuje na węzeł końcowy (wykonaj metodę statyczną CModelUkladanka::CzyUlozona dla planszy przechowywanej w tym węźle)
    if (CModelUkladanka::czyUlozona(aktualny->getStan()))
        return true; // - jeśli metoda zwróci wartość true - węzeł końcowy, zakończ działanie metody i zwróć wartość true <br>

    // 3. Znajdź następniki węzła ze wskaźnika aktualny (za pomocą metody statycznej CModelUkladanka::zwrocMozliweRuchy)
    std::vector<int> nastepnikiRuchy = CModelUkladanka::zwrocMozliweRuchy(aktualny->getStan());

    // 4. Dla każdego ze znalezionych następników:
    for(std::vector<int>::iterator it = nastepnikiRuchy.begin();it != nastepnikiRuchy.end();it++) {

        //utwórz nowy węzeł przechowujący stan planszy po wykonaniu tego ruchu
        CWezel *nastepnik = new CWezel(new CArray2D<int>(*(aktualny->getStan()))); //węzeł z planszą identyczną jak aktualny węzeł (plansza jest tworzona jako kopia obiektu z przekazanego wskaźnika)
        CModelUkladanka::wykonajRuch(*it,*(nastepnik->getStan())); //wykonanie ruchu z pola o nr z wektora nastepnikiRuchy na aktualnym ustawieniu - modyfikuje obiekt CArray2D<int> wskazywany przez wskaźnik - atrybut nowego węzła

        // - oblicz koszt dojścia - jest równy kosztowi dojścia do obecnego węzła + 1 (koszt dla węzła aktualny to metoda CWezel::getKoszt)
        // - oblicz wartość heurystyki (metoda CWezel::szacujOdleglosc dla sprawdzanego następnika)
        // - oblicz wartość funkcji oceny - równą sumie kosztu i heurystyki
        double wKoszt = aktualny->getKoszt()+1;
        double wHeurystyka = nastepnik->szacujOdleglosc(heurystyka);
        double wOcena = wKoszt + wHeurystyka;

        // - zapamiętaj wyliczone wartości w tym węźle oraz zapamiętaj jako poprzednik węzeł aktualny oraz ruch jaki został wykonany, by z węzła aktualnego uzyskać ten następnik
        nastepnik->aktualizujOceneKoszt(wOcena,wKoszt,aktualny,*it);

        // - sprawdź, czy następnik NIE należy do zbioru OPEN lub CLOSED
        std::set<CWezel*>::iterator itOPEN =  zbiorOPEN.find(nastepnik);
        std::set<CWezel*>::iterator itCLOSED =  zbiorCLOSED.find(nastepnik);
        if (itOPEN==zbiorOPEN.end() && itCLOSED==zbiorCLOSED.end()) {
            // Jeśli warunek jest spełniony - dopisz go do zbioru OPEN  i przejdź do sprawdzania kolejnego następnika
            zbiorOPEN.insert(nastepnik);
            liczbaOdwiedzonych++;
        }
        // Jeśli warunek nie był spełnionu to: <br>
        // - sprawdź warunek: ((następnik należy do zbioru OPEN lub następnik należy do zbioru CLOSED) i jego ocena jest niższa (lepsza) niż węzła ze zbioru OPEN/CLOSED).
        else {
            //jeśli następnik jest w zbiorze CLOSED i ma lepszą ocenę
            if (itCLOSED!=zbiorCLOSED.end() && (*itCLOSED)->getOcena()>nastepnik->getOcena()) {
                zbiorCLOSED.erase(itCLOSED);
                zbiorOPEN.insert(nastepnik);
            }
            else if (itOPEN!=zbiorOPEN.end() && (*itOPEN)->getOcena()>nastepnik->getOcena()) {              
                zbiorOPEN.erase(itOPEN);
                zbiorOPEN.insert(nastepnik);
            }
        }
    }

    return false;

}

std::vector<int> CAlgorytmAStar::zwrocSciezke()
{
    std::vector<int> wynik;
    CWezel *wezel = aktualny;
    while (wezel!=0) {
        wynik.push_back(wezel->getRuch());
        wezel = wezel->getPoprzednik();
    }
    if (wynik.back()==-1) wynik.pop_back(); //usuń ostatni element, który zapewne jest równy -1 (stan startowy nie miał poprzednika)
    return wynik;
}

int CAlgorytmAStar::getLiczbaOdwiedzonych()
{
    return liczbaOdwiedzonych;
}

void CAlgorytmAStar::setHeurystyka(CHeurystyka *heurystyka)
{
    this->heurystyka = heurystyka;
}

CHeurystyka *CAlgorytmAStar::getHeurystyka()
{
    return heurystyka;
}

void CAlgorytmAStar::wyczysc(CArray2D<int> *stanPoczatkowy)
{
    for (std::set<CWezel*,CWezelCompare>::iterator it = zbiorOPEN.begin(); it != zbiorOPEN.end(); it++)
        if (*it!=0) delete *it;
    for (std::set<CWezel*,CWezelCompare>::iterator it = zbiorCLOSED.begin(); it != zbiorCLOSED.end(); it++)
        if (*it!=0) delete *it;
    zbiorOPEN.clear();
    zbiorCLOSED.clear();
    liczbaOdwiedzonych=0;

    aktualny = new CWezel(stanPoczatkowy); //aktualny nie musi być usuwany, bo został usunięty wraz z usuwaniem obiektów wskazywanych przez zbiorCLOSED
    zbiorOPEN.insert(aktualny);
    //wyzeruj wskaźnik
    aktualny = 0;
}

double CAlgorytmAStar::getAktHeur()
{
    return aktHeur;
}

CWezel *CAlgorytmAStar::najmniejszyOPEN()
{
    if (zbiorOPEN.size()==0) return 0;
    CWezel *min = *(zbiorOPEN.begin());
    for (std::set<CWezel*,CWezelCompare>::iterator it = zbiorOPEN.begin(); it != zbiorOPEN.end(); it++)
        if ((*it)->getOcena()<min->getOcena()) min=*it;
    return min;
}

