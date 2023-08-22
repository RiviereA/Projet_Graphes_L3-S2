#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <time.h>

using namespace std;
const int n=5;     //Graphe à n sommets
int adj[n][n];  // matrice d’adjacence du graphe
int W[n][n];   //Matrice après l'algo FloydWarshall
int Pexacte[n][n];
vector< vector<int> > listClique;

vector<int> Intersect(vector<int> A, vector<int> B){    //Fais l'intersection de deux liste
    vector<int> I;
    for(int i = 0; i<A.size(); i++){
        for(int j = 0; j<B.size(); j++){
            if(A[i]==B[j]) I.push_back(A[i]);
        }
    }
    return I;
}

vector<int> Suppr(vector<int> A, int b){    //Supprime le sommet b de la liste
    for(int i = 0; i<A.size(); i++){
        if(A[i]==b) A.erase(A.begin()+i);
    }
    return A;
}

vector<int> GetV(int v){    //Obtient les voisin du sommet v
    vector<int> V;
    for(int i = 0; i<n; i++){
        if(adj[v][i]==1) V.push_back(i);
        //if(Pexacte[v][i]==1) V.push_back(i);
    }
    return V;
}

void BronKerBosch(vector<int> R, vector<int> P, vector<int> X){
    if((P.size() == 0) && (X.size() == 0) && (R.size()>1)){
        printf("Clique maximale :");
        vector<int> clique;
        for (int i=0; i<R.size(); i++){
            printf(" %d ", R[i]);
            clique.push_back(R[i]);
        }
        printf("\n");
        listClique.push_back(clique);
        return;
    }

    vector<int> P1;
    for(int i = 0; i<P.size();i++){P1.push_back(P[i]);}

    for(int i = 0; i < P.size(); i++){
        int v = P[i];
        vector<int> N = GetV(v);
        R.push_back(v);
        BronKerBosch(R,Intersect(P1,N),Intersect(X,N));
        P1 = Suppr(P1,v);
        R = Suppr(R,v);
        X.push_back(v);
    }
}


//_____________________________________________________________________________________________________________________________
void GenereGraphe(int p){ //p est la probabilité que deux sommets soit reliés
    srand(time(NULL));
    int x;
    for (int i=0;i<n;i++){
        for (int j=n-1;j>=i;j--){
            x=rand()%101;
            if(x<=p && i!=j){
                adj[i][j]=1;
                adj[j][i]=1;

                W[i][j]=1;
                W[j][i]=1;
            }
			else{
                W[i][j]=n; //n représente l'infini ici
                W[j][i]=n; //il n'y aura jamais n points reliés à la suite
			}
        }
    }
}

void AfficheAdj(int tab[n][n]) //Affiche les matrices d'adjacence
{
    for(int i=0;i<n;i++)
	{
        for(int j=0;j<n;j++)
		{
            if(tab[i][j]==n) //n pour l'infini
			{
				printf("inf  ");
			}
			else printf(" %d   ",tab[i][j]);
        }
        printf("\n");
    }
}

void FloydWarshall(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
                if(i==j){ W[i][j]= 0; }
				else{ if(W[i][k]+W[k][j] <= W[i][j]){ W[i][j]= W[i][k]+W[k][j];}}
			}
        }
    }
}

void PuissanceExacte(int d){
	FloydWarshall();
	for (int i=0;i<n;i++){
        for (int j=n-1;j>=i;j--){
            if(W[i][j]==d){
                Pexacte[i][j]=1;
                Pexacte[j][i]=1;
            }
        }
    }
}

int main(int argc, char *argv[]){

    GenereGraphe(50);
    PuissanceExacte(2);

    printf("Matrice d'adjacence\n");
    AfficheAdj(adj);

    printf("\n\nPlus courte distance\n");
    AfficheAdj(W);

    printf("\n\nPuissance exacte\n");
    AfficheAdj(Pexacte);

    printf("\n\nListe des cliques maximales\n");
    vector<int> R;
    vector<int> P;
    for (int i=0; i<n; i++){
        P.push_back(i);
    }
    vector<int> X;
    BronKerBosch(R,P,X);

    int tailleCliqM = 0;
    for (int i=0; i<listClique.size(); i++)
    {
        if (listClique[i].size() > tailleCliqM) tailleCliqM = listClique[i].size();
    }
    printf("\nLa taille de la clique maximum est : %d\n",tailleCliqM);

    ofstream fichier("Clique.txt", ios::out | ios::trunc);
    if(fichier)
    {
        for (int j=0; j<listClique.size(); j++)
        {
            if (listClique[j].size() == tailleCliqM) {
                for (int k=0; k<listClique[j].size(); k++)
                {
                    fichier << listClique[j][k] << "\t";
                }
                fichier << endl;
            }
        }
        fichier.close();
    } else {
        cerr << "Erreur à l'ouverture !" << endl;
    }

    return 0;
}
