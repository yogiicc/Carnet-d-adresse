/**
 * \file main.cpp
 *  \brief Programme principal.
 *  _\author KUT KEMAL et MURARASU LOUISE
 */
#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include "QSQLData.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSQLData bdSQL;
    MainWindow w;

    QObject::connect(&w, SIGNAL(sigdemandeExiste(Contact,bool&)), &bdSQL, SLOT(verifierContactExistant(Contact, bool&)));
    QObject::connect(&w, SIGNAL(ajouterContactBD(Contact)), &bdSQL, SLOT(ajouterContact(Contact)));
    QObject::connect(&w, SIGNAL(ajouterInteractionBD(QString,QString,Interaction&)), &bdSQL, SLOT(ajouterInteraction(QString,QString,Interaction&)));
    QObject::connect(&w, SIGNAL(ajouterTacheBD(int,Tache)), &bdSQL, SLOT(ajouterTache(int,Tache)));
    QObject::connect(&w, SIGNAL(listeContactsBD(vector<Contact>&)), &bdSQL, SLOT(listeContacts(vector<Contact>&)));
    QObject::connect(&w, SIGNAL(supprimerContactBD(Contact)),&bdSQL,SLOT(supprimerContact(Contact)));
    QObject::connect(&w, SIGNAL(modifierContactBD(QString,QString,Contact)),&bdSQL,SLOT(modifierContact(QString,QString,Contact)));
    QObject::connect(&w,SIGNAL(modifierInteractionBD(int,QString)),&bdSQL,SLOT(modifierInteraction(int,QString)));
    QObject::connect(&w, SIGNAL(listeInteractionsBD(QString,QString,QDate,QDate, vector<Interaction>&)), &bdSQL, SLOT(listeInteractions(QString,QString, QDate, QDate, vector<Interaction>&)));
    QObject::connect(&w,SIGNAL(listeTachesBD(QString,QString,QDate, QDate, vector<Tache>&)),&bdSQL,SLOT(listeTaches(QString,QString,QDate,QDate, vector<Tache>&)));
    QObject::connect(&w, SIGNAL(listeDatesBD(QString,QString,QDate, QDate, vector<QString>&)),&bdSQL,SLOT(listeDates(QString,QString,QDate, QDate, vector<QString>&)));
    QObject::connect(&w, SIGNAL(rechercheContactBD(vector<Contact>&, QString,QString,QString,QString,int)),&bdSQL, SLOT(rechercheContact(vector<Contact>&,QString,QString,QString,QString,int)));
    w.afficherContacts();
    w.show();
    return a.exec();
}
