#include "cmodelukladanka.h"
#include "heurystyki/cheurystykamanhattan.h"
#include <QRandomGenerator>

CModelUkladanka::CModelUkladanka(int N, int M) :
    N(N),
    M(M),
    plansza(new CArray2D<int>(N,M,-1)),
    licznikRuchow(0),
    ostatniRuch({-1,-1}),
    timer(new QTime()),
    stan(EStan::rozwiazany),
    czasUlozenia(0)
{
    plansza = new CArray2D<int>(N,M,0);
    for(int i=0;i<N*M-1;i++)
        plansza->dostepLiniowy(i)=i+1;
    plansza->dostepLiniowy(N*M-1)=0;
}

CModelUkladanka::CModelUkladanka(std::vector<int> tbl, int N, int M) :
    N(N),
    M(M),
    plansza(new CArray2D<int>(N,M,tbl)),
    licznikRuchow(0),
    ostatniRuch({-1,-1}),
    timer(new QTime()),
    stan(EStan::wolny),
    czasUlozenia(0)
{
    if (czyUlozona(plansza)) stan = EStan::rozwiazany; //sprawdź, czy zadane ustawienie nie jest rozwiązaniem
}

bool CModelUkladanka::resetuj(int N, int M)
{
    this->N=N;
    this->M=M;
    delete plansza;
    plansza = new CArray2D<int>(N,M,0);
    for(int i=0;i<N*M-1;i++)
        plansza->dostepLiniowy(i)=i+1;
    plansza->dostepLiniowy(N*M-1)=0;
    ostatniRuch = {-1,-1};
    stan = EStan::rozwiazany;
    czasUlozenia = 0;
    licznikRuchow = 0;
}

CArray2D<int> *CModelUkladanka::getPlansza()
{
    return plansza;
}

void CModelUkladanka::setPlansza(CArray2D<int> *plansza)
{
    this->plansza=plansza;
}

void CModelUkladanka::setPlansza(std::vector<int> tbl)
{
    delete plansza;
    plansza = new CArray2D<int>(N,M,tbl);
    ostatniRuch = {-1,-1};
    if (czyUlozona(plansza)) stan = EStan::rozwiazany; //sprawdź, czy zadane ustawienie nie jest rozwiązaniem
    else stan = EStan::wolny;
    czasUlozenia = 0;
    licznikRuchow = 0;
}

bool CModelUkladanka::sprawdzRuch(int nrPola)
{
    return sprawdzRuch(nrPola,*plansza);
}

int CModelUkladanka::wykonajRuch(int nrPola)
{
    int nowePole = wykonajRuch(nrPola,*plansza);
    if (nowePole>-1) {
        ostatniRuch[0] = nrPola;
        ostatniRuch[1] = nowePole;
        switch (stan) {
        case EStan::rozwiazany:
            stan=EStan::ustawianie; //dowolny prawidłowy ruch wykonany z pozycji początkowej powoduje włączenie trybu ręcznego ustawiania pozycji
            break;
        case EStan::wolny: //dowolny prawidłowy ruch wykonany poczynając z trybu wolny powoduje włączenie liczników i przejście do trybu rozwiązywania
            stan=EStan::rozwiazywanie;
            timer->restart();
            licznikRuchow==0; //bez breaka na końcu, żeby wykonany został kolejny blok case
        case EStan::rozwiazywanie:
            licznikRuchow++;
            if (czyUlozona(plansza)) {
                czasUlozenia = timer->elapsed();
                stan=EStan::rozwiazany;
            }
            break;
        }
    }
    return nowePole;
}

std::array<int, 2> CModelUkladanka::getOstatniRuch()
{
    return ostatniRuch;
}

int CModelUkladanka::getCzas()
{
    if (stan==EStan::rozwiazany) return czasUlozenia;
    else return timer->elapsed();
}

int CModelUkladanka::getLiczbaRuchow()
{
    return licznikRuchow;
}

EStan CModelUkladanka::getStan()
{
    return stan;
}

void CModelUkladanka::setReczneUstawianie(bool ustawianie)
{
    if (ustawianie && stan!=EStan::ustawianie) { //ustaw stan ustawianie, resetuj statystyki
        stan=EStan::ustawianie;
        ostatniRuch = {-1,-1};
        czasUlozenia = 0;
        licznikRuchow = 0;
    }
    else if (!ustawianie && stan==EStan::ustawianie) { //ustaw stan wolny - oczekiwanie na rozpoczęcie rozwiązywania, resetuj statystyki
        stan=EStan::wolny;
        ostatniRuch = {-1,-1};
        czasUlozenia = 0;
        licznikRuchow = 0;
    }
}

bool CModelUkladanka::sprawdzRuch(int nrPola, CArray2D<int> &stan)
{
    return stan.dostepLiniowy(nrPola)==0 ? false :
                                           stan.zLewej(nrPola)==0 ||
                                           stan.zPrawej(nrPola)==0 ||
                                           stan.zGory(nrPola)==0 ||
                                           stan.zDolu(nrPola)==0;
}

int CModelUkladanka::wykonajRuch(int nrPola, CArray2D<int> &stan)
{
    if (stan.zLewej(nrPola)==0) { //jeśli z lewej jest pole puste (wartość==0)
        stan.zLewej(nrPola) = stan.dostepLiniowy(nrPola); //przypisz pustemu polu wartość z pola aktualnego
        stan.dostepLiniowy(nrPola)=0; //przypisz aktualnemu polu wartość 0 (pole puste)
        return nrPola-1; //zwróć nr pola na które przesunięto element z pola nrPola
    }
    else if (stan.zPrawej(nrPola)==0) {
        stan.zPrawej(nrPola) = stan.dostepLiniowy(nrPola);
        stan.dostepLiniowy(nrPola)=0;
        return nrPola+1;
    }
    else if (stan.zGory(nrPola)==0) {
        stan.zGory(nrPola) = stan.dostepLiniowy(nrPola);
        stan.dostepLiniowy(nrPola)=0;
        return nrPola-stan.getN();
    }
    else if (stan.zDolu(nrPola)==0) {
        stan.zDolu(nrPola) = stan.dostepLiniowy(nrPola);
        stan.dostepLiniowy(nrPola)=0;
        return nrPola+stan.getN();
    }
    return -1;
}

bool CModelUkladanka::czyUlozona(CArray2D<int> *stan)
{
    for(int t=0;t<stan->getM()*stan->getN();t++)
        if (stan->dostepLiniowy(t)>0 && stan->dostepLiniowy(t)!=(t+1)) //sprawdzaj tylko pola z elementami (wartość>0), których numer odpowiada pozycji "zlinearyzowanej" w tablicy
            return false;
    return true;
}

double CModelUkladanka::podajOcene(CArray2D<int> *stan, CHeurystyka *heurystyka)
{
    return heurystyka->policzOcene(stan);
}

std::vector<int> CModelUkladanka::zwrocMozliweRuchy(CArray2D<int> *stan)
{

}

void CModelUkladanka::wygenerujLosoweUstawienie()
{
    //generuje losową pozycję spośród pozycji od pierwszej do przedostatniej (oprócz elementu pustego z ostatniej pozycji) i zamienia ją miejscem z następną
    //zamianę wykonuje ustaloną liczbę razy - aby układ był rozwiązywalny musi być to parzysta liczba
    int zakres = M*N;
    resetuj(N,M); //zapewnia, że pole puste jest na końcu
    for (int i=0;i<2*((zakres-1)/2+1);i++) { //liczba losowan  jest równa lub większa od liczby elementów układanki bez elementu pustego i jest parzysta
        int los = (int)(QRandomGenerator::global()->bounded(0,zakres-2)); //generuje losową liczbę uint32 z zakresu 0 do zakres-2; ostatnia pozycja (o nr zakres-1) jest zarezerwowana dla elementu pustego
        int temp = plansza->dostepLiniowy(los);
        plansza->dostepLiniowy(los) = plansza->dostepLiniowy(los+1);
        plansza->dostepLiniowy(los+1) = temp;
    }
    plansza->dostepLiniowy(zakres-1) = 0; //na koniec - element pusty
    //zeruj statystyki
    ostatniRuch = {-1,-1};
    stan = EStan::wolny;
    czasUlozenia = 0;
    licznikRuchow = 0;
}








