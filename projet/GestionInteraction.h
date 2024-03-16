/**
 * \file GestionInteraction.h
 * \brief fichier de déclaration de la class GestionInteraction.
 */
#ifndef GESTIONINTERACTION_H
#define GESTIONINTERACTION_H

#include "Interaction.h"
#include "GestionTache.h"

#include <vector>

/**
 * \brief class GestionInteraction permettant de gérer toutes les Interactions.
 */
class GestionInteraction
{
private:
    vector<Interaction> lInteractions; /**< Attributs contenant toute les interactions*/
public:
    GestionInteraction();
    ~GestionInteraction();

    vector<Interaction> getlInteractions() const;

    void ajouterInteraction(Interaction& i);
    void ajouterTache(int, Tache& t);
    void supprimerInteraction(int id, GestionTache&);

    friend ostream& operator<<(ostream&, const GestionInteraction&);
};
#endif // GESTIONINTERACTION_H
