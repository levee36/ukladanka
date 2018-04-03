#ifndef CMODELUKLADANKA_H
#define CMODELUKLADANKA_H

#include "iukladanka.h"
#include "heurystyki/cheurystyka.h"
#include <array>
#include <QTime>

class CModelUkladanka : public IUkladanka
{
public:
    CModelUkladanka(int N, int M);
    CModelUkladanka(std::vector<int> tbl, int N, int M);
    bool resetuj(int N, int M);
    CArray2D<int> *getPlansza();
    void setPlansza(CArray2D<int>* plansza);
    void setPlansza(std::vector<int> tbl);
    static CHeurystyka *getHeurystyka();
    static void setHeurystyka(CHeurystyka *heurystyka);
    bool sprawdzRuch(int nrPola);
    int wykonajRuch(int nrPola);
    std::array<int,2> getOstatniRuch();
    bool czyUlozona();
    int getCzas();
    int getLiczbaRuchow();
    EStan getStan();
    void setReczneUstawianie(bool ustawianie);
    void wygenerujLosoweUstawienie();

    static bool sprawdzRuch(int nrPola, CArray2D<int> &stan);
    static int wykonajRuch(int nrPola, CArray2D<int> &stan);
    static bool czyUlozona(CArray2D<int> *stan);
    static double podajOcene(CArray2D<int> *stan, CHeurystyka *heurystyka);
    static std::vector<int> zwrocMozliweRuchy(CArray2D<int> stan);
    static bool czyPrawidlowyUklad(CArray2D<int> stan);
private:
    EStan stan;
    int N;
    int M;
    CArray2D<int> *plansza;
    std::array<int,2> ostatniRuch;
    QTime *timer;
    int licznikRuchow;
    int czasUlozenia;
};

#endif // CMODELUKLADANKA_H
