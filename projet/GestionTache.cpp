/**
 * \file GestionTache.cpp
 * \brief fichier de déclaration de la class GestionTache.h .
 */
#include <iostream>

#include "GestionTache.h"

/**
 * @brief Constructeur de la class GestionTache.
 */
GestionTache::GestionTache(){}
/**
 * @brief Destructeur de la class GestionTache.
 */
GestionTache::~GestionTache(){}

/**
 * @brief récupérer la liste des Taches du gestionnaire de Taches.
 * @return lTaches en vector<Tache>
 */
vector<Tache> GestionTache::getlTaches() const{return lTaches;}

/**
 * @brief permet d'ajouter une tache à la liste du Gestionnaire de Taches.
 * @param t la tache à ajouter
 */
void GestionTache::ajouterTache(Tache& t)
{
    lTaches.push_back(t);
}

/**
 * @brief permet de supprimer les taches liés à l'interaction supprimée et donc au contact supprimé.
 * @param idTache identifiant pour supprimer la bonne tache
 */
void GestionTache::supprimerTache(int id)
{
    for(int t=0; t<lTaches.size(); t++)
        if( lTaches[t].getId()== id)
            lTaches.erase(lTaches.begin()+ t);
}

/**
 * @brief Surchagueur de l'operateur qui affiche la liste des Taches du gestionnaire de Taches.
 * @param os, gt le flux de sortie et le gestionnaire de Taches
 */
ostream& operator<<(ostream& os, const GestionTache& gt)
{
    for(auto t:gt.getlTaches())
        os << t << endl;
    return os;
}

