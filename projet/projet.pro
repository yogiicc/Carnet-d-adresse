QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AjoutContact.cpp \
    Contact.cpp \
    FicheContact.cpp \
    GestionContact.cpp \
    GestionInteraction.cpp \
    GestionTache.cpp \
    Interaction.cpp \
    QSQLData.cpp \
    Tache.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AjoutContact.h \
    Contact.h \
    FicheContact.h \
    GestionContact.h \
    GestionInteraction.h \
    GestionTache.h \
    Interaction.h \
    QSQLData.h \
    Tache.h \
    mainwindow.h

FORMS += \
    UIFicheContact.ui \
    UImainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
