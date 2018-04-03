#ifndef IGUI_H
#define IGUI_H

#include <vector>
#include <array>
#include <map>
#include <string>
#include "Kontroler/ikontroler.h"

class IGUI {
public:
    virtual bool rysujPlansze(std::vector<int> tbl, int N, int M) = 0;
    virtual bool zamienPola(std::vector<std::array<int,2>> pary) = 0;
    virtual bool setUstawianieReczne(bool ustawianie) = 0;
    virtual bool wyswietlKonfiguracje(std::map<std::string,std::string> param) = 0;
    virtual bool wyswietlStatus(std::string status) = 0;
    virtual bool zamknijOkno() = 0;
    virtual bool wyswietlOprogramie(std::map<std::string,std::string> param) = 0;
    virtual bool wyswietlInstrukcje(std::map<std::string,std::string> param) = 0;
    virtual void setKontroler(IKontroler *kontroler) = 0;
};

#endif // IGUI_H
