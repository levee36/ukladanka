#include "GUI\coknoglowne.h"
#include <QApplication>

#include <Kontroler/ckontroler.h>
#include <GUI/coknoglowne.h>

#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CKontroler *kontroler = new CKontroler();

    int c[] = {1,2,3,4,5,6,7,8,0,2,11,23,43,12,33,44,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    std::vector<int> ciag (c, c + sizeof(c) / sizeof(int) );

    COknoGlowne *gui = new COknoGlowne(ciag,6,6,kontroler);
    kontroler->setGUI(gui);
    gui->show();

    return a.exec();
}
