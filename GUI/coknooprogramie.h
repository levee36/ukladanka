#ifndef COKNOOPROGRAMIE_H
#define COKNOOPROGRAMIE_H

#include <QDialog>
#include <QLabel>
#include "Kontroler/ikontroler.h"
#include <map>
#include <string>

namespace Ui {
class COknoOprogramie;
}

class COknoOprogramie : public QDialog
{
    Q_OBJECT

public:
    explicit COknoOprogramie(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent = 0);
    ~COknoOprogramie();

private:
    Ui::COknoOprogramie *ui;
    IKontroler *kontroler;
};

#endif // COKNOOPROGRAMIE_H
