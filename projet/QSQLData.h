#ifndef QSQLDATA_H
#define QSQLDATA_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <vector>
#include <Contact.h>
#include <QDateTime>
#include <QDate>


class QSQLData:public QObject
{
    Q_OBJECT;
public:
    QSQLData(QObject *parent = nullptr);
    ~QSQLData();
private:
    QSqlDatabase bd;
    bool bdOuverte;

    bool connexionBD();
    void fermerBD();



private slots:
    void ajouterContact(Contact c);
    void supprimerContact(Contact c);
    void modifierContact(QString,QString,Contact c);

    void ajouterInteraction(QString, QString, Interaction&);
    void modifierInteraction(int id,QString);
    void supprimerInteractions(int id);
    void ajouterTache(int id, Tache);
    void supprimerTaches(int id);
    //void supprimerTache(Tache t);

    void listeContacts(vector<Contact> &lContacts);
    void listeInteractions(QString, QString, QDate, QDate, vector<Interaction> &lInteractions);
    void listeTaches(QString, QString, QDate, QDate, vector<Tache> &lTaches);
    void listeDates(QString,QString, QDate, QDate, vector<QString> &lDates);
    void verifierContactExistant(Contact c, bool &existe);

    void rechercheContact(vector<Contact> &lContacts, QString, QString, QString, QString,int);
};

#endif // QSQLDATA_H
