#ifndef CPOLE_H
#define CPOLE_H

#include <QPushButton>

class CPole : public QPushButton
{
public:
    CPole(int pozycja, int numer);
    void setNumer(int numer);
    int getNumer();
    int getPozycja();
private:
    int pozycja;
    int numer;

};

#endif // CPOLE_H
