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

void lister_classe(int indice, int *classes, int *liste)
{
    int i = 0;
    for (int k=0;k<TAILLE;k++)
    {
        if (classes[k] == classes[indice])
        {
            liste[i] = k;
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

void lister_partition(int *classes, cellule_t *liste_classes[TAILLE])
{
    cellule_t *tete = NULL;
    int classe;

    for (int k=0;k<TAILLE;k++)
    {
        classe = classes[k];
        tete = liste_classes[classe];
        ADJ_TETE(&tete,k);
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

void graph_partition(FILE *fichier, int *classes)
{
    fprintf(fichier, "digraph {\n");

    for (int k=0;k<TAILLE;k++)
    {
        if (k == classes[k])
        {
            fprintf(fichier,"\t%d -> %d\n",k,k);
        }
        else
        {
            fprintf(fichier,"\t%d -> %d\n",k,classes[k]);
        }
    }
    fprintf(fichier, "}");
}

int main()
{
    int classes[TAILLE];
    int hauteurs[TAILLE];
    int elements_classe[TAILLE];
    cellule_t *liste_classes[TAILLE];
    int resultat;

    for (int k=0;k<TAILLE;k++)
    {
        liste_classes[k] = NULL;
    }
    
    FILE *fichier = NULL;
    fichier = fopen("graph_partition.dot", "w");
    
    if (fichier == NULL)
    {
        printf("erreur d'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    if (fichier)
    {      
        creer(classes,hauteurs);
        fusion(2,3,classes,hauteurs);
        fusion(4,3,classes,hauteurs);
        graph_partition(fichier,classes);
        resultat = recuperer_classe(3,classes);
        printf("elements de la classe 3 :\t");
        lister_classe(3,classes,elements_classe);
        afficher_elements(elements_classe);
        lister_partition(classes,liste_classes);
        fclose(fichier);
    }

    return 0;
}