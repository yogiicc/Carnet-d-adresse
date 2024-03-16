/**
 * \file GestionContact.h
 * \brief fichier de déclaration de la class GestionContact.
 */
#ifndef GESTIONCONTACT_H
#define GESTIONCONTACT_H

#include "Contact.h"
#include "GestionInteraction.h"
#include "GestionTache.h"

#include <vector>

/**
 * \brief Class GestionContact permettant de gérer les Contacts et les actions dessus
 */
class GestionContact
{
public:
private:
    vector<Contact> lContacts; /**< Attribut vector contenant les Contacts*/

public:
    GestionContact();
    ~GestionContact();

    vector<Contact> getlContacts() const;

    void ajouterContact(Contact c);
    void ajouterInteraction(string nom, string prenom, Interaction, GestionInteraction&);

    void ajouterTache(string, string, int, Tache, GestionInteraction&, GestionTache&);

    void supprimerContact(Contact contactASupp);
    void supprimerContact(string nom, string prenom, GestionInteraction& gi, GestionTache& gt);
    friend ostream& operator<<(ostream&, const GestionContact &);
};

#endif // GESTIONCONTACT_H
