#include "cwezelcompare.h"

bool CWezelCompare::operator()(CWezel *lewyOperand, CWezel *prawyOperand) const
{
    //sprawdzaj pole po polu aż do końca krótszego operanda
    for(int i=0;i<lewyOperand->getStan()->getN()*lewyOperand->getStan()->getM() && i<prawyOperand->getStan()->getN()*prawyOperand->getStan()->getM();i++) {
        int lewy = lewyOperand->getStan()->dostepLiniowy(i);
        int prawy = prawyOperand->getStan()->dostepLiniowy(i);
        if (lewy<prawy) return true; //lewy mniejszy od prawego - true
        else if (lewy>prawy) return false; //lewy większy od prawego - false
    }
    //jeśli pętla zakończyła działanie bez wywołania return - wszystkie elementy były identyczne
    //porównaj ilość elementów - jeśli lewyOperand miał mniej elementów - jest mniejszy od prawego - zwróć true
    //jeśli lewy ma tyle samo lub więcej elementów - na pewno nei jest mniejszy od prawego - zwróć false
    if (lewyOperand->getStan()->getN()*lewyOperand->getStan()->getM() < prawyOperand->getStan()->getN()*prawyOperand->getStan()->getM()) return true;
    else return false;
}
