#ifndef COKNOGLOWNE_H
#define COKNOGLOWNE_H

#include <QMainWindow>
#include <QCloseEvent>
#include <map>
#include <vector>
#include <array>
#include <string>
#include "GUI/igui.h"
#include "GUI/cplansza.h"
#include "Kontroler/ikontroler.h"

namespace Ui {
class COknoGlowne;
}

class COknoGlowne : public QMainWindow, public IGUI
{
    Q_OBJECT

public:
    explicit COknoGlowne(std::vector<int> tbl, int N, int M, IKontroler *kontroler, QWidget *parent = 0);
    ~COknoGlowne();
    bool rysujPlansze(std::vector<int> tbl, int N, int M);
    bool zamienPola(std::vector<std::array<int,2>> pary);
    bool wyswietlKonfiguracje(std::map<std::string,std::string> param);
    bool wyswietlStatus(std::string status);
    bool zamknijOkno();
    bool wyswietlOprogramie(std::map<std::string,std::string> param);
    bool wyswietlInstrukcje(std::map<std::string,std::string> param);

private slots:
    void on_actionKonfiguracja_triggered();
    void on_actionWyjscie_triggered();
    void on_actionTasuj_triggered();
    void on_actionRozwiaz_triggered();
    void on_actionResetuj_triggered();
    void on_actionReczneUstawianie_triggered(bool checked);
    void on_actionInstrukcje_triggered();
    void on_actionOprogramie_triggered();

private:
    void closeEvent(QCloseEvent *event);

    Ui::COknoGlowne *ui;
    CPlansza *plansza;
    IKontroler *kontroler;
};

#endif // COKNOGLOWNE_H
