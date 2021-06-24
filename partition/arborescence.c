#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arborescence.h"

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
    int hauteur1 = hauteurs[classes[i]];
    int hauteur2 = hauteurs[classes[j]];

    if (hauteur1 < hauteur2)
    {
        if (hauteur1 == 1)
        {
            for (int k=0;k<TAILLE;k++)
            {
                if (classes[k] == classes[i])
                {
                    classes[k] = classes[j];     //relier la racine
                }
            }
        }
        else
        {
            classes[i] = classes[j];
        }
        
        hauteurs[classes[i]] = hauteur2;        //on ne modifie que la hauteur de la racine
    }
    else if (hauteur1 > hauteur2)
    {
        if (hauteur2 == 1)
        {
            for (int k=0;k<TAILLE;k++)
            {
                if (classes[k] == classes[j])
                {
                    classes[k] = classes[i];
                }
            }
        }
        else
        {
            classes[j] = classes[i];
        }
        
        hauteurs[classes[j]] = hauteur1;
    }
    else    //egalite des hauteurs
    {
        int min = fmin(classes[i],classes[j]);
        int max = fmax(classes[i],classes[j]);
        if (hauteur1 == 1)
        {
            for (int k=0;k<TAILLE;k++)
            {
                if (classes[k] == max)
                {
                    classes[k] = min;
                }
            }
        }
        else
        {
            if (max == classes[i])
            {
                classes[i] = min;
            }
            else
            {
                classes[j] = min;
            }
            
        }
        
        hauteurs[classes[i]] = hauteur1 + 1;
        hauteurs[classes[j]] = hauteurs[classes[i]];
    }
}

int recuperer_classe(int i, int *classes)
{
    int classe_avant = i;
    int classe_apres = classes[i];

    while (classe_avant != classe_apres)
    {
        classe_avant = classe_apres;
        classe_apres = classes[classe_avant];
    }
    return classe_avant;
}

void lister_classe(int classe, int *classes, int *liste, int *nb_elements)
{
    for (int k=0;k<TAILLE;k++)
    {
        int clas = recuperer_classe(k,classes);
        if (clas == classe)
        {
            liste[*nb_elements] = k;
            (*nb_elements)++;
        }
    }
}

void afficher_elements(int *liste, int nb_elements)
{
    int i = 0;
    
    while (i < nb_elements)
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
        classe = recuperer_classe(k,classes);
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

int main_arbo()
{
    int classes[TAILLE];
    int hauteurs[TAILLE];
    int elements_classe[TAILLE];
    cellule_t *liste_classes[TAILLE];
    int resultat;
    int nb_elements = 0;

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
        fusion(5,6,classes,hauteurs);
        fusion(5,2,classes,hauteurs);
        fusion(7,1,classes,hauteurs);
        graph_partition(fichier,classes);
        resultat = recuperer_classe(7,classes);
        printf("classe de 7 : %d\n",resultat);
        printf("elements de la classe 0 : ");
        lister_classe(0,classes,elements_classe,&nb_elements);
        afficher_elements(elements_classe,nb_elements);
        lister_partition(classes,liste_classes);
        system("dot -Tjpg graph_partition.dot -o graph_partition.jpg");
        fclose(fichier);
    }

    return 0;
}