#include <iostream>
#include <vector>

using namespace std;

enum Direction{

    NORD=0,
    SUD=1,
    EST=2,
    OUEST=3,
    end
};

enum COULEUR{

    BLANC,
    GRIS,
    NOIR
};

class Grille{

    int C; //colonne, largeur
    int L; //ligne,hauteur
    vector <int> tab;

    public:
        
        Grille(const char * nomFichier);

        int taille();
        int hauteur();
        int largeur();

        int indice(int i, int j);
        int ligne(int indice);
        int colonne(int indice);
        
        int altitude2P(int i, int j);
        int altitude(int indice);

        int nb_voisin(int indice);
        int nb_voisin2P(int i, int j);
        int voisin(int Indice, Direction d);

        float poid_arete_voisin(int Indice, Direction d);

        void modif_altitude(int indice, int new_altitude);
        void modif_altitude2P(int i, int j, int new_altitude);
        void modif_altitude_grille_complete(int new_altitude);

        void affiche_grille();
        
        //Dijkstra avec une unique source
        //void dijkstra(int src);

        void dijkstra(int nbLibrairie, const char * nomFichier);
        void creer_fichier_librairie(int nbLibrairie);
};

void creer_fichier_altitude();
//void creer_fichier_librairie(int nbLibrairie, int C, int L);