#ifndef __arborescence_h__
#define __arborescence_h__

#define TAILLE 11

typedef struct cellule{
    int indice;
    struct cellule *suiv;
}cellule_t;

void creer(int *classes, int *hauteurs);
void afficher_tab(int *tab);
void fusion(int i, int j, int *classes, int *hauteur);
int recuperer_classe(int i, int *classes);
int lister_classe(int classe, int *indices, int *classes, int *liste);
void afficher_elements(int *liste);
void lister_partition(int *indices, int *classes, cellule_t *liste_classes[TAILLE]);
void ADJ_TETE(cellule_t **ptete, int el);

#endif