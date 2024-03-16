/**
 * \file FicheContact.cpp
 * \brief fichier de la class FicheContact.h .
 */
#include "FicheContact.h"
#include "ui_UIFicheContact.h"

/**
 *@brief Constructeur avec paramètres de la class FicheContact.
 */
FicheContact::FicheContact(const Contact &contact, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FicheContact)
{
    ui->setupUi(this);

    //permet de afficher les informations du contact actuel dans les bons labels
    contactActuel = contact;

    afficherFiche();

    //bouton modifContact
    bt_modifierContact = ui->bt_modifier;
    state_modifierContact = new QStateMachine;

    QState *st1 = new QState;
    QState *st2 = new QState;

    state_modifierContact->addState(st1);
    state_modifierContact->addState(st2);

    st1->addTransition(bt_modifierContact, SIGNAL(clicked()),st2);
    st2->addTransition(bt_modifierContact, SIGNAL(clicked()),st1);

    connect(st2,SIGNAL(entered()), this, SLOT(modifierContact()));
    connect(st2,SIGNAL(exited()), this, SLOT(validerModifContact()));

    state_modifierContact->setInitialState(st1);
    state_modifierContact->start();

    //bouton modifierInteraction
    bt_modifierInteraction = ui->bt_modifInteraction;
    state_modifierInteraction = new QStateMachine;

    QState *st3 = new QState;
    QState *st4 = new QState;

    state_modifierInteraction->addState(st3);
    state_modifierInteraction->addState(st4);

    st3->addTransition(bt_modifierInteraction, SIGNAL(clicked()), st4);
    st4->addTransition(bt_modifierInteraction, SIGNAL(clicked()), st3);

    connect(st4, SIGNAL(entered()), this, SLOT(modifierInteraction()));
    connect(st4, SIGNAL(exited()), this, SLOT(validerModifInteraction()));

    state_modifierInteraction->setInitialState(st3);
    state_modifierInteraction->start();


    connect(ui->bt_photo, SIGNAL(clicked()), this, SLOT(ajouterPhoto()));
    //Lorsqu'on appuie sur le bouton supprimer, on emet le signal qui donne le contact à supprimer à la mainWindow
    connect(ui->bt_supprimer, SIGNAL(clicked()), this, SLOT(supprimerContact()));

    //Lorsqu on appuie sur le bouton ajouter Interaction
    connect(ui->bt_ajoutInteraction, SIGNAL(clicked()), this, SLOT(ajouterInteraction()));
    connect(ui->bt_ajoutTache,SIGNAL(clicked()), this, SLOT(ajouterTache()));

    //connect(ui->bt_suppTache, SIGNAL(clicked()), this, SLOT(supprimerTache()));

    connect(ui->cb_ChoixInteraction, SIGNAL(currentIndexChanged(int)), this, SLOT(remplirCBTaches(int)));
    qDebug() << "Connecté le signal currentIndexChanged de cb_ChoixInteraction";
    remplirComboBox();
    remplirCBTaches(ui->cb_ChoixInteraction->currentIndex());



}

/**
 *@brief Destructeur avec paramètres de la class AjoutContact.
 */
FicheContact::~FicheContact()
{
    delete ui;
}

/**
 *@brief Fonction permettant d'afficher la fiche d'un contact avec les bons paramaetres
 */
void FicheContact::afficherFiche()
{
    QString qnom = QString::fromStdString(contactActuel.getNom());
    ui->nomEdit->setText("" + qnom);
    ui->nomEdit->setReadOnly(true);

    QString qprenom = QString::fromStdString(contactActuel.getPrenom());
    ui->prenomEdit->setText("" + qprenom);
    ui->prenomEdit->setReadOnly(true);

    setWindowTitle("Fiche contact de " + qnom + " " + qprenom);

    QString qentreprise = QString::fromStdString(contactActuel.getEntreprise());
    ui->entrepriseEdit->setText("" + qentreprise);
    ui->entrepriseEdit->setReadOnly(true);

    QString qmail = QString::fromStdString(contactActuel.getMail());
    ui->mailEdit->setText("" + qmail);
    ui->mailEdit->setReadOnly(true);

    QString qtel = QString::fromStdString(contactActuel.getTel());
    ui->telEdit->setText("" + qtel);
    ui->telEdit->setReadOnly(true);

    QString qPhoto = QString::fromStdString(contactActuel.getPhoto());
    ui->photoEdit->setText("" + qPhoto);
    ui->photoEdit->setReadOnly(true);
    ui->lb_Photo->setPixmap(QPixmap(QString::fromStdString(contactActuel.getPhoto())));
    ui->le_modifInteraction->setReadOnly(true);

    QString qDateCreation = QString::fromStdString(contactActuel.getDateCreation());
    ui->lb_creation->setText(qDateCreation);

    QString qDateModif = QString::fromStdString(contactActuel.getDateModif());
    ui->lb_modif->setText(qDateModif);

}

/**
 *@brief Fonction permettant de supprimer un contact. On envoie un signal de suppression à la mainWindow
 */
void FicheContact::supprimerContact()
{
    emit envoyerContactSupp(contactActuel);
    this->close();
    delete this;
}

/**
 *@brief Fonction permettant de modifier un contact.
 */
void FicheContact::modifierContact()
{
    ui->nomEdit->setReadOnly(false);
    ui->prenomEdit->setReadOnly(false);
    ui->entrepriseEdit->setReadOnly(false);
    ui->mailEdit->setReadOnly(false);
    ui->telEdit->setReadOnly(false);

    bt_modifierContact->setText("Valider");
}

void FicheContact::ajouterPhoto(){
    ui->photoEdit->setText(QFileDialog::getOpenFileName(this,"Selectionnez une photo","/home","Images JPEG(*.jpeg *.jpg)"));
}

/**
 *@brief Fonction permettant de valider la modification d'un contact. On envoie un signal de modification à la mainWindow
 */
void FicheContact::validerModifContact()
{
    QString ancienNom = QString::fromStdString(contactActuel.getNom());
    QString ancienPrenom = QString::fromStdString(contactActuel.getPrenom());

    if(verifierValide()){

        qDebug() << "dedans le if";
    ui->nomEdit->setReadOnly(true);
    QString nouveauNom = ui->nomEdit->text();
    contactActuel.setNom(nouveauNom.toStdString());

    ui->prenomEdit->setReadOnly(true);
    QString nouveauPrenom = ui->prenomEdit->text();
    contactActuel.setPrenom(nouveauPrenom.toStdString());

    ui->entrepriseEdit->setReadOnly(true);
    QString nouvelleEntreprise = ui->entrepriseEdit->text();
    contactActuel.setEntreprise(nouvelleEntreprise.toStdString());

    ui->mailEdit->setReadOnly(true);
    QString nouveauMail = ui->mailEdit->text();
    contactActuel.setMail(nouveauMail.toStdString());

    ui->telEdit->setReadOnly(true);
    QString nouveauTel = ui->telEdit->text();
    contactActuel.setTel(nouveauTel.toStdString());

    ui->photoEdit->setReadOnly(true);
    QString nouvellePhoto = ui->photoEdit->text();
    ui->lb_Photo->setPixmap(QPixmap(ui->photoEdit->text()));
    contactActuel.setTel(nouvellePhoto.toStdString());


    //On envoie le contact modifier à la mainWindow
    emit envoyerContactModif(ancienNom, ancienPrenom, contactActuel);
    //recuperer la date et l'heure de modification pour envoyer à la base de données egalement
    }
    else{
    afficherFiche();
    }
    qDebug() << "apres le if";
    bt_modifierContact->setText("Modifier");
}

/**
 *@brief Fonction permettant d'ajouter une interaction. On envoie un signal  à la mainWindow
 */
void FicheContact::ajouterInteraction()
{
    QString textInteraction = ui->le_Interaction->text();
    if(!textInteraction.isEmpty())
    {
        Interaction i(textInteraction.toStdString());
        emit envoyerInteraction(QString::fromStdString(contactActuel.getNom()), QString::fromStdString(contactActuel.getPrenom()), i);
        contactActuel.ajouterInteraction(i);
        ui->le_Interaction->clear();
        remplirComboBox();
        afficherInteractions();
    }
}

/**
 *@brief Fonction permettant d'ajouter une tache On envoie un signal  à la mainWindow
 */
void FicheContact::ajouterTache()
{
    QString textTache = ui->le_Tache->text();
    if(!textTache.isEmpty())
    {
        QStringList numInteraction = ui->cb_ChoixInteraction->currentText().split(".");
        if(ui->dt_dateTache->text() == "01/01/2000 00:00")
        {
            Tache nouvelleTache(textTache.toStdString(), "");
            emit envoyerTache(contactActuel.getInteractionI(numInteraction[1].toInt()-1).getId(), nouvelleTache);
            contactActuel.getInteractionI(numInteraction[1].toInt()-1).ajouterTache(nouvelleTache);
            ui->le_Tache->clear();
        }
        else
        {
            QString dateTache = ui->dt_dateTache->text();
            Tache nouvelleTache(textTache.toStdString(), dateTache.toStdString());
            emit envoyerTache(contactActuel.getInteractionI(numInteraction[1].toInt()-1).getId(), nouvelleTache);
            contactActuel.getInteractionI(numInteraction[1].toInt()-1).ajouterTache(nouvelleTache);
            ui->le_Tache->clear();
        }
        remplirCBTaches(numInteraction[1].toInt()-1);
        afficherInteractions();
    }
}

/**
 *@brief Fonction permettant deverifier avant de faire les modifications sur un Contact. On envoie un signal  à la mainWindow
 */
bool FicheContact::verifierValide() {
    QString qnom = ui->nomEdit->text();
    QString qprenom = ui->prenomEdit->text();
    QString qmail = ui->mailEdit->text();
    QString qtel = ui->telEdit->text();
    QString qphoto = ui->photoEdit->text();

    qDebug() << "verif nom prenom";
    if (qnom.isEmpty() || qprenom.isEmpty()) {
        QMessageBox::critical(this, "ERREUR", "Le nom et le prénom ne peuvent pas être vides.\nFermer pour quitter sans ajouter de Contact.");
        return false;
    }

    qDebug()<<"verif photo";
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

    qDebug()<<"verif tel";
    // Vérification du numéro de téléphone (s'il n'est pas vide, il doit contenir uniquement des chiffres)
    if (!qtel.isEmpty() && !qtel.toInt()) {
        qDebug() << "Erreur : numéro de téléphone invalide.";
        return false;
    }

    qDebug()<< "verif mail";
    // Vérification de l'adresse e-mail
    static const QRegularExpression regex2("^[A-Za-z0-9.%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$|^$");
    QRegularExpressionMatch match2 = regex2.match(qmail);
    if (!match2.hasMatch()) {
        qDebug() << "Erreur : adresse e-mail invalide.";
        return false;
    }

    // Rajouter le signal pour doublon de contact
    return true;
}

/**
 *@brief Fonction permettant de modifier une interaction.
 */
void FicheContact::modifierInteraction()
{
    ui->le_modifInteraction->setReadOnly(false);
    QStringList numInteraction = ui->cb_ChoixInteraction->currentText().split(".");
    string ancienneInteraction = contactActuel.getlInteractions()[numInteraction[1].toInt()-1].getContenu();
    ui->le_modifInteraction->setText(QString::fromStdString(ancienneInteraction));
    bt_modifierInteraction->setText("Valider");
}

/**
 *@brief Fonction permettant de modifier une interaction. On envoie un signal  à la mainWindowcquand elle est correcte
 */
void FicheContact::validerModifInteraction()
{
    QString modifContenu = ui->le_modifInteraction->text();
    QStringList numInteraction = ui->cb_ChoixInteraction->currentText().split(".");
    int idInteraction = contactActuel.getlInteractions()[numInteraction[1].toInt()-1].getId();
    if(!modifContenu.isEmpty())
    {
        contactActuel.getInteractionI(numInteraction[1].toInt()-1).setContenu(modifContenu.toStdString());
        emit envoyerInteractionModif(idInteraction, modifContenu);
    }
    ui->le_modifInteraction->clear();
    afficherInteractions();
    ui->le_modifInteraction->setReadOnly(true);
    bt_modifierInteraction->setText("Modifier");
}
/*
void FicheContact::supprimerTache()
{
    int index  = ui->cb_taches->currentIndex();
    if(index >=0)
    {
        QStringList numInteraction = ui->cb_ChoixInteraction->currentText().split(".");
        int idInteraction = contactActuel.getlInteractions()[numInteraction[1].toInt()-1].getId();
        Tache t = contactActuel.getInteractionI(idInteraction).getlTaches()[index];
        emit envoyerTacheSupp(t);
    }
    else
    {
        qDebug() << "L'index de la tâche sélectionnée n'est pas valide.";
    }
}*/

/**
 *@brief Fonction permettant d'afficher les interactions. 
*/
void FicheContact::afficherInteractions()
{
    ui->zoneInteraction->clear();
    string s;
    vector<Interaction> li = contactActuel.getlInteractions();
    for(int n = 0; n < li.size();n++)
    {
        ostringstream affichageInteraction;
        affichageInteraction << li[n];
        s =  "Interaction n. " + to_string(n+1) + " : \n" + affichageInteraction.str();
        ui->zoneInteraction->append(QString::fromStdString(s));
    }
}

void FicheContact::remplirComboBox()
{
    ui->cb_ChoixInteraction->clear();
    for(int i = 0; i < contactActuel.getlInteractions().size(); i++)
    {
        ui->cb_ChoixInteraction->addItem(" Interaction n." + QString::number(i+1));
    }
}

void FicheContact::remplirCBTaches(int index)
{
    qDebug() << "Index sélectionné dans cb_ChoixInteraction : " << index;
    if(index>=0)
    {
        ui->cb_taches->clear();
        //On recupere le numero de l'interaction dans la comboBox
        //on recupere la liste de taches de cette interaction
        vector<Tache> lTaches = contactActuel.getlInteractions()[index].getlTaches();
        for(int i = 0; i < lTaches.size(); i++)
        {
            ui->cb_taches->addItem("@todo " + QString::fromStdString(lTaches[i].getContenu()));
        }
    }
}
