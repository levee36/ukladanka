#include "coknopopup.h"
#include "ui_coknopopup.h"

#include <QPushButton>
#include "GUImsg/cguimsgpopup.h"

COknoPopup::COknoPopup(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent) :
    QDialog(parent),
    kontroler(kontroler),
    ui(new Ui::COknoPopup)
{
    ui->setupUi(this);
    //szukaj w mapie wartości dla kluczy i ustawiaj wg nich kontrolki
    std::map<std::string, std::string>::iterator it; //iterator do przeglądania danych w mapie
    it = parametry.find("tytul");
    if (it!=parametry.end()) this->setWindowTitle(QString::fromStdString((*it).second));
    else this->setWindowTitle(QString::fromStdString((*it).second));
    it = parametry.find("tresc");
    if (it!=parametry.end()) ui->label_tresc->setText(QString::fromStdString((*it).second));
    else ui->label_tresc->setText(QString("<pusty>"));
    it = parametry.find("przycisk");
    if (it!=parametry.end()) ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QString::fromStdString((*it).second));
    else ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QString("OK"));
}

COknoPopup::~COknoPopup()
{
    delete ui;
}

void COknoPopup::on_buttonBox_accepted()
{
    emit zamykany(); //emituje sygnał do komunikacji zamknięcia dla okna głownego (żeby wyzerować wskaźnik na aktywne okno popup)
    kontroler->wyslijWiadomosc(new CGUIMsgPopup(ui->buttonBox->button(QDialogButtonBox::Ok)->text().toStdString()));
}

void COknoPopup::on_buttonBox_rejected()
{
    emit zamykany(); //emituje sygnał do komunikacji zamknięcia dla okna głownego (żeby wyzerować wskaźnik)
    kontroler->wyslijWiadomosc(new CGUIMsgPopup(ui->buttonBox->button(QDialogButtonBox::Ok)->text().toStdString()));
}

void COknoPopup::closeEvent(QCloseEvent *event)
{
    emit zamykany(); //emituje sygnał do komunikacji zamknięcia dla okna głownego (żeby wyzerować wskaźnik)
    kontroler->wyslijWiadomosc(new CGUIMsgPopup(ui->buttonBox->button(QDialogButtonBox::Ok)->text().toStdString()));
    event->accept();
}
