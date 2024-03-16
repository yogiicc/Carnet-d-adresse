/**
 * \file mainwindow.cpp
 * \brief fichier de la class mainwindow.h .
 */
#include "mainwindow.h"
#include "ui_UImainwindow.h"

#include <QDebug>

/**
 *@brief Constructeur de la class mainwindow.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Lorsqu'on clique sur le bouton "Ajouter Contact" de la barre de Menu, apparition d'une nouvelle fenetre
    QObject::connect(ui->actionAJouter_Contact, SIGNAL(triggered()), this, SLOT(ouvrirAjoutContact()));
    QObject::connect(ui->bt_interactions,SIGNAL(clicked()),this,SLOT(afficherInteractions()));
    QObject::connect(ui->bt_taches,SIGNAL(clicked()),this,SLOT(afficherTaches()));
    QObject::connect(ui->bt_dates,SIGNAL(clicked()),this,SLOT(afficherDates()));

    QObject::connect(ui->bt_rechercher, SIGNAL(clicked()), this, SLOT(rechercherContact()));


}
/**
 *@brief Destructuer de la class FicheContact.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 *@brief fonction qui permet d'ouvrir la page pour ajouter un contact
 */
void MainWindow::ouvrirAjoutContact()
{
    //ouvrir le widget pour ajouter un contact
    ajoutContact = new AjoutContact(this);
    ajoutContact->show();
    ajoutContact->raise();
    ajoutContact->setModal(true);

    connect(ajoutContact, SIGNAL(demandeContact(Contact,bool&)), this, SLOT(demandeContactBD(Contact,bool&)));
    connect(ajoutContact, SIGNAL(envoyerContact(Contact)), this, SLOT(recevoirContact(Contact)));
}

/**
 *@brief fonction qui permet d'ouvrir la page pour visualiser un contact
 */
void MainWindow::ouvrirFicheContact( Contact contact)
{
    //ouvrir le widget pour visualiser un contact
    ficheContact = new FicheContact(contact, this);
    ficheContact->show();
    ficheContact->raise();
    ficheContact->setModal(true);
    ficheContact->afficherInteractions();

    connect(ficheContact, SIGNAL(envoyerContactSupp(Contact)), this, SLOT(supprimerContact(Contact)));
    connect(ficheContact, SIGNAL(envoyerContactModif(QString,QString,Contact)), this, SLOT(modifierContact(QString,QString,Contact)));
    connect(ficheContact, SIGNAL(envoyerInteraction(QString, QString, Interaction&)), this, SLOT(recevoirInteraction(QString, QString,Interaction&)));
    connect(ficheContact, SIGNAL(envoyerInteractionModif(int,QString)), this, SLOT(modifierInteraction(int,QString)));
    connect(ficheContact, SIGNAL(envoyerTache(int,Tache)), this, SLOT(recevoirTache(int,Tache)));
}

/**
 *@brief Fonctions qui emettent des siganux à la base de données pour les modifications sur un contact ainsi que les suppresions
 */
void MainWindow::demandeContactBD(Contact c, bool &existant)
{
    emit sigdemandeExiste(c, existant);
}

void MainWindow::recevoirContact(Contact nouveauContact)
{
    emit ajouterContactBD(nouveauContact);
    afficherContacts();
}


void MainWindow::supprimerContact(Contact contactASupp)
{
    emit supprimerContactBD(contactASupp);
    afficherContacts();
}

void MainWindow::modifierContact(QString ancienNom, QString ancienPrenom, Contact contactModif)
{
    emit modifierContactBD(ancienNom,ancienPrenom,contactModif);
    afficherContacts();
}

void MainWindow::recevoirInteraction(QString nom, QString prenom, Interaction &nouvelleInteraction)
{
    emit ajouterInteractionBD(nom, prenom, nouvelleInteraction);
    afficherContacts();
}

void MainWindow::recevoirTache(int id, Tache nouvelleTache)
{
    emit ajouterTacheBD(id, nouvelleTache);
    afficherContacts();
}

void MainWindow::modifierInteraction(int id, QString nouveauContenu)
{
    emit modifierInteractionBD(id,nouveauContenu);
    afficherContacts();
}


/**
 *@brief Fonction qui permet d'afficher les contacts sous formes de boutons et d'initialiser les gestionnaires
 */
void MainWindow::afficherContacts()
{
    for(auto contact:gestionContact.getlContacts())
    {
        gestionContact.supprimerContact(contact.getNom(), contact.getPrenom(), gestionInteraction, gestionTache);
    }
    vector<Contact> lContacts;
    emit listeContactsBD(lContacts);

    //On nettoie le layout pour ne pas avoir des boutons en double
    QVBoxLayout *ly_listeContacts = ui->ly_listeContacts;
    QLayoutItem *item;

    while((item = ly_listeContacts->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }


    for(auto contact:lContacts)
    {
        gestionContact.ajouterContact(contact);
        for(auto interaction:contact.getlInteractions())
        {
            gestionInteraction.ajouterInteraction(interaction);
            for(auto tache:interaction.getlTaches())
            {
                gestionTache.ajouterTache(tache);
            }
        }
    }
    //On peut maintenant ajouter les nouveaux boutons
    vector<Contact> listeContacts = gestionContact.getlContacts();
    for(const Contact &contact : listeContacts)
    {
        QString texteBouton = QString::fromStdString(contact.getNom()+ " " + contact.getPrenom());
        QPushButton *bouton = new QPushButton(texteBouton);
        bouton->setFixedSize(QSize(200, 50));
        ly_listeContacts->addWidget(bouton);

        //quand on clique sur le bouton d'un contact, on ouvre la fiche contact correspondante
        QObject::connect(bouton, &QPushButton::clicked,this,[this, contact](){
            ouvrirFicheContact(contact);
        });
    }
    QWidget *scrollWidget = new QWidget;
    scrollWidget->setLayout(ly_listeContacts);
    ui->scrollArea->setWidget(scrollWidget);
    ui->scrollArea->setWidgetResizable(true);

    afficherNbContacts();
    remplirCBContacts();
}

void MainWindow::afficherNbContacts()
{
    size_t nbContacts = gestionContact.getlContacts().size();
    int nbContactsInt = static_cast<int>(nbContacts);
    ui->lb_nbContacts->setText("Nombre de Contacts : " + QString::number(nbContactsInt));
}


//remplir la combo box avec la liste de Contacts de la BD
void MainWindow::remplirCBContacts()
{
    ui->cb_contatcs->clear();
    vector<Contact> listeContacts = gestionContact.getlContacts();
    ui->cb_contatcs->addItem("ALL");
    for(int i = 0; i < gestionContact.getlContacts().size(); i++)
    {
        ui->cb_contatcs->addItem(QString::fromStdString(gestionContact.getlContacts()[i].getNom()) + " " + QString::fromStdString(gestionContact.getlContacts()[i].getPrenom()));
    }
}

void MainWindow::afficherInteractions()
{
    ui->textEdit->clear();
    QString contact = ui->cb_contatcs->currentText();
    QString dateDebut = ui->dtDebut->text();
    QString dateFin = ui->dtFin->text();
    if (contact == "ALL")
    {
        if(dateDebut == "01/01/2000" && dateFin == "01/01/2000")
        {
            string s;
            ostringstream affichageInteractions;
            affichageInteractions << gestionInteraction;
            s = affichageInteractions.str();
            ui->textEdit->append(QString::fromStdString(s));
        }
        else if( dateDebut != "01/01/2000" && dateFin == "01/01/2000")
        {
            for(int i=0; i < gestionInteraction.getlInteractions().size();i++)
            {
                QDate dated = QDate::fromString(dateDebut, "yyyy-MM-dd");
                QDate dateI = QDate::fromString(QString::fromStdString(gestionInteraction.getlInteractions()[i].getDateCreation()), "yyyy-MM-dd");
                if(dateI >= dated)
                {
                    string s;
                    ostringstream affichageInteraction;
                    affichageInteraction << gestionInteraction.getlInteractions()[i];
                    s = affichageInteraction.str();
                    ui->textEdit->append(QString::fromStdString(s));
                }
            }
        }
        else if( dateDebut == "01/01/2000" && dateFin != "01/01/2000")
        {
            for(int i=0; i < gestionInteraction.getlInteractions().size();i++)
            {
                QDate datef = QDate::fromString(dateFin, "yyyy-MM-dd");
                QDate dateI = QDate::fromString(QString::fromStdString(gestionInteraction.getlInteractions()[i].getDateCreation()), "yyyy-MM-dd");
                if(dateI <= datef)
                {
                    string s;
                    ostringstream affichageInteraction;
                    affichageInteraction << gestionInteraction.getlInteractions()[i];
                    s = affichageInteraction.str();
                    ui->textEdit->append(QString::fromStdString(s));
                }
            }
        }
        else if( dateDebut != "01/01/2000" && dateFin != "01/01/2000")
        {
            for(int i=0; i < gestionInteraction.getlInteractions().size();i++)
            {
                 QDate dated = QDate::fromString(dateDebut, "yyyy-MM-dd");
                QDate datef = QDate::fromString(dateFin, "yyyy-MM-dd");
                QDate dateI = QDate::fromString(QString::fromStdString(gestionInteraction.getlInteractions()[i].getDateCreation()), "yyyy-MM-dd");
                if(dateI >= dated && dateI <= datef)
                {
                    string s;
                    ostringstream affichageInteraction;
                    affichageInteraction << gestionInteraction.getlInteractions()[i];
                    s = affichageInteraction.str();
                    ui->textEdit->append(QString::fromStdString(s));
                }
            }
        }
    }
    else
    {
        //on recupere les interactions du contact demande
        QStringList contact = ui->cb_contatcs->currentText().split(" ");
        QString nom = contact[0];
        QString prenom = contact[1];
        QDate dated = QDate::fromString(dateDebut, "yyyy-MM-dd 00:00:00");
        QDate datef = QDate::fromString(dateFin, "yyyy-MM-dd 00:00:00");
        vector<Interaction> lInteractions;
        emit listeInteractionsBD(nom, prenom, dated, datef, lInteractions);
        for(int i = 0; i < lInteractions.size(); i++)
        {
            string s;
            ostringstream affichageInteractions;
            affichageInteractions << lInteractions[i];
            s = affichageInteractions.str();
            ui->textEdit->append(QString::fromStdString(s));
        }
    }
}

void MainWindow::afficherTaches()
{
    ui->textEdit->clear();
    QString contact = ui->cb_contatcs->currentText();
    QString dateDebut = ui->dtDebut->text();
    QString dateFin = ui->dtFin->text();
    if (contact == "ALL")
    {
        if(dateDebut == "01/01/2000" && dateFin == "01/01/2000")
        {
            string s;
            ostringstream affichageTaches;
            affichageTaches << gestionTache;
            s = affichageTaches.str();
            ui->textEdit->append(QString::fromStdString(s));
        }
        else if( dateDebut != "01/01/2000" && dateFin == "01/01/2000")
        {
            for(int i=0; i < gestionTache.getlTaches().size();i++)
            {
                QDate dated = QDate::fromString(dateDebut, "yyyy-MM-dd");
                QDate dateI = QDate::fromString(QString::fromStdString(gestionTache.getlTaches()[i].getDateTache()), "yyyy-MM-dd");
                if(dateI >= dated)
                {
                    string s;
                    ostringstream affichageTaches;
                    affichageTaches << gestionTache.getlTaches()[i];
                    s = affichageTaches.str();
                    ui->textEdit->append(QString::fromStdString(s));
                }
            }
        }
        else if( dateDebut == "01/01/2000" && dateFin != "01/01/2000")
        {
            for(int i=0; i < gestionTache.getlTaches().size();i++)
            {
                QDate datef = QDate::fromString(dateFin, "yyyy-MM-dd");
                QDate dateI = QDate::fromString(QString::fromStdString(gestionTache.getlTaches()[i].getDateTache()), "yyyy-MM-dd");
                if(dateI <= datef)
                {
                    string s;
                    ostringstream affichageTaches;
                    affichageTaches << gestionTache.getlTaches()[i];
                    s = affichageTaches.str();
                    ui->textEdit->append(QString::fromStdString(s));
                }
            }
        }
        else if( dateDebut != "01/01/2000" && dateFin != "01/01/2000")
        {
            for(int i=0; i < gestionTache.getlTaches().size();i++)
            {
                QDate dated = QDate::fromString(dateDebut, "yyyy-MM-dd");
                QDate datef = QDate::fromString(dateFin, "yyyy-MM-dd");
                QDate dateI = QDate::fromString(QString::fromStdString(gestionTache.getlTaches()[i].getDateTache()), "yyyy-MM-dd");
                if(dateI >= dated && dateI <= datef)
                {
                    string s;
                    ostringstream affichageTaches;
                    affichageTaches << gestionTache.getlTaches()[i];
                    s = affichageTaches.str();
                    ui->textEdit->append(QString::fromStdString(s));
                }
            }
        }
    }
    else
    {
        //on recupere les taches du contact demande
        QStringList contact = ui->cb_contatcs->currentText().split(" ");
        QString nom = contact[0];
        QString prenom = contact[1];
        QDate dated = QDate::fromString(dateDebut, "yyyy-MM-dd 00:00:00");
        QDate datef = QDate::fromString(dateFin, "yyyy-MM-dd 00:00:00");
        vector<Tache> lTaches;
        emit listeTachesBD(nom, prenom, dated, datef, lTaches);
        for(int i = 0; i < lTaches.size(); i++)
        {
            string s;
            ostringstream affichageTaches;
            affichageTaches << lTaches[i];
            s = affichageTaches.str();
            ui->textEdit->append(QString::fromStdString(s));
        }
    }
}

void MainWindow::afficherDates()
{
    ui->textEdit->clear();
    QString dateDebut = ui->dtDebut->text();
    QString dateFin = ui->dtFin->text();
    QString contact = ui->cb_contatcs->currentText();
    if (contact == "ALL")
    {
        for(int i = 0; i < gestionTache.getlTaches().size();i++)
        {
            QDate dated = QDate::fromString(dateDebut, "yyyy-MM-dd");
            QDate datef = QDate::fromString(dateFin, "yyyy-MM-dd");
            QDate dateI = QDate::fromString(QString::fromStdString(gestionTache.getlTaches()[i].getDateTache()), "yyyy-MM-dd");
            if(dateI>=dated && dateI<=datef)
            {
                ui->textEdit->append("@date " + QString::fromStdString(gestionTache.getlTaches()[i].getDateTache()));
            }
        }
    }
    else
    {
        //on recupere les dates du contact demande
        QStringList contact = ui->cb_contatcs->currentText().split(" ");
        QString nom = contact[0];
        QString prenom = contact[1];
        QDate dated = QDate::fromString(dateDebut, "yyyy-MM-dd 00:00:00");
        QDate datef = QDate::fromString(dateFin, "yyyy-MM-dd 00:00:00");
        vector<QString> lDates;
        emit listeDatesBD(nom, prenom, dated, datef, lDates);
        for(int i = 0; i < lDates.size(); i++)
        {
            ui->textEdit->append("@date" + lDates[i]);
        }
    }
}

void MainWindow::rechercherContact()
{
    //trie par ordre alphabetique ou date de creation
    //on envoie un signal a la base de donnee
    int ordre;
    if(ui->rdb_dateCreation->isChecked())
    {
        qDebug() << "ordre creation";
        ordre = 0;
    }
    else
    {
        qDebug() << "ordre alphabetique";
        ordre = 1;
    }

    for(auto contact:gestionContact.getlContacts())
    {
        gestionContact.supprimerContact(contact.getNom(), contact.getPrenom(), gestionInteraction, gestionTache);
    }
    qDebug() << "fin suppression ancienne listes";

    vector<Contact> lContacts;
    QString nomRechercher = ui->le_nomRecherche->text();
    QString entrepriseRechercher = ui->le_entrepriseRecherche->text();
    QString dateMin = ui->dtDebutRecherche->text();
    QString dateMax = ui->dateFinRecherce->text();
    emit rechercheContactBD(lContacts, nomRechercher, entrepriseRechercher, dateMin, dateMax, ordre);

    //On nettoie le layout pour ne pas avoir des boutons en double
    QVBoxLayout *ly_listeContacts = ui->ly_listeContacts;
    QLayoutItem *item;

    while((item = ly_listeContacts->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }


    for(auto contact:lContacts)
    {
        gestionContact.ajouterContact(contact);
        for(auto interaction:contact.getlInteractions())
        {
            gestionInteraction.ajouterInteraction(interaction);
            for(auto tache:interaction.getlTaches())
            {
                gestionTache.ajouterTache(tache);
            }
        }
    }
    //On peut maintenant ajouter les nouveaux boutons
    vector<Contact> listeContacts = gestionContact.getlContacts();
    for(const Contact &contact : listeContacts)
    {
        QString texteBouton = QString::fromStdString(contact.getNom()+ " " + contact.getPrenom());
        QPushButton *bouton = new QPushButton(texteBouton);
        bouton->setFixedSize(QSize(200, 50));
        ly_listeContacts->addWidget(bouton);

        //quand on clique sur le bouton d'un contact, on ouvre la fiche contact correspondante
        QObject::connect(bouton, &QPushButton::clicked,this,[this, contact](){
            ouvrirFicheContact(contact);
        });
    }
    QWidget *scrollWidget = new QWidget;
    scrollWidget->setLayout(ly_listeContacts);
    ui->scrollArea->setWidget(scrollWidget);
    ui->scrollArea->setWidgetResizable(true);

    afficherNbContacts();
    remplirCBContacts();

}
