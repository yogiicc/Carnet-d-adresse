#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include "AjoutContact.h"
#include "FicheContact.h"
#include "Contact.h"
#include "GestionTache.h"
#include "GestionInteraction.h"
#include "GestionContact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

    GestionContact gestionContact;
    GestionInteraction gestionInteraction;
    GestionTache gestionTache;
    AjoutContact *ajoutContact;
    FicheContact *ficheContact;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void afficherContacts();
    void afficherNbContacts();
    void remplirCBContacts();

private slots:
    void ouvrirAjoutContact();
    void demandeContactBD(Contact, bool&);
    void recevoirContact(Contact nouveauContact);

    void ouvrirFicheContact(const Contact contact);
    void supprimerContact(const Contact contact);
    void modifierContact(QString, QString, const Contact contact);
    void recevoirInteraction(QString, QString, Interaction &nouvelleInteraction);
    void modifierInteraction(int id, QString nouveauContenu);
    void recevoirTache(int id, Tache nouvelleTache);

    void afficherInteractions();
    void afficherTaches();
    void afficherDates();

    //void afficherOrdreDateCreation();
    void rechercherContact();

signals:
    void sigdemandeExiste(Contact, bool&);
    void ajouterContactBD(Contact nouveauContact);
    void supprimerContactBD(Contact contactASupp);

    void ajouterInteractionBD(QString, QString, Interaction&);
    void ajouterTacheBD(int, Tache);
    void modifierContactBD(QString,QString,Contact);
    void modifierInteractionBD(int,QString);

    void listeContactsBD(vector<Contact> &lContacts);
    void listeInteractionsBD(QString, QString, QDate, QDate, vector<Interaction> &lInteractions);
    void listeTachesBD(QString, QString,QDate, QDate, vector<Tache> &lTaches);
    void listeDatesBD(QString, QString, QDate, QDate, vector<QString> &lDates);

    void rechercheContactBD(vector<Contact>&, QString,QString,QString,QString,int);

};
#endif // MAINWINDOW_H
