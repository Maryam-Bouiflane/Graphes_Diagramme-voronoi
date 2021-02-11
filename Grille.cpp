#include <iostream>
#include <fstream>
#include <random>
#include <cassert>
#include <string.h>
#include <queue>
#include <vector>
#include <math.h>
#include <limits>
#include <algorithm>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h>

#include "Grille.h"

using namespace std;

//element de la priority_queue
struct ElementPQ {

    //Donnees membres
    int indiceSommet;
    float priorite; //correspond à la distance entre le sommet numero indiceSommet et la source

    //constructeur
    ElementPQ(int i, int p){
        indiceSommet=i;
        priorite=p;
    }
};

bool operator<(const ElementPQ& p1, const ElementPQ& p2) {
  return p1.priorite < p2.priorite;
}

Grille:: Grille(const char * nomFichier){

    ifstream lecture(nomFichier);
    if(lecture.is_open()){
        while(!lecture.eof()) {
            lecture>>C>>L;
            int taille=L*C;
            tab.reserve(taille);

            int alt;
            for(int i=0; i<taille; i++){
                lecture>>alt;
                tab.push_back(alt);
            }
        }
        lecture.close();
    }else{ cout<<"Erreur d’ouverture du fichier: ";}
}

int Grille::taille(){
    return L*C;
}

int Grille::hauteur(){
    return L;
}

int Grille::largeur(){
    return C;
}

int Grille::indice(int i, int j){
    return i*C+j;
}

int Grille::ligne(int indice){
    return indice/C;
}

int Grille::colonne(int indice){
    return indice%C;
}

int Grille::altitude2P(int i, int j){
    int ind=indice(i,j);
    return tab[ind];
}

int Grille::altitude(int indice){
    return tab[indice];
}

int Grille::voisin(int Indice, Direction d){
    int i=ligne(Indice);
    int j=colonne(Indice);

    int iv, jv;
    int indiceVoisin;

    switch(d){

        case 0: iv=i-1;
                jv=j;
                break;

        case 1: iv=i+1;
                jv=j;
                break;

        case 2: iv=i;
                jv=j+1;
                break;

        case 3: iv=i;
                jv=j-1;
                break;

        default: assert( ! "Invalid Direction value" );
                 break;
    }

    if (iv>=0 && iv<L && jv>=0 && jv<C){

        indiceVoisin=indice(iv,jv);
        return indiceVoisin;

    }else return -1;
    

}

Direction& operator ++ (Direction& d){

    if (d == Direction::end){
        throw std::out_of_range("for Direction& operator ++ (Direction&)");
    }
    d = Direction(static_cast<std::underlying_type<Direction>::type>(d) + 1);
    return d;
}

int Grille::nb_voisin(int indice){

    int indiceVoisin;
    int nbVoisin=0;

    for(Direction d=Direction::NORD; d != Direction::end; ++d){

        indiceVoisin=voisin(indice,d);
        if(indiceVoisin != -1){
            nbVoisin++;
        }
    }
    return nbVoisin;
}

int Grille::nb_voisin2P(int i, int j){

    int ind=indice(i,j);
    int indiceVoisin;
    int nbVoisin=0;

    for(Direction d=Direction::NORD; d != Direction::end; ++d){

        indiceVoisin=voisin(ind,d);
        if(indiceVoisin != -1){
            nbVoisin++;
        }
    }
    return nbVoisin;
}

float Grille::poid_arete_voisin(int Indice, Direction d){
    int i=ligne(Indice);
    int j=colonne(Indice);

    int iv, jv, indiceVoisin;
    float poid;

    switch(d){

        case 0: iv=i-1;
                jv=j;
                break;

        case 1: iv=i+1;
                jv=j;
                break;

        case 2: iv=i;
                jv=j+1;
                break;

        case 3: iv=i;
                jv=j-1;
                break;

        default: assert( ! "Invalid Direction value" );
                 break;
    }

    if (iv>=0 && iv<L && jv>=0 && jv<C){

        indiceVoisin=indice(iv,jv);
        poid=sqrt(1 + pow((tab[Indice] - tab[indiceVoisin]), 2) );
        return poid;

    }else return -2;
    
}

void Grille::modif_altitude(int indice, int new_altitude){

    tab[indice]=new_altitude;
}

void Grille::modif_altitude2P(int i, int j, int new_altitude){
    int ind=indice(i,j);
    tab[ind]=new_altitude;
}

void Grille::modif_altitude_grille_complete(int new_altitude){
    int Taille=taille();
    for(int i=0; i<Taille; i++){
        tab[i]=new_altitude;
    }
}

void Grille::affiche_grille(){
    
    for(int i = 0; i <L; ++i) {
        for(int j = 0; j <C; ++j) {
            cout<<tab[i*C+j]<<"   " ;
        }
        cout<<endl;
    }
}

void Grille::dijkstra(int nbLibrairie, const char * nomFichier){ 
    
    int Taille=taille();

    //on défini nos tableaux pour stocker: la couleur,
    //les distances les plus courtes entre la source et un sommet,
    //les librairies les plus proches et l'indice des sommets sources
    COULEUR couleur[Taille];
    float distance[Taille];
    int precedent[Taille];
    int src[nbLibrairie];

    
    //on initialise les tableaux locaux
    for(int i=0; i<Taille; i++){
        couleur[i]=BLANC;
        //on initialise à l'infini
        precedent[i]= std::numeric_limits<int>::infinity();
        distance[i]= std::numeric_limits<float>::infinity();
    }

    //on initialise le tableau de sources
    for (int k=0; k<nbLibrairie; k++){
        src[k]=0;
    }

    //on lit le fichier "librairies.txt" pour remplir notre tableau de sources avec leur indices 
    ifstream lecture(nomFichier);
    if(lecture){

            lecture>>nbLibrairie;

            //on remplit notre tableau de sources avec toutes les librairies
            int i, j;
            cout<<endl;
            for(int k=0; k<nbLibrairie; k++){
                lecture>>i>>j;
                src[k]=indice(i,j);
                cout<<"la librairie "<<k+1<<" est le sommet ("<<i<<","<<j<<"), son indice global est "<<src[k]<<endl;
            }
            cout<<endl;

    }else{ cout<<"Erreur d’ouverture du fichier: ";}
    
    //on declare notre file à priorité
    priority_queue <ElementPQ> pq ;

    //on execute dijkstra sur toutes les sources et on met à jour les tab distance et precedent
    for(int k=0; k<nbLibrairie; k++){ 

        //on insere les sources dans la file et on met à jour les tableaux
        ElementPQ sommetD(src[k],0.0);
        pq.push(sommetD);

        distance[src[k]]=0.0;
        precedent[src[k]]=src[k];
        couleur[src[k]]=GRIS;

        //tant que la file n'est pas vide
        while(!pq.empty()){

            //s sommet de la file (qui a la distance/priorité minimal)
            ElementPQ s=pq.top() ;
            //on sort s de la file
            pq.pop();
            //ds la distance entre src et s
            float ds=distance[s.indiceSommet];

            for(Direction dir=Direction::NORD; dir != Direction::end; ++dir){

                //v l'indice du voisin
                int v=voisin(s.indiceSommet,dir);
                //si le voisin n'existe pas on passe à l'itération suivante
                if (v == -1) continue;

                //sv distance entre s et le voisin v
                float sv=poid_arete_voisin(s.indiceSommet,dir);

                if(couleur[v] == BLANC){

                    float dv=distance[v];
                    //si c'est la 1ere fois qu'on parcourt la grille
                    if (dv == std::numeric_limits<float>::infinity() ){
                        //on colorie v en gris-> on l'ajoute dans la file-> on ajoute sa distance-> on stock son precedent pour retrouver le chemin
                        couleur[v]=GRIS;

                        float newChemin=ds+sv;
                        ElementPQ sommetV(v,newChemin);
                        pq.push(sommetV);

                        distance[v]=newChemin;
                        precedent[v]=src[k];

                    } else if (ds+sv<dv){ //si on a deja le tableau distance remplit par le parcours de dijkstra avec une autre source
                        couleur[v]=GRIS;

                        float newChemin=ds+sv;
                        //relachement des arcs:
                        //on met à jour le plus court chemin avec le nouveau qu'on vient de trouver
                        ElementPQ sommetV(v,newChemin);
                        pq.push(sommetV);

                        distance[v]=newChemin;
                        precedent[v]=src[k];
                    }
                }

                if(couleur[v] == GRIS){

                    //dv distance entre d et v (deja calculer avant)
                    float dv=distance[v];

                    float newChemin=ds+sv;
                    //on verifie si le nouveau chemin trouvé est plus court que le precedent enregistré
                    if (newChemin<dv){
                        //relachement des arcs:
                        //on met à jour le plus court chemin avec le nouveau qu'on vient de trouver
                        ElementPQ sommetV(v,newChemin);
                        pq.push(sommetV);

                        distance[v]=newChemin;
                        precedent[v]=src[k];
                    }
                }
            }
            //on colorie s en noir 
            couleur[s.indiceSommet]=NOIR;
        }
        //on reinitialise le tableau de couleur à BLANC pour un nouveau parcours de la grille avec une nouvelle source
        for(int i=0; i<Taille; i++){
            couleur[i]=BLANC;
        }
    }

    cout<<"Tableau de librairies:"<<endl;
    for (int k=0; k<nbLibrairie; k++){
        cout<<src[k]<<"  ";
    }

    cout<<endl<<endl<<"Tableau de distances:"<<endl;
    for (int i=0; i<Taille; i++){
        cout<<distance[i]<<"  ";
    }

    cout<<endl<<endl<<"======================= DIAGRAMME DE VORONOI ======================"<<endl;
    int color=40;
    for(int i = 0; i <L; ++i) {
        for(int j = 0; j <C; ++j) {
            for (int k=0; k<nbLibrairie; k++){
                if(precedent[i*C+j] == src[k]){
                
                    cout<<"\033[0;37;"<<color<<"m"<<precedent[i*C+j]<<" "<<"\033[0m";
                }
                color++;
            }
            color=40;
        }
        cout<<endl;
    }
    /*
    cout<<endl<<endl<<"Tableau de couleur:"<<endl;
    for (int i=0; i<Taille; i++){
        if(couleur[i] == BLANC) cout<<"B  ";
        if(couleur[i] == GRIS) cout<<"G  ";
        if(couleur[i] == NOIR) cout<<"N  ";
    }
    */
}

void creer_fichier_altitude(){

    int colonnes=15;
    int lignes=10;

    std::ofstream fichier("altitudes.txt") ;

    fichier << colonnes << "   " << lignes << std::endl ;

    std::mt19937 alea ;
    std::uniform_int_distribution<int> rand_altitude(0, 9) ;

    for(int i = 0; i <lignes; ++i) {
        for(int j = 0; j <colonnes; ++j) {
            fichier << rand_altitude(alea) << "   " ;
        }
        fichier <<std::endl;
    }
    fichier << std::endl ;
}

void Grille::creer_fichier_librairie(int nbLibrairie){
    srand (time(NULL));
    ofstream fichier("librairies.txt") ;

    fichier << nbLibrairie << endl ;
    
    int l,c;
    for(int i = 0; i <nbLibrairie; ++i) {
        
        do{
            l=rand()%L;
            c=rand()%C;
        }while(indice(l,c)>=L*C);
        
        fichier<<l<<"   "<<c<<endl;
    }
}

/* Dijkstra avec une unique source
void Grille::dijkstra(int src){  //src l'indice de notre sommet source
    
    int Taille=taille();

    //on défini nos tableaux pour stocker la couleur,
    //les distances les plus courtes entre la source et un sommet
    //et les precedents
    COULEUR couleur[Taille];
    float distance[Taille];
    int precedent[Taille]; 
    
    //on initialise les tableaux locaux
    for(int k=0; k<Taille; k++){
        couleur[k]=BLANC;
        //on initialise à l'infini
        precedent[k]= std::numeric_limits<int>::infinity();
        distance[k]= std::numeric_limits<float>::infinity();
    }

    //on declare notre file à priorité
    priority_queue <ElementPQ> pq ;

    //on insere d dans la file et on met à jour les tableaux
    ElementPQ sommetD(src,0.0);
    pq.push(sommetD);

    distance[src]=0.0;
    precedent[src]=src;
    couleur[src]=GRIS;

    //tant que la file n'est pas vide
    while(!pq.empty()){

        //s sommet de la file (qui a la distance/priorité minimal)
        ElementPQ s=pq.top() ;
        //on sort s de la file
        pq.pop();
        //ds la distance entre d et s
        float ds=distance[s.indiceSommet];

        for(Direction dir=Direction::NORD; dir != Direction::end; ++dir){

            //v l'indice du voisin
            int v=voisin(s.indiceSommet,dir);
            //si le voisin n'existe pas on passe à l'itération suivante
            if (v == -1) continue;

            //sv distance entre s et le voisin v
            float sv=poid_arete_voisin(s.indiceSommet,dir);

            if(couleur[v] == BLANC){

                //on colorie v en gris-> on l'ajoute dans la file-> on ajoute sa distance-> on stock son precedent pour retrouver le chemin
                couleur[v]=GRIS;

                float newChemin=ds+sv;
                ElementPQ sommetV(v,newChemin);
                pq.push(sommetV);

                distance[v]=newChemin;
                precedent[v]=s.indiceSommet;
            }

            if(couleur[v] == GRIS){

                //dv distance entre d et v (deja calculer avant)
                float dv=distance[v];

                float newChemin=ds+sv;
                //on verifie si le nouveau chemin trouvé est plus court que le precedent enregistré
                if (newChemin<dv){
                    //relachement des arcs:
                    //on met à jour le plus court chemin avec le nouveau qu'on vient de trouver
                    ElementPQ sommetV(v,newChemin);
                    pq.push(sommetV);

                    distance[v]=newChemin;
                    precedent[v]=s.indiceSommet;
                }
            }
        }
        //on colorie s en noir 
        couleur[s.indiceSommet]=NOIR;
    }

    cout<<"Tableau de distances:"<<endl;
    for (int k=0; k<Taille; k++){
        cout<<distance[k]<<"  ";
    }

    cout<<endl<<endl<<"Tableau de precedent:"<<endl;
    for (int k=0; k<Taille; k++){
        cout<<precedent[k]<<"  ";
    }

    cout<<endl<<endl<<"Tableau de couleur:"<<endl;
    for (int k=0; k<Taille; k++){
        if(couleur[k] == BLANC) cout<<"B  ";
        if(couleur[k] == GRIS) cout<<"G  ";
        if(couleur[k] == NOIR) cout<<"N  ";
    }
    cout<<endl;
}*/
