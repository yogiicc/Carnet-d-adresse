/**
 * \file Contact.cpp
 * \brief fichier de la class Contact.h .
 */
#include "Contact.h"

using namespace std;
#include <string>
#include <iostream>

/**
 * @brief Constructeur avec paramètres de la class Contact.
 * @param n, p, e, m, t, url, dc, dm pour le nom et le prénom du Contact qui agiront comme ID et les autres parametres d'un contact
 */
//Constructeur par défaut
Contact::Contact(){}
//Constructeur par défaut, il faut au moins un nom et un prenom pour créer un Contact
Contact::Contact(const string &n, const string &p, const string &e, const string &m,const string &t, const string &url, const string &dc, const string &dm)
{
    setNom(n);
    setPrenom(p);
    setEntreprise(e);
    setMail(m);
    setTel(t);
    setPhoto(url);
    setDateCreation(dc);
    setDateModif(dm);
}

/**
 * @brief Destructeur de la class Contact.
 */
Contact::~Contact(){}

/**
 * @brief récupérer les attributs de la class Contact.
 * @return nom, prénom, entreprise, mail, téléphone en string ainsi que les dates de creations et de modifications
 */
string Contact::getNom() const{return nom;}
string Contact::getPrenom() const{return prenom;}
string Contact::getEntreprise() const{return entreprise;}
string Contact::getMail() const{return mail;}
string Contact::getTel() const{return tel;}
string Contact::getPhoto() const{return urlPhoto;}
string Contact::getDateCreation() const{return dateCreation;}
string Contact::getDateModif() const{return dateModif;}

/**
 * @brief récupérer la liste d'Interaction du Contact.
 * @return lInteractions en vector<Interaction>
 */
vector<Interaction> Contact::getlInteractions() const{return linteractions;}
/**
 * @brief récupérer la référence de l'interaction par sa position dans la list d'Interaction d'un Contact.
 * @return linteractions [i] en Interaction
 */
Interaction& Contact::getInteractionI(int i){return linteractions[i];}

/**
 * @brief modifier les attributs d'un Contact, utiliser lors d'une modification ou dans le constructeur de la class Contact.
 */
void Contact::setNom(const string &n){nom = n;}
void Contact::setPrenom(const string &p){prenom = p;}
void Contact::setEntreprise(const string &e){entreprise = e;}
void Contact::setMail(const string &m){mail = m;}
void Contact::setTel(const string &t){tel = t;}
void Contact::setPhoto(const string &url){urlPhoto = url;}
void Contact::setDateCreation(const string &d){dateCreation = d;}
void Contact::setDateModif(const string &d){dateModif = d;}

/**
 * @brief permet d'ajouter une Interaction à la liste d'Interaction du Contact.
 * @param i Interaction référencié à ajouter à la liste
 */
void Contact::ajouterInteraction(Interaction& i)
{
    linteractions.push_back(i);
}

/**
 * @brief Surchargeur de l'operateur pour afficher un Contact
 * @param os, c flux de sortie et Contact à afficher
 */
ostream& operator<<(ostream &os, const Contact& c)
{
    os << c.nom << " " << c.prenom << endl; //<< "Date de création de la fiche contact : " << c.dateCreation << endl;

    vector<Interaction> li = c.getlInteractions();
    for(int n = 0; n< li.size();n++)
    {
        os << "Interaction n. " << n << "\n" << li[n] << endl;
    }
    return os;
}
