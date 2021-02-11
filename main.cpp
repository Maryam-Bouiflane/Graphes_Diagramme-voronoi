#include "Grille.h"
#include <iostream>

using namespace std;

int main(){
    
    /*int colonnes, lignes;
    cout<<"Combien de lignes pour votre grille?"<<endl;
    cin>>lignes;
    cout<<"Combien de colonnes pour votre grille?"<<endl;
    cin>>colonnes;

    creer_fichier_altitude(colonnes, lignes);*/

    creer_fichier_altitude();

    Grille g("altitudes.txt");
    
    cout<<"=================== GRILLE ===================="<<endl<<endl;
    g.affiche_grille();

    cout<<endl<<"===================== TEST FONCTIONS ====================="<<endl;
    cout<<"Taille du tableau: "<<g.taille()<<endl;
    cout<<"Hauteur de la grille (L): "<<g.hauteur()<<endl;
    cout<<"Largeur de la grille (C): "<<g.largeur()<<endl<<endl;

    cout<<"i de la 3e case du tab 1D: "<<g.ligne(2)<<endl;
    cout<<"j de la 3e case du tab 1D: "<<g.colonne(2)<<endl;
    cout<<"Indice du sommet(0,2) du tab 1D: "<<g.indice(0,2)<<endl;
    cout<<"Altitude du sommet(0,2): "<<g.altitude2P(0,2)<<endl;
    cout<<"Altitude de la 3e case du tab 1D: "<<g.altitude(2)<<endl<<endl;

    cout<<"Nb de voisin de la 2e case du tab 1D: "<<g.nb_voisin(1)<<endl;
    cout<<"Nb de voisin de la 1ere case du tab 1D: "<<g.nb_voisin(1)<<endl;
    cout<<"Nb de voisin du sommet(0,0): "<<g.nb_voisin2P(0,0)<<endl;
    cout<<"Indice du voisin Nord du sommet(0,0): "<<g.voisin(0,NORD)<<endl;
    cout<<"Indice du voisin Est du sommet(0,0): "<<g.voisin(0,EST)<<endl;
    cout<<"Indice du voisin sud du sommet(0,0): "<<g.voisin(0,SUD)<<endl<<endl;

    cout<<"Poid de l'arête entre la 1ere case du tab 1D et son voisin Est: "<<g.poid_arete_voisin(0,EST)<<endl;
    cout<<"Poid de l'arête entre la 1ere case du tab 1D et son voisin Nord: "<<g.poid_arete_voisin(0,NORD)<<endl;

    cout<<endl<<"On modifie l'altitude du 1er sommet du tab 1D par 15"<<endl;
    g.modif_altitude(0,15);
    cout<<"On modifie l'altitude du sommet(0,1) par 20"<<endl;
    g.modif_altitude2P(0,1,20);

    cout<<endl<<"=============== GRILLE MODIFIER ==============="<<endl<<endl;
    g.affiche_grille();

    /* modifier toutes les altitudes de la grille
    cout<<endl<<endl<<"On passe toutes les altitudes de la grille à 0"<<endl;
    g.modif_altitude_grille_complete(0);

    cout<<endl<<"=============== GRILLE MODIFIER 2 ==============="<<endl<<endl;
    g.affiche_grille();
    */

    /* Dijkstra avec une unique source
    cout<<endl<<endl<<"================= TEST DE DIJKSTRA ================="<<endl;
    cout<<"Test de Dijkstra avec le sommet (0,0) comme source:"<<endl<<endl;
    g.dijkstra(0);
    */

    cout<<endl<<endl<<"=================== LIBRAIRIES ====================="<<endl;
    /*int nbLibrairie;
    cout<<"Combien de librairies/sites souhaitez vous?"<<endl;
    cin>>nbLibrairie;

    creer_fichier_librairie(nbLibrairie, colonnes, lignes);
    
    g.dijkstra(nbLibrairie, "librairies.txt");*/

    g.creer_fichier_librairie(5);

    g.dijkstra(5, "librairies.txt");   

    return 0;
}