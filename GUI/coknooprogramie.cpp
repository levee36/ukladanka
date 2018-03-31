#include "coknooprogramie.h"
#include "ui_coknooprogramie.h"

COknoOprogramie::COknoOprogramie(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent) :
    QDialog(parent),
    kontroler(kontroler),
    ui(new Ui::COknoOprogramie)
{
    ui->setupUi(this);
    //szukaj w mapie wartości dla kluczy i ustawiaj wg nich kontrolki
    std::map<std::string, std::string>::iterator it; //iterator do przeglądania danych w mapie
    it = parametry.find("tytul");
    if (it!=parametry.end()) ui->label_tytul->setText(QString::fromStdString((*it).second));
    else ui->label_tytul->setText(QString("<pusty>"));
    it = parametry.find("podtytul");
    if (it!=parametry.end()) ui->label_podtytul->setText(QString::fromStdString((*it).second));
    else ui->label_podtytul->setText(QString("<pusty>"));
    it = parametry.find("autor");
    if (it!=parametry.end()) ui->label_autor->setText(QString::fromStdString((*it).second));
    else ui->label_autor->setText(QString("<pusty>"));
}

COknoOprogramie::~COknoOprogramie()
{
    delete ui;
}
