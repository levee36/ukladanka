#ifndef COKNOGLOWNE_H
#define COKNOGLOWNE_H

#include <QMainWindow>

namespace Ui {
class COknoGlowne;
}

class COknoGlowne : public QMainWindow
{
    Q_OBJECT

public:
    explicit COknoGlowne(QWidget *parent = 0);
    ~COknoGlowne();

private:
    Ui::COknoGlowne *ui;
};

#endif // COKNOGLOWNE_H
