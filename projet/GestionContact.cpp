/**
 * \file GestionContact.cpp
 * \brief fichier la class GestionContact.h .
 */
#include "GestionContact.h"
#include <ostream>

using namespace std;

/**
 * @brief Constructeur de la class GestionContact.
 */
GestionContact::GestionContact(){}
/**
 * @brief Destructeur de la class GestionContact.
 */
GestionContact::~GestionContact(){}

/**
 * @brief récupérer la liste de Contact de GestionContact.
 * @return lContacts en vector<Contact>
 */
vector<Contact> GestionContact::getlContacts() const{return lContacts;}


/**
 * @brief permet de créer et d'ajouter un Contact à la liste de GestionContact.
 * @param nom, prenom permet d'identifier un Contact
 */
void GestionContact::ajouterContact(Contact c)
{
    lContacts.push_back(c);
}


/**
 * @brief permet de créer et d'ajouter une Interaction à la liste d'interactions du Contact et dans GestionInteraction
 * @param nom, prenom, contenuInteraction, gi identifiant du contact, contenu de la nouvelle interaction et le gestionnaire d'interaction
 */
void GestionContact::ajouterInteraction(string nom, string prenom, Interaction i, GestionInteraction& gi)
{
    //Interaction i((contenuI);

    for( int c= 0; c<lContacts.size(); c++)
        if(lContacts[c].getNom()==nom && lContacts[c].getPrenom()==prenom)
        {
            lContacts[c].ajouterInteraction(i);
            gi.ajouterInteraction(i);
        }
}

/**
 * @brief permet de créer et d'ajouter une Tache à la liste de Taches d'une interaction et dans GestionTache.
 * @param nom, prenom, i, contenuTache, gi, gt identifiant du contact, numero de l'interaction, contenu de la nouvelle tache, le gestionnaire d'interaction et le gestionnaire de taches.
 */
void GestionContact::ajouterTache(string nom, string prenom, int i, Tache t, GestionInteraction& gi, GestionTache& gt)
{
   // Tache t(contenu, date);

    for(int c=0; c<lContacts.size(); c++){
        if(lContacts[c].getNom()==nom && lContacts[c].getPrenom()==prenom)
        {
            Interaction& ic = lContacts[c].getInteractionI(i);
            ic.ajouterTache(t);
            int iId = ic.getId();
            gi.ajouterTache(iId, t);
            gt.ajouterTache(t);
        }
    }
}

/**
 * @brief permet de supprimer un contact et donc les interactions et les taches qui lui sont liés.
 * @param nom, prenom,  gi, gt identifiant du contact, le gestionnaire d'interaction et le gestionnaire de taches.
 */
void GestionContact::supprimerContact(string nom, string prenom, GestionInteraction& gi, GestionTache& gt)
{
    for(int c=0; c<lContacts.size(); c++)
    {
        if(lContacts[c].getNom()==nom && lContacts[c].getPrenom()==prenom)
        {
            for(int i=0; i<lContacts[c].getlInteractions().size();i++)
            {
                Interaction& ic = lContacts[c].getInteractionI(i);
                int iId = ic.getId();
                gi.supprimerInteraction(iId,gt);
            }
            lContacts.erase(lContacts.begin()+c);
        }
    }
}


void GestionContact::supprimerContact(Contact contactASupp)
{
    for(int c=0; c<lContacts.size(); c++)
    {
        if(lContacts[c].getNom()== contactASupp.getNom() && lContacts[c].getPrenom()== contactASupp.getPrenom())
        {
            lContacts.erase(lContacts.begin()+c);
        }
    }
}

/**
 * @brief Surchargueur de l'operateur qui affiche la liste de tous les contacts.
 * @param os, gc flux de sortie et le gestionnaire de contacts
 */
ostream& operator<<(ostream& os, const GestionContact& gc)
{
    for(auto c:gc.getlContacts())
        os << c << endl;
    return os;
}

