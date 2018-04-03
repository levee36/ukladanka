#ifndef IUKLADANKA_H
#define IUKLADANKA_H

#include "Model/Ukladanka/carray2d.h"
#include "Model/Ukladanka/heurystyki/cheurystyka.h"
#include <vector>
#include <array>

enum EStan {
    wolny,
    rozwiazywanie,
    ustawianie,
    rozwiazany
};

class IUkladanka
{

public:
    virtual bool resetuj(int N, int M) = 0;
    virtual CArray2D<int> *getPlansza() = 0;
    virtual void setPlansza(CArray2D<int>*) = 0;
    virtual bool sprawdzRuch(int nrPola) = 0;
    virtual int wykonajRuch(int nrPola) = 0;
    virtual std::array<int,2> getOstatniRuch() = 0;
    virtual int getCzas() = 0;
    virtual int getLiczbaRuchow() = 0;
    virtual EStan getStan() = 0;
    virtual void setReczneUstawianie(bool ustawianie) = 0;
    virtual void wygenerujLosoweUstawienie() = 0;

    static bool sprawdzRuch(int nrPola, CArray2D<int> &stan);
    static int wykonajRuch(int nrPola, CArray2D<int> &stan);
    static bool czyUlozona(CArray2D<int> *stan);
    static double podajOcene(CArray2D<int> *stan, CHeurystyka *heurystyka);
    static std::vector<int> zwrocMozliweRuchy(CArray2D<int> stan);
    static bool czyPrawidlowyUklad(CArray2D<int> stan);
};

#endif // IUKLADANKA_H
