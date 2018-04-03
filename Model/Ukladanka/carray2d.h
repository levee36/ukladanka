#ifndef CARRAY2D_H
#define CARRAY2D_H

#include <vector>
#include <cstdlib>

template<typename T = int> class CArray2D : public std::vector<std::vector<T>>
{
private:
    int M; //liczba wierszy
    int N; //liczba kolumn
public:
    //konstruktor ustawiający rozmiar i wartość początkową
    CArray2D(size_t n, size_t m, T wartosc) :
        N(n),
        M(m),
        std::vector<std::vector<T>>(m, std::vector<T>(n,wartosc))
    { }

    //konstruktor ustawiający rozmiar i wartości z podanego wektora
    CArray2D(size_t n, size_t m, std::vector<T> tbl) :
        N(n),
        M(m),
        std::vector<std::vector<T>>(m, std::vector<T>(n))
    {
        int i=0;
        for(typename std::vector<T>::iterator it=tbl.begin();it!=tbl.end() && i<N*M;it++) {
            CArray2D<T>::at((i%N),(i/N)) = *it;
            i++;
        }
    }

    //zwraca referencję do elementu o współrzędnych n,m
    T &at(size_t n, size_t m){
        return std::vector<std::vector<T>>::at(m).std::vector<T>::at(n);
    }

    //zwraca wektor liniowy obiektów klasy T przez odczyt liniami poziomymi od elementu 0,0)
    std::vector<T> wektor() {
        std::vector<T> wynik;
        for(int m=0;m<M;m++)
            for(int n=0;n<N;n++)
                wynik.push_back(at(n,m));
        return wynik;
    }

    //zwraca referencję do elementu w odczycie liniowym (odczyt liniami poziomymi od elementu 0,0)
    T &dostepLiniowy(size_t t) {
        return CArray2D<T>::at(t%N,t/N);
    }
    size_t getN() {return N;}
    size_t getM() {return M;}
    T &zGory(size_t n, size_t m) {return m==0 ? at(n,m) : at(n,m-1);}
    T &zGory(size_t t) {return t/N==0 ? at(t%N,t/N) : at(t%N,t/N-1);}
    T &zDolu(size_t n, size_t m) {return m==M-1 ? at(n,m) : at(n,m+1);}
    T &zDolu(size_t t) {return t/N==M-1 ? at(t%N,t/N) : at(t%N,t/N+1);}
    T &zLewej(size_t n, size_t m) {return n==0 ? at(n,m) : at(n-1,m);}
    T &zLewej(size_t t) {return t%N==0 ? at(t%N,t/N) : at(t%N-1,t/N);}
    T &zPrawej(size_t n, size_t m) {return n==N-1 ? at(n,m) : at(n+1,m);}
    T &zPrawej(size_t t) {return t%N==N-1 ? at(t%N,t/N) : at(t%N+1,t/N);}
};

#endif // CARRAY2D_H
