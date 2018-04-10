#ifndef CARRAY2D_H
#define CARRAY2D_H

#include <vector>
#include <cstdlib>

///
/// @ingroup model
/// @brief
/// szablon klasy pochodnej szablonu wektora z biblioteki STL
/// realizującej wektor dwuwymiarowy o ustalonych przy tworzeniu wymiarach
/// @details
/// umożliwia dostęp do elementów zarówno przez odwołanie się po dwóch współrzędnych
/// jak i po jednej współrzędnej (przy odczycie wierszami poczynając od elementu (0,0)
/// @tparam T typ przechowywany w wektorze, domyślnie int
///
/// @author Robert Płatkowski
/// @date 2018-04-04
///
template<typename T = int> class CArray2D : public std::vector<std::vector<T>>
{
private:
    int M; ///<liczba wierszy
    int N; ///<liczba kolumn
public:
    ///
    /// @brief konstruktor ustawiający rozmiar i wartość początkową
    ///
    /// @param[in] n liczba kolumn
    /// @param[in] m liczba wierszy
    /// @param[in] wartosc wartość nadawana każdemu elementowi dwuwymiarowego wektora
    ///
    CArray2D(size_t n, size_t m, T wartosc) :
        N(n),
        M(m),
        std::vector<std::vector<T>>(m, std::vector<T>(n,wartosc))
    { }

    ///
    /// @brief konstruktor ustawiający rozmiar i wartości z podanego wektora int
    ///
    /// @details
    /// jeśli wektor podany jako argument ma niewystarczającą liczbę elementów - pozostałe elementy zostaną ustawione na 0 <br>
    /// jeśli wektor podany jako argument ma więcej elementów niż n*m - nadmiarowe elementy zostaną pominięte <br>
    ///
    /// @param[in] n liczba kolumn
    /// @param[in] m liczba wierszy
    /// @param[in] tbl wektor wartości do ustawienia w kolejnych komórkach wektora dwuwymiarowego
    ///
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

    ///
    /// @brief metoda zwracająca referencję do elementu wektora o współrzędnych n,m
    ///
    /// @param[in] n współrzędna kolumny
    /// @param[in] m współrzędna wiersza
    /// @return referencja do elementu znajdującego się na współrzędnych (n,m)
    ///
    T &at(size_t n, size_t m){
        return std::vector<std::vector<T>>::at(m).std::vector<T>::at(n);
    }

    ///
    /// @brief metoda zwracająca wektor liniowy obiektów klasy T przez odczyt liniami poziomymi od elementu (0,0)
    ///
    /// @return wektor listujący wszystkie elementy wektora dwuwymiarowego przy odczycie wierszami poczynając od elementu (0,0)
    ///
    std::vector<T> wektor() {
        std::vector<T> wynik;
        for(int m=0;m<M;m++)
            for(int n=0;n<N;n++)
                wynik.push_back(at(n,m));
        return wynik;
    }

    ///
    /// @brief metoda zwracająca referencję do elementu w odczycie liniowym - odczyt liniami poziomymi od elementu (0,0)
    ///
    /// @param[in] t pozycja elementu przy odczycie liniowym wierszami poczynając od elementu (0,0)
    /// @return referencja do elementu na pozycji t przy odczycie liniowym wierszami poczynając od elementu (0,0)
    ///
    T &dostepLiniowy(size_t t) {
        return CArray2D<T>::at(t%N,t/N);
    }

    ///
    /// @brief metoda zwracająca liczbę kolumn wektora dwuwymiarowego
    ///
    /// @return liczba kolumn wektora dwuwymiarowego
    ///
    size_t getN() {return N;}

    ///
    /// @brief metoda zwracająca liczbę wierszy wektora dwuwymiarowego
    ///
    /// @return liczba wierszy wektora dwuwymiarowego
    ///
    size_t getM() {return M;}

    ///
    /// @brief metoda przeciążona zwracająca referencję do elementu sąsiadującego od góry ze wskazanym elementem <br>
    /// wskazanie elementu za pomocą współrzędnych dwuwymiarowych
    ///
    /// @details gdy wskazano element znajdujący się w pierwszym wierszu wektora dwuwymiarowego zwrócony zostanie ten sam element (podany jako argument)
    ///
    /// @param[in] n współrzędna kolumny
    /// @param[in] m współrzędna wiersza
    /// @return referencja do elementu sąsiadującego od góry ze wskazanym w argumencie
    ///
    T &zGory(size_t n, size_t m) {return m==0 ? at(n,m) : at(n,m-1);}

    ///
    /// @brief metoda przeciążona zwracająca referencję do elementu sąsiadującego od góry ze wskazanym elementem <br>
    /// wskazanie elementu za pomocą współrzędnej liniowej (kolejności elementu w odczycie liniowym wierszami poczynając od elementu (0,0))
    ///
    /// @details gdy wskazano element znajdujący się w pierwszym wierszu wektora dwuwymiarowego zwrócony zostanie ten sam element (podany jako argument)
    ///
    /// @param[in] n współrzędna kolumny
    /// @param[in] m współrzędna wiersza
    /// @return referencja do elementu sąsiadującego od góry ze wskazanym w argumencie
    ///
    T &zGory(size_t t) {return t/N==0 ? at(t%N,t/N) : at(t%N,t/N-1);}

    ///
    /// @brief metoda przeciążona zwracająca referencję do elementu sąsiadującego od dołu ze wskazanym elementem <br>
    /// wskazanie elementu za pomocą współrzędnych dwuwymiarowych
    ///
    /// @details gdy wskazano element znajdujący się w ostatnim wierszu wektora dwuwymiarowego zwrócony zostanie ten sam element (podany jako argument)
    ///
    /// @param[in] n współrzędna kolumny
    /// @param[in] m współrzędna wiersza
    /// @return referencja do elementu sąsiadującego od dołu ze wskazanym w argumencie
    ///
    T &zDolu(size_t n, size_t m) {return m==M-1 ? at(n,m) : at(n,m+1);}

    ///
    /// @brief metoda przeciążona zwracająca referencję do elementu sąsiadującego od dołu ze wskazanym elementem <br>
    /// wskazanie elementu za pomocą współrzędnej liniowej (kolejności elementu w odczycie liniowym wierszami poczynając od elementu (0,0))
    ///
    /// @details gdy wskazano element znajdujący się w ostatnim wierszu wektora dwuwymiarowego zwrócony zostanie ten sam element (podany jako argument)
    ///
    /// @param[in] n współrzędna kolumny
    /// @param[in] m współrzędna wiersza
    /// @return referencja do elementu sąsiadującego od dołu ze wskazanym w argumencie
    ///
    T &zDolu(size_t t) {return t/N==M-1 ? at(t%N,t/N) : at(t%N,t/N+1);}

    ///
    /// @brief metoda przeciążona zwracająca referencję do elementu sąsiadującego od lewej ze wskazanym elementem <br>
    /// wskazanie elementu za pomocą współrzędnych dwuwymiarowych
    ///
    /// @details gdy wskazano element znajdujący się w pierwszej kolumnie wektora dwuwymiarowego zwrócony zostanie ten sam element (podany jako argument)
    ///
    /// @param[in] n współrzędna kolumny
    /// @param[in] m współrzędna wiersza
    /// @return referencja do elementu sąsiadującego od lewej ze wskazanym w argumencie
    ///
    T &zLewej(size_t n, size_t m) {return n==0 ? at(n,m) : at(n-1,m);}

    ///
    /// @brief metoda przeciążona zwracająca referencję do elementu sąsiadującego od lewej ze wskazanym elementem <br>
    /// wskazanie elementu za pomocą współrzędnej liniowej (kolejności elementu w odczycie liniowym wierszami poczynając od elementu (0,0))
    ///
    /// @details gdy wskazano element znajdujący się w pierwszej kolumnie wektora dwuwymiarowego zwrócony zostanie ten sam element (podany jako argument)
    ///
    /// @param[in] n współrzędna kolumny
    /// @param[in] m współrzędna wiersza
    /// @return referencja do elementu sąsiadującego od lewej ze wskazanym w argumencie
    ///
    T &zLewej(size_t t) {return t%N==0 ? at(t%N,t/N) : at(t%N-1,t/N);}

    ///
    /// @brief metoda przeciążona zwracająca referencję do elementu sąsiadującego od prawej ze wskazanym elementem <br>
    /// wskazanie elementu za pomocą współrzędnych dwuwymiarowych
    ///
    /// @details gdy wskazano element znajdujący się w ostatniej kolumnie wektora dwuwymiarowego zwrócony zostanie ten sam element (podany jako argument)
    ///
    /// @param[in] n współrzędna kolumny
    /// @param[in] m współrzędna wiersza
    /// @return referencja do elementu sąsiadującego od prawej ze wskazanym w argumencie
    ///
    T &zPrawej(size_t n, size_t m) {return n==N-1 ? at(n,m) : at(n+1,m);}

    ///
    /// @brief metoda przeciążona zwracająca referencję do elementu sąsiadującego od prawej ze wskazanym elementem <br>
    /// wskazanie elementu za pomocą współrzędnej liniowej (kolejności elementu w odczycie liniowym wierszami poczynając od elementu (0,0))
    ///
    /// @details gdy wskazano element znajdujący się w ostatniej kolumnie wektora dwuwymiarowego zwrócony zostanie ten sam element (podany jako argument)
    ///
    /// @param[in] n współrzędna kolumny
    /// @param[in] m współrzędna wiersza
    /// @return referencja do elementu sąsiadującego od prawej ze wskazanym w argumencie
    ///
    T &zPrawej(size_t t) {return t%N==N-1 ? at(t%N,t/N) : at(t%N+1,t/N);}
};

#endif // CARRAY2D_H
