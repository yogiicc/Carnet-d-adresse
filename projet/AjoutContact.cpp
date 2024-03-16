/**
 * \file AjoutContact.cpp
 * \brief fichier de la class AjoutContact.h .
 */
#include "AjoutContact.h"
#include <QDebug>
#include <QMessageBox>

using namespace std;

/**
 *@brief Constructeur avec paramètres de la class AjoutContact.
 */
AjoutContact::AjoutContact(QWidget *parent)
{

    layout = new QGridLayout(this);

    nomLabel = new QLabel("Nom : ",this);
    nomEdit = new QLineEdit;

    prenomLabel = new QLabel("Prenom : ",this);;
    prenomEdit = new QLineEdit;

    entrepriseLabel = new QLabel("Entreprise : ",this);
    entrepriseEdit= new QLineEdit;

    mailLabel = new QLabel("E-mail : ",this);
    mailEdit = new QLineEdit;

    telLabel = new QLabel("Telephone : ",this);
    telEdit = new QLineEdit;

    photoLabel = new QLabel("URL Photo : ",this);
    photoEdit = new QLineEdit;
    photoEdit->setReadOnly(true);
    bt_Photo = new QPushButton("Choississez une photo");

    bt_Valider = new QPushButton("Valider",this);

    layout->addWidget(nomLabel,0,0);
    layout->addWidget(nomEdit,0,1);

    layout->addWidget(prenomLabel,1,0);
    layout->addWidget(prenomEdit,1,1);

    layout->addWidget(entrepriseLabel,2,0);
    layout->addWidget(entrepriseEdit,2,1);

    layout->addWidget(mailLabel,3,0);
    layout->addWidget(mailEdit,3,1);

    layout->addWidget(telLabel,4,0);
    layout->addWidget(telEdit,4,1);

    layout->addWidget(photoLabel,5,0);
    layout->addWidget(photoEdit,5,1);
    layout->addWidget(bt_Photo,6,1);

    layout->addWidget(bt_Valider,7,0,1,2);

    setLayout(layout);

    connect(bt_Valider, SIGNAL(clicked()),this, SLOT(validerContact()));
    connect(bt_Photo,SIGNAL(clicked()),this,SLOT(ajouterPhoto()));
}
/**
 *@brief Destructeur avec paramètres de la class AjoutContact.
 */
AjoutContact::~AjoutContact(){}

/**
 *@brief Fonction permetttant de valider la creation d'un contact et d'envoyer le signal à la mainWindow avec le nouveauContact
 */
void AjoutContact::validerContact()
{
    QString qnom = nomEdit->text();
    QString qprenom = prenomEdit->text();
    QString qentreprise = entrepriseEdit->text();
    QString qmail =  mailEdit->text();
    QString qtel = telEdit->text();
    QString qphoto = photoEdit->text();

    if(verifieValide()){
        string nom = qnom.toStdString();
        string prenom = qprenom.toStdString();
        string entreprise = qentreprise.toStdString();
        string mail = qmail.toStdString();
        string tel = qtel.toStdString();
        string urlphoto = qphoto.toStdString();

        //Créer le nouveau contact, on envoie le signal à la mainwindow avec le Contact.
        Contact nouveauContact(nom, prenom, entreprise, mail, tel, urlphoto, "", "");
        //On emmet le signal avec les informations actuelles du Contact
        emit envoyerContact(nouveauContact);
        //On ferme le widget
        close();
        delete this;
    }
}

/**
 *@brief fonction permettant d'ouvrir un widget pour ajouter une photo
 */
void AjoutContact::ajouterPhoto(){
    photoEdit->setText(QFileDialog::getOpenFileName(this,"Selectionnez une photo","/home","Images JPEG(*.jpeg *.jpg)"));
}

/**
 *@brief Fonction qui permet de verifier que toute les valeurs affectées par le client sont correctes
 *@param bool renvoie true si tout est correct sinon false
 */
bool AjoutContact::verifieValide() {
    QString qnom = nomEdit->text();
    QString qprenom = prenomEdit->text();
    QString qmail = mailEdit->text();
    QString qtel = telEdit->text();
    QString qphoto = photoEdit->text();

    if (qnom.isEmpty() || qprenom.isEmpty()) {
        QMessageBox::critical(this, "ERREUR", "Le nom et le prénom ne peuvent pas être vides.\nFermer pour quitter sans ajouter de Contact.");
        return false;
    }

    /* Vérification de la validité du chemin de la photo
    static const QRegularExpression regex("\\b[A-Za-z0-9.%+-]+\\.(jpg|jpeg)\\b|^$");
    if (!regex.match(qphoto).hasMatch()) {
        qDebug() << "Erreur : chemin de la photo invalide.";
        return false;
    }*/

    // Vérification de la validité du chemin de la photo
    static const QRegularExpression regex("\\b.*\\.(jpg|jpeg)\\b|^$");
    if (!regex.match(qphoto).hasMatch()) {
        qDebug() << "Erreur : chemin de la photo invalide.";
        return false;
    }



    // Vérification du numéro de téléphone (s'il n'est pas vide, il doit contenir uniquement des chiffres)
    if (!qtel.isEmpty() && !qtel.toInt()) {
        qDebug() << "Erreur : numéro de téléphone invalide.";
        return false;
    }

    // Vérification de l'adresse e-mail
    static const QRegularExpression regex2("^[A-Za-z0-9.%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$|^$");
    QRegularExpressionMatch match2 = regex2.match(qmail);
    if (!match2.hasMatch()) {
        qDebug() << "Erreur : adresse e-mail invalide.";
        return false;
    }

    bool existant = false;
    emit demandeContact(nouveauContact, existant);
    qDebug() << "valeur du bool existant " << existant;
    if(existant)
    {
        return false;
    }
    return true;
}

