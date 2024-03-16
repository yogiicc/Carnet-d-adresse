#include "QSQLData.h"

QSQLData::QSQLData(QObject *parent) : QObject(parent)
{
    bdOuverte = false;
    connexionBD();
}

QSQLData::~QSQLData()
{
    fermerBD();
}

bool QSQLData::connexionBD()
{
    bd = QSqlDatabase::addDatabase("QSQLITE");
    QString cheminBD="../bd.sqlite";
    bd.setDatabaseName(cheminBD);
    if(!bd.open())
    {
        qDebug() << "Pas de connexion à la BDD !";
        bdOuverte=false;
    }
    else
    {
        qDebug() << "Connexion réussie à la BDD !\n";
        bdOuverte=true;
        QSqlQuery query;
        query.prepare("CREATE TABLE IF NOT EXISTS Contacts (id INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR(255), prenom VARCHAR(255), entreprise VARCHAR(255), mail VARCHAR(255), tel VARCHAR(255), photo VARCHAR(255), dateCreation DATETIME, dateModif DATETIME);");
        if(!query.exec())
        {
            qDebug() << "Impossible d’exécuter la requête !";
        }
        else
        {
            qDebug() << "Table de Contacts crées";
        }
        query.prepare("CREATE TABLE IF NOT EXISTS Interactions (id INTEGER PRIMARY KEY AUTOINCREMENT, contenu VARCHAR(255), contactID INTEGER,dateCreation DATETIME, dateModif DATETIME, FOREIGN KEY (contactID) REFERENCES Contacts (id));");
        if(!query.exec())
        {
            qDebug() << "Impossible d’exécuter la requête !";
        }
        else
        {
            qDebug() << "Table d'interactions crées";
        }
        query.prepare("CREATE TABLE IF NOT EXISTS Taches (id INTEGER PRIMARY KEY AUTOINCREMENT, contenu VARCHAR(255), interactionID INTEGER,  dateTache DATETIME, dateCreation DATETIME, FOREIGN KEY (interactionID) REFERENCES Interactions (id));");
        if(!query.exec())
        {
            qDebug() << "Impossible d’exécuter la requête !";
        }
        else
        {
            qDebug() << "Table de taches crées";
        }

    }
    return bdOuverte;
}

void QSQLData::fermerBD()
{
    if (bdOuverte==true)
        bd.close();
}


void QSQLData::ajouterContact(Contact c)
{
    if(bdOuverte)
    {
        qDebug ()<< "ajouterContact de QSQLDatabase";
        QSqlQuery query;
        query.prepare("INSERT INTO Contacts (nom,prenom,entreprise,mail,tel,photo,datecreation)VALUES(:nom, :prenom, :entreprise, :mail, :tel, :photo, DATETIME('now'));");
        query.bindValue(":nom",QString::fromStdString(c.getNom()));
        query.bindValue(":prenom",QString::fromStdString(c.getPrenom()));
        query.bindValue(":entreprise",QString::fromStdString(c.getEntreprise()));
        query.bindValue(":mail",QString::fromStdString(c.getMail()));
        query.bindValue(":tel",QString::fromStdString(c.getTel()));
        query.bindValue(":photo",QString::fromStdString(c.getPhoto()));
        if(!query.exec())
        {
            qDebug() << "Impossible d’exécuter la requête !\n";
        }
        else
        {
            qDebug() << "Contact ajouter avec succes " << QString::fromStdString(c.getNom()) << QString::fromStdString(c.getPrenom());
        }
    }
}

void QSQLData::verifierContactExistant(Contact c, bool &existe)
{
        QSqlQuery queryContactExist;
        queryContactExist.prepare("SELECT COUNT(*) FROM Contacts WHERE nom = :n AND prenom = :p");
        queryContactExist.bindValue(":n", QString::fromStdString(c.getNom()));
        queryContactExist.bindValue(":p", QString::fromStdString(c.getPrenom()));

        // Exécutez la requête avant de récupérer le résultat
        if(queryContactExist.exec()) {
            if(queryContactExist.next()){
                int cpt = queryContactExist.value(0).toInt();
                if( cpt < 1)
                {
                    qDebug() << "dans le if du compteur le compteur : " << cpt;
                    existe = false;
                }
                else
                {
                    qDebug() << "le contact existe déjà";
                    existe = true;
                }
            }
        } else {
            qDebug() << "Erreur lors de l'exécution de la requête.";
            existe = false;  // Par défaut, le contact n'existe pas en cas d'erreur.
        }
}

void QSQLData::supprimerContact(Contact c)
{
    if(bdOuverte==true){
        QSqlQuery query;

        int contactId = 0;
        //On va supprimer les interactions et les taches liés a ce contact de la base de données
        query.prepare("SELECT id FROM Contacts WHERE nom=:n AND prenom=:p");
        query.bindValue(":n",QString::fromStdString(c.getNom()));
        query.bindValue(":p",QString::fromStdString(c.getPrenom()));
        if (!query.exec()) {
                qDebug() << "Impossible d'exécuter la requête de sélection du contact !";
        } else {
                if (query.next()) {
                    contactId = query.value(0).toInt();
                    supprimerInteractions(contactId);
                }
        }

        query.prepare("DELETE FROM Contacts WHERE nom=:n AND prenom=:p");
        query.bindValue(":n",QString::fromStdString(c.getNom()));
        query.bindValue(":p",QString::fromStdString(c.getPrenom()));
        if(!query.exec())
        {
            qDebug() << "Impossible d’exécuter la requête !";
        }
        else
        {
            qDebug() << "contact supprimer avec succès" << QString::fromStdString(c.getNom()) ;
        }
    }
}

void QSQLData::supprimerInteractions(int idContact)
{
    if(bdOuverte==true){
        QSqlQuery query;
        int idInteraction = 0;
        //on va supprimer les taches des interactions du contact
        query.prepare("SELECT id FROM interactions WHERE contactID =:id");
        query.bindValue(":id", idContact);
        if (!query.exec()) {
            qDebug() << "Impossible d'exécuter la requête de sélection du contact !";
        } else {
            while (query.next()) {
                    idInteraction = query.value(0).toInt();
                    supprimerTaches(idInteraction);
            }
        }
        //On supprime maintenant les interactions de ce contact
        query.prepare("DELETE FROM Interactions WHERE contactID = :id");
        query.bindValue(":id", idContact);
        if(!query.exec())
        {
            qDebug() << "Impossible d’exécuter la requête !";
        }
        else
        {
            qDebug() << "interactions  supprimer avec succès";
        }
    }
}

void QSQLData::supprimerTaches(int idInteraction)
{
    if(bdOuverte==true){
        QSqlQuery query;
        //On supprime maintenant les taches de l'interaction;
        query.prepare("DELETE FROM Taches WHERE interactionID = :id");
        query.bindValue(":id", idInteraction);
        if(!query.exec())
        {
            qDebug() << "Impossible d’exécuter la requête !";
        }
        else
        {
            qDebug() << "taches  supprimer avec succès";
        }
    }
}

/*
void QSQLData::supprimerTache(Tache t)
{

}*/

void QSQLData::ajouterInteraction(QString nom, QString prenom, Interaction &i) {
    if (bdOuverte) {
        int contactId = 0;
        QSqlQuery query;
        // Sélection de l'ID du contact
        query.prepare("SELECT id FROM Contacts WHERE nom = :n AND prenom = :p");
        query.bindValue(":n", nom);
        query.bindValue(":p", prenom);
        qDebug() << "on recupere l'id du contact lié à l'interaction";

        if (!query.exec()) {
            qDebug() << "Impossible d'exécuter la requête de sélection du contact !";
        } else {
            if (query.next()) {
                contactId = query.value(0).toInt();
            }

            // Insertion de l'interaction
            query.prepare("INSERT INTO Interactions (contenu, contactID, dateCreation, dateModif) VALUES (:c, :id, DATETIME('now'), DATETIME('now'))");
            query.bindValue(":c", QString::fromStdString(i.getContenu()));
            query.bindValue(":id", contactId);
            qDebug() << "On ajoute l'interaction à la table";

            if (!query.exec()) {
                qDebug() << "Impossible d'exécuter la requête d'insertion de l'interaction !";
            } else {
                // Récupération de l'ID de l'interaction ajoutée
                int interactionId = query.lastInsertId().toInt();
                i.setId(interactionId);

                qDebug() << "on donne l'id à l'interaction";

                // Mise à jour de la date de modification du contact
                query.prepare("UPDATE Contacts SET dateModif = DATETIME('now') WHERE id = :id");
                query.bindValue(":id", contactId);

                qDebug() << "on met à jour la date de modification du contact";

                if (!query.exec()) {
                    qDebug() << "Impossible d'exécuter la requête de mise à jour de la date de modification du contact !";
                }
            }
        }
    }
}


void QSQLData::ajouterTache(int idInteraction, Tache nouvelleTache) {
    if (bdOuverte) {
        QSqlQuery query;

        // Insertion de la tâche
        query.prepare("INSERT INTO Taches (contenu, interactionID, dateTache, dateCreation) "
                      "VALUES (:c, :id, DATETIME('now'), DATETIME('now'))");
        query.bindValue(":c", QString::fromStdString(nouvelleTache.getContenu()));
        query.bindValue(":id", idInteraction);

        qDebug() << "on ajoute la tache à la table";

        if (!query.exec()) {
            qDebug() << "Impossible d'exécuter la requête d'insertion de la tâche !";
        } else {
            // Récupération de l'ID de la tâche ajoutée
            int tacheId = query.lastInsertId().toInt();
            nouvelleTache.setId(tacheId);
            qDebug() << "On donne l'id à la tache";

            // Mise à jour de la date de modification du contact associé à l'interaction
            query.prepare("UPDATE Contacts SET dateModif = DATETIME('now') "
                            "WHERE id = (SELECT contactID FROM Interactions WHERE id = :id)");
            query.bindValue(":id", idInteraction);
            if (!query.exec()) {
                qDebug() << "Impossible d'exécuter la requête pour la mise à jour de la date de modification du contact.";
            }

            // Mise à jour de la date de modification de l'interaction
            query.prepare("UPDATE Interactions SET dateModif = DATETIME('now') "
                          "WHERE id = :id");
            query.bindValue(":id", idInteraction);
            if (!query.exec()) {
                qDebug() << "Impossible d'exécuter la requête pour la mise à jour de la date de modification de l'interaction.";
            }


            qDebug() << "on met à jour la date de derniere modifaction de interaction et de contact";

            if (!query.exec()) {
                qDebug() << "Impossible d'exécuter la requête de mise à jour de la date de modification du contact !";
            }
        }
    }
}

void QSQLData::listeContacts(vector<Contact> &lContacts) {
    if (bdOuverte) {
        QSqlQuery queryContact;
        queryContact.prepare("SELECT * FROM Contacts ORDER BY dateCreation ASC");

        if(!queryContact.exec())
        {
            qDebug() << "Impossible d'exécuter la requête de récupération des contacts !";
        }
        else
        {
            while (queryContact.next()) {
                QString nom = queryContact.value("nom").toString();
                QString prenom = queryContact.value("prenom").toString();
                QString entreprise = queryContact.value("entreprise").toString();
                QString mail = queryContact.value("mail").toString();
                QString tel = queryContact.value("tel").toString();
                QString photo = queryContact.value("photo").toString();
                QString dateCreation = queryContact.value("dateCreation").toString();
                QString dateModif = queryContact.value("dateModif").toString();

                Contact contact(nom.toStdString(), prenom.toStdString(), entreprise.toStdString(), mail.toStdString(), tel.toStdString(), photo.toStdString(), dateCreation.toStdString(), dateModif.toStdString());

                QSqlQuery queryInteraction;
                queryInteraction.prepare("SELECT * FROM Interactions WHERE contactID = :id");
                queryInteraction.bindValue(":id", queryContact.value("id").toInt());

                if(!queryInteraction.exec())
                {
                    qDebug() << "Impossible d'exécuter la requête de récupération des interactions !";
                }
                else
                {
                    while(queryInteraction.next())
                    {
                        QString contenu = queryInteraction.value("contenu").toString();
                        QString dateCreation = queryInteraction.value("dateCreation").toString();
                        QString dateModif = queryInteraction.value("dateModif").toString();

                        Interaction interaction(contenu.toStdString());
                        interaction.setId(queryInteraction.value("id").toInt());
                        interaction.setDateCreation(dateCreation.toStdString());
                        interaction.setDateModif(dateModif.toStdString());

                        QSqlQuery queryTache;
                        queryTache.prepare("SELECT * FROM Taches WHERE interactionID = :id");
                        queryTache.bindValue(":id", queryInteraction.value("id").toInt());

                        if(!queryTache.exec())
                        {
                            qDebug() << "Impossible d'exécuter la requête de récupération des taches !";

                        }
                        else
                        {
                            while(queryTache.next())
                            {
                                QString contenu = queryTache.value("contenu").toString();
                                QString dateTache = queryTache.value("dateTache").toString();
                                QString dateCreation = queryTache.value("dateCreation").toString();
                                Tache tache(contenu.toStdString(), dateTache.toStdString());
                                tache.setDateCreation(dateCreation.toStdString());
                                tache.setId(queryTache.value("id").toInt());

                                interaction.ajouterTache(tache);
                            }
                        }

                        contact.ajouterInteraction(interaction);
                    }
                }
                lContacts.push_back(contact);
            }
        }
    }
}

void QSQLData::listeInteractions(QString nom, QString prenom, QDate dateD, QDate dateF, vector<Interaction> &lInteractions)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Interactions WHERE contactID =(SELECT id FROM Contacts WHERE nom= :n AND prenom = :p ) AND dateCreation >= :dated AND dateCreation <= :datef");
    query.bindValue(":n", nom);
    query.bindValue(":p", prenom);
    query.bindValue(":dated", dateD);
    query.bindValue(":datef", dateF);
    if(!query.exec())
    {
        qDebug() << "Impossible d'exécuter la requête de récupération des interactions !";
    }
    else
    {
        while (query.next())
        {
            QString contenu = query.value("contenu").toString();
            QString dateCreation = query.value("dateCreation").toString();
            QString dateModif = query.value("dateModif").toString();

            Interaction interaction(contenu.toStdString());
            interaction.setId(query.value("id").toInt());
            interaction.setDateCreation(dateCreation.toStdString());
            interaction.setDateModif(dateModif.toStdString());
            QSqlQuery queryTache;
            queryTache.prepare("SELECT * FROM Taches WHERE interactionID = :id");
            queryTache.bindValue(":id", query.value("id").toInt());

            if(!queryTache.exec())
            {
                qDebug() << "Impossible d'exécuter la requête de récupération des taches !";
            }
            else
            {
                while(queryTache.next())
                {
                    QString contenu = queryTache.value("contenu").toString();
                    QString dateTache = queryTache.value("dateTache").toString();
                    QString dateCreation = queryTache.value("dateCreation").toString();
                    Tache tache(contenu.toStdString(), dateTache.toStdString());
                    tache.setDateCreation(dateCreation.toStdString());
                    tache.setId(queryTache.value("id").toInt());

                    interaction.ajouterTache(tache);
                }
            }
            lInteractions.push_back(interaction);
        }
    }
}

void QSQLData::listeTaches(QString nom, QString prenom, QDate dateD, QDate dateF, vector<Tache> &lTaches)
{
    if (bdOuverte) {
        QSqlQuery query;
        query.prepare("SELECT * FROM Taches WHERE interactionID = (SELECT id FROM Interactions WHERE contactID = (SELECT id FROM Contacts WHERE nom = :n AND prenom = :p)) AND dateTache >= :dated AND dateTache <= :datef");
        query.bindValue(":n", nom);
        query.bindValue(":p", prenom);
        query.bindValue(":dated", dateD);
        query.bindValue(":datef", dateF);
        if(!query.exec())
        {
            qDebug() << "Impossible d'exécuter la requête de récupération des contacts !";
        }
        else
        {
            while (query.next())
            {
                QString contenu = query.value("contenu").toString();
                QString dateTache = query.value("dateTache").toString();
                QString dateCreation = query.value("dateCreation").toString();

                Tache tache(contenu.toStdString(), dateTache.toStdString());
                tache.setDateCreation(dateCreation.toStdString());
                tache.setId(query.value("id").toInt());

                lTaches.push_back(tache);
            }
        }
    }
}

void QSQLData::listeDates(QString nom, QString prenom, QDate dateD, QDate dateF, vector<QString> &lDates)
{
    if (bdOuverte) {
        QSqlQuery query;
        query.prepare("SELECT * FROM Taches WHERE interactionID = (SELECT id FROM Interactions WHERE contactID = (SELECT id FROM Contacts WHERE nom = :n AND prenom = :p)) AND dateTache >= :dated AND dateTache <= :datef");
        query.bindValue(":n", nom);
        query.bindValue(":p", prenom);
        query.bindValue(":dated", dateD);
        query.bindValue(":datef", dateF);
        if(!query.exec())
        {
            qDebug() << "Impossible d'exécuter la requête de récupération des contacts !";
        }
        else
        {
            while (query.next())
            {
                lDates.push_back(query.value("dateTache").toString());
                qDebug()<< "toute dates recuperer";
            }
        }
    }
}

void QSQLData::modifierContact(QString nom,QString prenom,Contact c){
    QSqlQuery query;
    query.prepare("UPDATE Contacts SET nom=:n, prenom=:p, entreprise=:e, mail=:m, tel=:tel, photo=:photo, dateModif=DATETIME('now') WHERE nom=:OldN AND prenom=:OldP;");
    query.bindValue(":n", QString::fromStdString(c.getNom()));
    query.bindValue(":p", QString::fromStdString(c.getPrenom()));
    query.bindValue(":e", QString::fromStdString(c.getEntreprise()));
    query.bindValue(":m", QString::fromStdString(c.getMail()));
    query.bindValue(":tel", QString::fromStdString(c.getTel()));
    query.bindValue(":photo", QString::fromStdString(c.getPhoto()));
    query.bindValue(":OldN", nom);
    query.bindValue(":OldP", prenom);

    if(!query.exec()){
        qDebug() << "Probleme lors de la mise à jour du contact";
    }
}

void QSQLData::modifierInteraction(int id,QString contenu){
    QSqlQuery query;
    query.prepare("UPDATE Interactions SET contenu = :c, dateModif = DATETIME('now') WHERE id = :id");
    query.bindValue(":c",contenu);
    query.bindValue(":id",id);
    if(!query.exec()){
        qDebug()<<"Probleme lors de la mise à jour de l'interaction";
    }

    query.prepare("UPDATE Contacts SET dateModif = DATETIME('now') "
                  "WHERE id = (SELECT contactID FROM Interactions WHERE id = :id)");
    query.bindValue(":id",id);
    if(query.exec()){
        qDebug()<< " Mise à jour du dateModif reussi";
    }
}

void QSQLData::rechercheContact(vector<Contact> &lContacts, QString nom, QString entreprise, QString dateMin, QString dateMax, int ordre)
{
    if(bdOuverte)
    {
        QString query = "SELECT * FROM Contacts ";
        bool avecAND = false;
        if(!nom.isEmpty())
        {
            if(!avecAND)
            {
                query += "WHERE ";
            }
            query += "(nom LIKE :n)";
            avecAND = true;
        }
        if(!entreprise.isEmpty())
        {
            if(!avecAND)
            {
                query += "WHERE ";
            }
            if(avecAND)
            {
                query += "AND ";
            }
            query += "(entreprise LIKE :e)";
            avecAND = true;
        }
        if(dateMin != "01/01/2000")
        {
            if(!avecAND)
            {
                query += "WHERE ";
            }
            if(avecAND)
            {
                query += "AND ";
            }
            query += "(:dateMin <= dateCreation)";
            avecAND = true;
        }
        if(dateMax != "01/01/2000")
        {
            if(!avecAND)
            {
                query += "WHERE ";
            }
            if(avecAND)
            {
                query += "AND ";
            }
            query += "(:dateMax >= dateCreation)";
            avecAND = true;
        }
        if(ordre == 1)
        {
            query += " ORDER BY nom ";
        }
        if(ordre == 0)
        {
            query += " ORDER BY dateCreation";
        }
        QSqlQuery queryRecherche;
        queryRecherche.prepare(query);
        if(!nom.isEmpty())
        {
            queryRecherche.bindValue(":n", QString("%1%").arg(nom));
        }
        if(!entreprise.isEmpty())
        {
            queryRecherche.bindValue(":e", QString("%1%").arg(entreprise));
        }
        if(dateMin != "01/01/2000")
        {
            queryRecherche.bindValue(":dateMin", dateMin);
        }
        if(dateMax != "01/01/2000")
        {
            queryRecherche.bindValue(":dateMax", dateMax);
        }
        qDebug() << query;


        if(!queryRecherche.exec())
        {
            qDebug() << "Impossible d'exécuter la requête de récupération des contacts !";
        }
        else
        {
            while (queryRecherche.next()) {
                QString nom = queryRecherche.value("nom").toString();
                QString prenom = queryRecherche.value("prenom").toString();
                QString entreprise = queryRecherche.value("entreprise").toString();
                QString mail = queryRecherche.value("mail").toString();
                QString tel = queryRecherche.value("tel").toString();
                QString photo = queryRecherche.value("photo").toString();
                QString dateCreation = queryRecherche.value("dateCreation").toString();
                QString dateModif = queryRecherche.value("dateModif").toString();

                Contact contact(nom.toStdString(), prenom.toStdString(), entreprise.toStdString(), mail.toStdString(), tel.toStdString(), photo.toStdString(), dateCreation.toStdString(), dateModif.toStdString());

                QSqlQuery queryInteraction;
                queryInteraction.prepare("SELECT * FROM Interactions WHERE contactID = :id");
                queryInteraction.bindValue(":id", queryRecherche.value("id").toInt());

                if(!queryInteraction.exec())
                {
                    qDebug() << "Impossible d'exécuter la requête de récupération des interactions !";
                }
                else
                {
                    while(queryInteraction.next())
                    {
                        QString contenu = queryInteraction.value("contenu").toString();
                        QString dateCreation = queryInteraction.value("dateCreation").toString();
                        QString dateModif = queryInteraction.value("dateModif").toString();

                        Interaction interaction(contenu.toStdString());
                        interaction.setId(queryInteraction.value("id").toInt());
                        interaction.setDateCreation(dateCreation.toStdString());
                        interaction.setDateModif(dateModif.toStdString());

                        QSqlQuery queryTache;
                        queryTache.prepare("SELECT * FROM Taches WHERE interactionID = :id");
                        queryTache.bindValue(":id", queryInteraction.value("id").toInt());

                        if(!queryTache.exec())
                        {
                            qDebug() << "Impossible d'exécuter la requête de récupération des taches !";

                        }
                        else
                        {
                            while(queryTache.next())
                            {
                                QString contenu = queryTache.value("contenu").toString();
                                QString dateTache = queryTache.value("dateTache").toString();
                                QString dateCreation = queryTache.value("dateCreation").toString();
                                Tache tache(contenu.toStdString(), dateTache.toStdString());
                                tache.setDateCreation(dateCreation.toStdString());
                                tache.setId(queryTache.value("id").toInt());

                                interaction.ajouterTache(tache);
                            }
                        }

                        contact.ajouterInteraction(interaction);
                    }
                }
                lContacts.push_back(contact);
            }
        }
    }
}
