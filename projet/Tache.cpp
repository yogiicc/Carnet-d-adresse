/**
 * \file Tache.cpp
 * \brief fichier de la class tache.h .
 */
#include "Tache.h"

#include <iostream>

/**
 *@brief Constructeur avec paramètres de la class Tache.
 *@param c, d pour le contenu de la Tache et pour la date de la Tache
 */
Tache::Tache(string c,string d){
    setContenu(c);
    setDateTache(d);
}
/**
 *@brief Destructeur de la class Tache.
 */
Tache::~Tache(){}

/**
 *@brief récupérer le contenu, la date de creation et la date de la Tache.
 *@return le contenu en string
 */
string Tache::getContenu() const{return contenu;}
string Tache::getDateTache() const{return dateTache;}
string Tache::getDateCreation() const{return dateCreation;}
/**
 *@brief récupérer l'ID de la Tache.
 *@return l'ID en int
 */
int Tache::getId() const{return id;}

/**
 *@brief changer le contenu d'une Tache, utiliser seulement dans le constructeur.
 *@param c, nouveau contenu pour la Tache
 */
void Tache::setContenu(const string c){contenu=c;}
void Tache::setDateTache(const string d){dateTache=d;}
void Tache::setDateCreation(const string d){dateCreation = d;}
void Tache::setId(const int i){id = i;}

/**
 *@brief surchargeur de l'operateur pour l'affichage d'une Tache.
 *@param os,t flux de sortie et la Tache à afficher
 */
ostream& operator<<(ostream& os, const Tache& t)
{
    os << "@todo " << t.getContenu() << " @date " << t.getDateTache()<<endl;
    return os;
}
