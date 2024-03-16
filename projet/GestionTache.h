/**
 * \file GestionTache.h
 * \brief fichier de déclaration de la class GestionTache.
 */
#ifndef GESTIONTACHE_H
#define GESTIONTACHE_H


#include "Tache.h"
#include <vector>

/**
 * \brief class GestionTache permettant de gérer l'ensemble des Taches.
 */
class GestionTache
{
private:
    vector<Tache> lTaches;

public:
    GestionTache();
    ~GestionTache();

    vector<Tache> getlTaches() const;

    void ajouterTache(Tache& t);
    void supprimerTache(int);

    friend ostream& operator<<(ostream&, const GestionTache &);
};

#endif // GESTIONTACHE_H
