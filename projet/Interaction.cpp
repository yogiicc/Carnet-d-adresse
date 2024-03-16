/**
 * \file Interaction.cpp
 * \brief fichier de la class interaction.h .
 */
#include <iostream>
#include "Interaction.h"

/**
 * @brief Constructeur avec paramètres de Interaction.
 * @param c pour défnir le contenu de l'Interaction
 */
Interaction::Interaction(const string c)
{
    setContenu(c);
    //setDateHeure();
}
/**
 * @brief Destructeur de la class Interaction.
 */
Interaction::~Interaction(){}

/**
 * @brief récupérer le contenu et la date de creation et de moidfication de l'Interaction.
 * @return contenu, dateCreation et dateModif en string
 */
string Interaction::getContenu() const{return contenu;}
string Interaction::getDateCreation() const{return dateCreation;}
string Interaction::getDateModif() const{return dateModif;}
/**
 * @brief récupérer l'ID de l'Interaction.
 * @return id en int
 */
int Interaction::getId() const{return id;}
/**
 * @brief récupérer la liste de Taches de l'Interaction.
 * @return lTaches en vector<Tache>
 */
vector<Tache> Interaction::getlTaches() const{return lTaches;}
/**
 * @brief récupérer une référence de Tache par sa position dans la liste de Tache de l'Interaction.
 * @return lTaches[i] en réference de Tache&
 */
Tache& Interaction::getTache(int i){return lTaches[i];}

/**
 * @brief modifier le contenu la date de creation ou de mofification d'une Interaction.
 * @param c, d, d le nouveau contenu ou dateCreation ou dateModif de l'Interaction
 */
void Interaction::setContenu(const string c){contenu = c;}
void Interaction::setDateCreation(const string d){dateCreation = d;}
void Interaction::setDateModif(const string d){dateModif = d;}
void Interaction::setId(const int i){id = i;}

/**
 * @brief permet d'ajouter une Tache à la liste de Tache de l'Interaction.
 * @param t une référence de la Tache t à ajouter
 */
void Interaction::ajouterTache(Tache& t)
{
    lTaches.push_back(t);
}

/**
 * @brief Surchargeur de l'opérateur pour afficher une Interaction.
 * @param os, i flux de sortie et Interaction à afficher
 */
ostream& operator<<(ostream &os, const Interaction& i)
{
    os << i.getContenu() << endl;
    for(auto t:i.getlTaches())
        os << t << endl;
    return os;
}
