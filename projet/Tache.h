/**
 * \file Tache.h
 * \brief fichier de déclaration de la class Tache.
 */
#ifndef TACHE_H
#define TACHE_H

#include <string>

using namespace std;

/**
 * \brief class Tache qui permet de rajouter des taches à une interaction
 */
class Tache{
private:
    //attributs
    string contenu; /**< attribut pour stocker le contenu d'une tache*/
    string dateTache; /**< attribut pour stocker la date de la tache*/
    string dateCreation;
    int id; /**< attribut permettant de reconnaitre une tache dans la liste de taches*/

public:
    //Constructeurs et Destructeur
    Tache(string, string);
    ~Tache();

    //Accesseurs et Modificateurs
    string getContenu() const;
    string getDateTache() const;
    string getDateCreation() const;
    int getId() const;

    void setContenu(string);
    void setDateTache(string);
    void setDateCreation(string);
    void setId(int);

    //Méthodes
    friend ostream& operator<<(ostream &, const Tache &);
};

#endif // TACHE_H
