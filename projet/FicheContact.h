/**
 * \file FicheContact.h
 * \brief fichier de déclaration de la class FicheContact.
 */
#ifndef FICHECONTACT_H
#define FICHECONTACT_H

#include "Contact.h"
#include "Interaction.h"
#include <QWidget>
#include <QDialog>
#include <QStateMachine>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include <sstream>
#include <string>
#include <QFileDialog>


namespace Ui {
class FicheContact;
}

/**
 * \brief class FicheContact qui permet d'ouvrir un Dialog pour visualiser un contact et ses informations.
 */
class FicheContact : public QDialog
{
    Q_OBJECT

    QStateMachine *state_modifierContact;
    QPushButton *bt_modifierContact;
    QStateMachine *state_modifierInteraction;
    QPushButton *bt_modifierInteraction;

public:
    FicheContact(const Contact &contact, QWidget *parent = nullptr);
    ~FicheContact();

    void afficherFiche();
    void remplirComboBox();
    bool verifierValide();
    void afficherInteractions();

private:
    Ui::FicheContact *ui;
    Contact contactActuel;

signals:
    void envoyerContactSupp( Contact contact);
    void envoyerContactModif(QString ancienNom, QString ancienPrenom, Contact contact);
    void envoyerInteraction(QString nom, QString prenom, Interaction &interaction);
    void envoyerTache(int id, Tache tache);
    void envoyerInteractionModif(int id, QString nouveauContenu);
    //void envoyerTacheSupp(Tache tache);

private slots:
    void supprimerContact();
    void modifierContact();
    void validerModifContact();
    void ajouterInteraction();
    void ajouterTache();
    void modifierInteraction();
    void validerModifInteraction();
    //void supprimerTache();
    void ajouterPhoto();
    void remplirCBTaches(int index);
};

#endif // FICHECONTACT_H
