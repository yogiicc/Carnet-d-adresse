/**
 * \file GestionInteraction.cpp
 * \brief fichier de la class GestionInteraction.h .
 */
#include <iostream>
#include "GestionInteraction.h"

/**
 * @brief Constructeur de la class GestionInteraction
 */
GestionInteraction::GestionInteraction(){}
/**
 * @brief Destructeur de la class GestionInteraction
 */
GestionInteraction::~GestionInteraction(){}

/**
 * @brief récupérer la liste d'Interactions de GestionInteraction
 * @return lInteractions en vector<Interaction>
 */
vector<Interaction> GestionInteraction::getlInteractions() const{return lInteractions;}

/**
 * @brief permet d'ajouter l'interaction crée dans le Gestionnaire d'interactions.
 * @param i l'interaction à ajouter
 */
void GestionInteraction::ajouterInteraction(Interaction &i)
{
    lInteractions.push_back(i);
}

/**
 * @brief permet d'ajouter la tache crée à l'interaction dans le Gestionnaire d'interactions.
 * @param numeroInteraction, t  le numéro de l'interaction et la tache à lui ajouter
 */
void GestionInteraction::ajouterTache(int id, Tache& t)
{
    for(int i=0; i < lInteractions.size(); i++)
    {
        if(lInteractions[i].getId()==id)
        {
            lInteractions[i].ajouterTache(t);
        }
    }
}

/**
 * @brief permet de supprimer l' interaction et ses taches liés au contact supprimé.
 * @param idInteraction, gt l'idendifiant de l'interaction à supprimer et le gestionnaire de taches
 */
void GestionInteraction::supprimerInteraction(int id, GestionTache& gt)
{
    for(int i=0; i<lInteractions.size();i++)
    {
        if(lInteractions[i].getId()==id)
        {
            for(int t=0; t<lInteractions[i].getlTaches().size(); t++)
            {
                Tache& ti = lInteractions[i].getTache(t);
                int tId = ti.getId();
                gt.supprimerTache(tId);
            }
            lInteractions.erase(lInteractions.begin()+i);
        }
    }
}

/**
 * @brief Suchargeur de l'operateur qui affiche toute la liste d'interactions
 * @param os, gi flux de sortie et le gestionnaire d'interactions
 */
ostream& operator<<(ostream& os, const GestionInteraction& gi)
{
    for(auto i:gi.getlInteractions())
        os << i << endl;
    return os;
}

