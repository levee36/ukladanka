#ifndef COKNOKONF_H
#define COKNOKONF_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include "Kontroler/ikontroler.h"
#include <map>
#include <string>

namespace Ui {
class COknoKonf;
}

class COknoKonf : public QDialog
{
    Q_OBJECT

public:
    explicit COknoKonf(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent = 0);
    ~COknoKonf();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::COknoKonf *ui;
    IKontroler *kontroler;
    //wskaźniki na kontrolki modyfikowane przez konstruktor
    QLabel *label_ogrN;
    QLabel *label_ogrM;
    QSpinBox *spinBox_N;
    QSpinBox *spinBox_M;

    //ograniczenia dla ustawianego rozmiaru planszy
    int Nmin;
    int Nmax;
    int Mmin;
    int Mmax;
};

#endif // COKNOKONF_H
