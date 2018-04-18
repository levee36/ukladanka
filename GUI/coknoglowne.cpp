#include "coknoglowne.h"
#include "ui_coknoglowne.h"
#include "coknoinstrukcje.h"
#include "coknokonf.h"
#include "coknooprogramie.h"
#include "coknopopup.h"
#include "GUImsg/cguimsgzadaniekonfiguracji.h"
#include "GUImsg/cguimsgwyjscie.h"
#include "GUImsg/cguimsgtasuj.h"
#include "GUImsg/cguimsgrozwiaz.h"
#include "GUImsg/cguimsgresetuj.h"
#include "GUImsg/cguimsgustawieniareczne.h"
#include "GUImsg/cguimsginstrukcja.h"
#include "GUImsg/cguimsgoprogramie.h"


COknoGlowne::COknoGlowne(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::COknoGlowne)
{
    ui->setupUi(this);
    plansza = new CPlansza(std::vector<int>(1,-1),1,1,0,this);
    popup = 0;
}

COknoGlowne::~COknoGlowne()
{
    delete plansza;
    delete ui;
}

void COknoGlowne::setKontroler(IKontroler *kontroler)
{
    this->kontroler = kontroler;
}

//definicje metod z interfejsu IGUI
bool COknoGlowne::rysujPlansze(std::vector<int> tbl, int N, int M) {
    delete plansza;
    plansza = new CPlansza(tbl,N,M,kontroler,this);
    ui->gridLayout->addWidget(plansza,0,0);
    return true;
}

bool COknoGlowne::zamienPola(std::vector<std::array<int,2>> pary) {
    return plansza->zamienPola(pary);
}

bool COknoGlowne::setUstawianieReczne(bool ustawianie)
{
    ui->actionReczneUstawianie->setChecked(ustawianie);
    return true;
}

bool COknoGlowne::wyswietlKonfiguracje(std::map<std::string,std::string> param) {
    COknoKonf *konf = new COknoKonf(param,kontroler,this);
    konf->exec();
    return true;
}

bool COknoGlowne::wyswietlStatus(std::string status) {
    this->statusBar()->showMessage(QString::fromStdString(status));
    return true;
}

bool COknoGlowne::zamknijOkno() {
    close();
    return true;
}

bool COknoGlowne::wyswietlOprogramie(std::map<std::string,std::string> param) {
    COknoOprogramie *oprogramie = new COknoOprogramie(param,kontroler,this);
    oprogramie->exec();
    return true;
}

bool COknoGlowne::wyswietlInstrukcje(std::map<std::string,std::string> param) {
    COknoInstrukcje *instrukcje = new COknoInstrukcje(param,kontroler,this);
    instrukcje->exec();
    return true;
}

bool COknoGlowne::wyswietlOknoPopup(std::map<std::string, std::string> param)
{
    popup = new COknoPopup(param,kontroler,this);
    QObject::connect(popup,SIGNAL(zamykany()), SLOT(zamknieciePopup()));
    popup->exec();
    return true;
}

bool COknoGlowne::zamknijOknoPopup()
{
    if (popup!=0) popup->close();
}

void COknoGlowne::on_actionKonfiguracja_triggered()
{
    kontroler->wyslijWiadomosc(new CGUIMsgZadanieKonfiguracji());
}

void COknoGlowne::on_actionWyjscie_triggered()
{
    close();
}

void COknoGlowne::on_actionTasuj_triggered()
{
    kontroler->wyslijWiadomosc(new CGUIMsgTasuj());
}

void COknoGlowne::on_actionRozwiaz_triggered()
{
    kontroler->wyslijWiadomosc(new CGUIMsgRozwiaz());
}

void COknoGlowne::on_actionResetuj_triggered()
{
    kontroler->wyslijWiadomosc(new CGUIMsgResetuj());
}

void COknoGlowne::on_actionReczneUstawianie_triggered(bool checked)
{
    kontroler->wyslijWiadomosc(new CGUIMsgUstawianieReczne(checked));
}

void COknoGlowne::on_actionInstrukcje_triggered()
{
    kontroler->wyslijWiadomosc(new CGUIMsgInstrukcja());
}

void COknoGlowne::on_actionOprogramie_triggered()
{
    kontroler->wyslijWiadomosc(new CGUIMsgOprogramie());
}

void COknoGlowne::zamknieciePopup()
{
    popup=0;
}

void COknoGlowne::closeEvent(QCloseEvent *event)
{
    kontroler->wyslijWiadomosc(new CGUIMsgWyjscie());
    event->accept();
}
