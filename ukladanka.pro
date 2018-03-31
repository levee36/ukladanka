#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T21:24:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ukladanka
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    GUI/coknoglowne.cpp \
    GUI/GUImsg/cguimsg.cpp \
    GUI/GUImsg/cguimsgzadaniekonfiguracji.cpp \
    GUI/GUImsg/cguimsginstrukcja.cpp \
    GUI/GUImsg/cguimsgkonfiguracja.cpp \
    GUI/GUImsg/cguimsgoprogramie.cpp \
    GUI/GUImsg/cguimsgresetuj.cpp \
    GUI/GUImsg/cguimsgrozwiaz.cpp \
    GUI/GUImsg/cguimsgtasuj.cpp \
    GUI/GUImsg/cguimsgustawieniareczne.cpp \
    GUI/GUImsg/cguimsgwcisnietepole.cpp \
    GUI/GUImsg/cguimsgwyjscie.cpp \
    GUI/cplansza.cpp \
    GUI/coknokonf.cpp \
    GUI/coknoinstrukcje.cpp \
    Kontroler/ckontroler.cpp \
    GUI/coknooprogramie.cpp \
    GUI/cpole.cpp

HEADERS += \
    GUI/coknoglowne.h \
    Kontroler/ckontroler.h \
    Kontroler/ikontroler.h \
    GUI/igui.h \
    GUI/coknoinstrukcje.h \
    GUI/coknooprogramie.h \
    GUI/coknokonf.h \
    GUI/GUImsg/cguimsg.h \
    GUI/GUImsg/cguimsgzadaniekonfiguracji.h \
    GUI/GUImsg/cguimsginstrukcja.h \
    GUI/GUImsg/cguimsgkonfiguracja.h \
    GUI/GUImsg/cguimsgoprogramie.h \
    GUI/GUImsg/cguimsgresetuj.h \
    GUI/GUImsg/cguimsgrozwiaz.h \
    GUI/GUImsg/cguimsgtasuj.h \
    GUI/GUImsg/cguimsgustawieniareczne.h \
    GUI/GUImsg/cguimsgwcisnietepole.h \
    GUI/GUImsg/cguimsgwyjscie.h \
    GUI/cplansza.h \
    GUI/coknokonf.h \
    GUI/coknoinstrukcje.h \
    GUI/cpole.h

FORMS += \
    GUI/coknokonf.ui \
    GUI/coknoglowne.ui \
    GUI/coknoinstrukcje.ui \
    GUI/coknooprogramie.ui

RESOURCES += \
    Resources/ikony.qrc
