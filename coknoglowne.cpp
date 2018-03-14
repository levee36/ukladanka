#include "coknoglowne.h"
#include "ui_coknoglowne.h"

COknoGlowne::COknoGlowne(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::COknoGlowne)
{
    ui->setupUi(this);
}

COknoGlowne::~COknoGlowne()
{
    delete ui;
}
