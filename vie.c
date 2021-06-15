#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//taille de la grille
#define LIGNES 30
#define COLONNES 50

//le tableau survie est rempli de 0 et 1 : si survie[k]=1, alors la cellule survit et 0 sinon
int survie[9];
int naissance[9];

//on construit les tableaux survie et naissance aléatoirement
/*int k;

for (k=0;k<9;k++)
{
    survie[k]=rand()%2;
    naissance[k]=rand()%2;
}*/

//on construit les tableaux survie et naissance selon la regle donnée par ScienceEtonnante
int k;

for (k=0;k<9;k++)
{
    survie[k]=0;
    naissance[k]=0;
}
survie[2]=survie[3]=1;
naissance[3]=1;

//retourne 1 si la cellule survit et 0 si elle meurt
int devenir(int **mat, int *i, int *j)
{
    int s=0;
    int ligne,colonne;
    int resultat=-1; //la valeur -1 indique une erreur

    for (ligne = ((*i)-1 + LIGNES) % LIGNES ; ligne = ((*i)+2) % LIGNES ; ligne++)
    {
        for (colonne = ((*j)-1 + COLONNES) % COLONNES ; colonne = ((*j)+2) % COLONNES ; colonne++)
        {
            s+=mat[ligne][colonne];
        }
    }
    s-=mat[*i][*j];
    //s est la somme des 8 cases entourant la cellule (i,j)

    if (mat[*i][*j] == 1)   //cellule en vie
    {
        resultat = survie[s];
    }
    else        //cellule morte
    {
        resultat = naissance[s];
    }
    changement = (resultat == mat[*i][*j]);
    return resultat;    
}

//evolution de l'etat N à l'etat N+1
int evolution(int **mat, int **matsuiv)
{
    int changement=0,resultat;
    int ligne=0,colonne=0;
    int i,j;

    while (ligne < LIGNES && changement == 0)
        {
            while (colonne < COLONNES && changement == 0)
            {
                resultat=devenir(mat,&ligne,&colonne);
                if (resultat < 0)
                {
                    fprintf(stderr,"probleme d'evolution");
                }
                else
                {
                   matsuiv[ligne][colonne] = resultat;
                   if (mat[ligne][colonne] != mat[ligne][colonne])
                    {
                        changement=1;
                    }
                } 
            }
        }

        for (j=colonne;j<COLONNES;j++)
        {
            resultat=devenir(mat,&ligne,&j);
            if (resultat < 0)
            {
                fprintf(stderr,"probleme d'evolution");
            }
            else
            {
                matsuiv[ligne][j] = resultat;
            }
        }

        for (i=ligne+1;i<LIGNES;i++)
        {
            for (j=0;j<COLONNES;j++)
            {
                resultat=devenir(mat,&i,&j);
                if (resultat < 0)
                {
                    fprintf(stderr,"probleme d'evolution");
                }
                else
                {
                    matsuiv[i][j] = resultat;
                }
            }
        }
    return changement;
}

int main()
{
    int etat_n[LIGNES][COLONNES];
    int etat_n+1[LIGNES][COLONNES];
    int changement=1;
    int ligne=0,colonne=0;
    int i,j;

    //initialisation aléatoire
    for (i=0;i<LIGNES;i++)
    {
        for (j=0;j<COLONNES;j++)
        {
            etat_n[i][j] = rand()%2;
        }
    }

    while (changement)
    {
        //afficher l'etat n
        changement = evolution(etat_n,etat_n+1);
        //afficher l'etat n+1
    }

    return 0;
}