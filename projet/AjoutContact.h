/**
 * \file AjoutContact.h
 * \brief fichier de déclaration de la class AjoutContact.
 */
#ifndef AJOUTCONTACT_H
#define AJOUTCONTACT_H

#include <Contact.h>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpression>
#include <QFileDialog>

/**
 * \brief class Tache qui permet d'ouvrir un Dialog pour ajouter un Contact
 */
class AjoutContact : public QDialog
{
    Q_OBJECT

public:

    explicit AjoutContact(QWidget *parent = nullptr);
    ~AjoutContact();

private:
    QGridLayout *layout;

    QLabel *nomLabel;
    QLineEdit *nomEdit;

    QLabel *prenomLabel;
    QLineEdit *prenomEdit;

    QLabel *entrepriseLabel;
    QLineEdit *entrepriseEdit;

    QLabel *mailLabel;
    QLineEdit *mailEdit;

    QLabel *telLabel;
    QLineEdit *telEdit;

    QLabel *photoLabel;
    QLineEdit *photoEdit;
    QPushButton *bt_Photo;

    Contact nouveauContact;
    QPushButton *bt_Valider;

    bool verifieValide();

signals:
    void demandeContact(Contact, bool&);
    void envoyerContact(Contact);

private slots:
    void validerContact();
    void ajouterPhoto();

};

#endif // AJOUTCONTACT_H
