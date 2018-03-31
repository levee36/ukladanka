#include "coknokonf.h"
#include "ui_coknokonf.h"
#include "GUImsg/cguimsgkonfiguracja.h"

COknoKonf::COknoKonf(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent) :
    QDialog(parent),
    kontroler(kontroler),
    ui(new Ui::COknoKonf)
{
    ui->setupUi(this);
    //przypisz kontrolki wczytane z pliku ui do wskaźników klasy
    label_ogrM = this->findChild<QLabel*>("label_ogrM");
    label_ogrN = this->findChild<QLabel*>("label_ogrN");
    spinBox_M = this->findChild<QSpinBox*>("spinBox_M");
    spinBox_N = this->findChild<QSpinBox*>("spinBox_N");

    //szukaj w mapie wartości dla kluczy i ustawiaj wg nich kontrolki
    int Nvalue = 3; //wartość domyślna dla liczby kolumn
    int Mvalue = 3; //wartość domyślna dla liczby wierszy
    std::map<std::string, std::string>::iterator it; //iterator do przeglądania danych w mapie
    it = parametry.find("N");
    if (it!=parametry.end()) Nvalue =std::stoi((*it).second);
    it = parametry.find("N_min");
    if (it!=parametry.end()) Nmin = std::stoi((*it).second);
    else Nmin = 2;
    it = parametry.find("N_max");
    if (it!=parametry.end()) Nmax = std::stoi((*it).second);
    else Nmax = 8;
    it = parametry.find("M");
    if (it!=parametry.end()) Mvalue=std::stoi((*it).second);
    it = parametry.find("M_min");
    if (it!=parametry.end()) Mmin = std::stoi((*it).second);
    else Mmin = 2;
    it = parametry.find("M_max");
    if (it!=parametry.end()) Mmax = std::stoi((*it).second);
    else Mmax = 8;
    //ustaw zakres spinboxów zgodnie z przekazanymi parametrami
    spinBox_M->setMaximum(Mmax);
    spinBox_M->setMinimum(Mmin);
    spinBox_N->setMaximum(Nmax);
    spinBox_N->setMinimum(Nmin);
    //ustaw wartości spinboxów
    spinBox_M->setValue(Mvalue);
    spinBox_N->setValue(Nvalue);
    //ustaw info o zkaresie w etykietach
    label_ogrM->setText(QString("min.")+QString::number(Mmin)+QString(" max.")+QString::number(Mmax));
    label_ogrN->setText(QString("min.")+QString::number(Nmin)+QString(" max.")+QString::number(Nmax));

}

COknoKonf::~COknoKonf()
{
    delete ui;
}

void COknoKonf::on_buttonBox_accepted()
{
    kontroler->wyslijWiadomosc(new CGUIMsgKonfiguracja(spinBox_N->value(),spinBox_M->value()));
}
