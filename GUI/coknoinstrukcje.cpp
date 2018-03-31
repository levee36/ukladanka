#include "coknoinstrukcje.h"
#include "ui_coknoinstrukcje.h"

COknoInstrukcje::COknoInstrukcje(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent) :
    QDialog(parent),
    kontroler(kontroler),
    ui(new Ui::COknoInstrukcje)
{
    ui->setupUi(this);
    //przypisz kontrolki wczytane z pliku ui do wskaźników klasy
    label_tekst = this->findChild<QLabel*>("label_tekst");
    //szukaj w mapie wartości dla kluczy i ustawiaj wg nich kontrolki
    std::map<std::string, std::string>::iterator it; //iterator do przeglądania danych w mapie
    it = parametry.find("instrukcje");
    if (it!=parametry.end()) label_tekst->setText(QString::fromStdString((*it).second));
    else label_tekst->setText(QString("<pusty>"));
}

COknoInstrukcje::~COknoInstrukcje()
{
    delete ui;
}
