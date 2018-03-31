#ifndef COKNOINSTRUKCJE_H
#define COKNOINSTRUKCJE_H

#include <QDialog>
#include <QLabel>
#include "Kontroler/ikontroler.h"
#include <map>
#include <string>

namespace Ui {
class COknoInstrukcje;
}

class COknoInstrukcje : public QDialog
{
    Q_OBJECT

public:
    explicit COknoInstrukcje(std::map<std::string, std::string> parametry, IKontroler *kontroler, QWidget *parent = 0);
    ~COknoInstrukcje();

private:
    Ui::COknoInstrukcje *ui;
    IKontroler *kontroler;
    //wskaźniki na kontrolki modyfikowane przez konstruktor
    QLabel *label_tekst;
};

#endif // COKNOINSTRUKCJE_H
