/**
 * \file Interaction.h
 * \brief fichier de déclaration de la class Interaction.
 */
#ifndef INTERACTION_H
#define INTERACTION_H

//#include "dateheure.h"
#include "Tache.h"

#include <string>
#include <vector>

using namespace std;

/**
 *\brief class Interaction qui permet d'ajouter des interactions à un contact
 */
class Interaction
{
private:
    string contenu; /**< attribut pour le contenu d'une interaction*/
    string dateCreation; /**< attribut pour sotcker la date et l'heure de créetion d'une Interaction*/
    string dateModif;
    int id; /**< attribut permettant de reconnaitre une Interaction dans la liste d'interaction */

    vector<Tache> lTaches; //**< tableau de Taches qui conient toutes les taches liés à cette Interaction*/

public:
    //Constructeurs et Destructeur
    Interaction(const string);
    ~Interaction();

    //Accesseurs et Modificateurs
    string getContenu() const;
    string getDateCreation() const;
    string getDateModif() const;
    int getId() const;
    vector<Tache> getlTaches() const;
    Tache& getTache(int);

    void setContenu(const string);
    void setDateCreation(const string);
    void setDateModif(const string);
    void setId(const int);

    //Méthodes
    void ajouterTache(Tache&);
    friend ostream& operator<<(ostream &, const Interaction&);
};

#endif // INTERACTION_H
