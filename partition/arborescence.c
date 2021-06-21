#include <stdio.h>
#include <stdlib.h>
#include "arborescence.h"

#define TAILLE 11

void creer(int *classes, int *hauteurs)
{
    for (int i=0;i<TAILLE;i++)
    {
        classes[i] = i;
        hauteurs[i] = 1;
    }
}

void afficher_tab(int *tab)
{
    fprintf(stdout,"contenu du tableau : \t");
    for (int i=0;i<TAILLE;i++)
    {
        fprintf(stdout,"%d\t",tab[i]);
    }
    fprintf(stdout,"\n");
}

void fusion(int i, int j, int *classes, int *hauteurs)
{
    int hauteur1 = hauteurs[i];
    int hauteur2 = hauteurs[j];

    if (hauteur1 < hauteur2)
    {
        hauteurs[i] = hauteur2;
        for (int k=0;k<TAILLE;k++)
        {
            if (classes[k] == classes[i])
            {
                classes[k] = classes[j];     //relier la racine
            }
        }
    }
    else if (hauteur1 > hauteur2)
    {
        hauteurs[j] = hauteur1;
        for (int k=0;k<TAILLE;k++)
        {
            if (classes[k] == classes[j])
            {
                classes[k] = classes[i];
            }
        }
    }
    else    //egalite des hauteurs
    {
        hauteurs[i] = hauteur1 + 1;
        hauteurs[j] = hauteurs[i];
        for (int k=0;k<TAILLE;k++)
        {
            if (classes[k] == classes[j])
            {
                classes[k] = classes[i];
            }
        }
    }
}

int recuperer_classe(int i, int *classes)
{
    return classes[i];
}

int lister_classe(int indice, int *indices, int *classes, int *liste)
{
    int i = 0;
    for (int k=0;k<TAILLE;k++)
    {
        if (classes[k] == classes[indice])
        {
            liste[i] = indices[k];
            i++;
        }
    }
    liste[i] = '\0';
}

void afficher_elements(int *liste)
{
    int i = 0;
    
    while (liste[i] != '\0')
    {
        fprintf(stdout,"%d\t",liste[i]);
        i++;
    }
    fprintf(stdout,"\n");
}

void lister_partition(int *indices, int *classes, cellule_t *liste_classes[TAILLE])
{
    cellule_t *tete = NULL;
    int classe;

    for (int k=0;k<TAILLE;k++)
    {
        classe = classes[k];
        tete = liste_classes[classe];
        ADJ_TETE(&tete,indices[k]);
        liste_classes[classe] = tete;
    }
}

void ADJ_TETE(cellule_t **ptete, int el)
{
    cellule_t *nouv = NULL;
    nouv = (cellule_t *) malloc(sizeof(cellule_t));

    if (nouv)
    {
        nouv->indice = el;
        nouv->suiv = *ptete;
        *ptete = nouv;
    }
}

void fichier_graphiz(int *tas)
{
    FILE *fichier = NULL;
    fichier = fopen("graph_tas.dot", "w");
    
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    fprintf(fichier, "graph { ");
}

int main()
{
    int indices[TAILLE];
    int classes[TAILLE];
    int hauteurs[TAILLE];
    int elements_classe[TAILLE];
    cellule_t *liste_classes[TAILLE];
    int resultat;

    for (int k=0;k<TAILLE;k++)
    {
        liste_classes[k] = NULL;
    }

    //remplir tableau des indices
    for (int i=0;i<TAILLE;i++)
    {
        indices[i] = i;
    }

    creer(classes,hauteurs);
    afficher_tab(classes);
    fusion(2,3,classes,hauteurs);
    fusion(4,3,classes,hauteurs);
    resultat = recuperer_classe(3,classes);
    printf("elements de la classe 3 :\t");
    lister_classe(3,indices,classes,elements_classe);
    afficher_elements(elements_classe);
    lister_partition(indices,classes,liste_classes);

    return 0;
}