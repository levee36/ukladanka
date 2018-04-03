#include "GUI/coknoglowne.h"
#include <QApplication>

#include "Kontroler/ckontroler.h"
#include "GUI/coknoglowne.h"
#include "Model/Ukladanka/cmodelukladanka.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //twórz obiekt okno główne
    COknoGlowne *gui = new COknoGlowne();
    CKontroler *kontroler = new CKontroler(gui); //twórz pusty obiekt kontrolera ze wskaźnikiem do okna głównego


    gui->show();

    return a.exec();
}
