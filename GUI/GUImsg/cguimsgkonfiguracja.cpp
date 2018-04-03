#include "cguimsgkonfiguracja.h"

CGUIMsgKonfiguracja::CGUIMsgKonfiguracja(int N, int M)
    : CGUIMsg(std::string("Konfiguracja")),
      N(N),
      M(M)
{

}

int CGUIMsgKonfiguracja::getN()
{
    return N;
}

int CGUIMsgKonfiguracja::getM()
{
    return M;
}
