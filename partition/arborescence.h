#ifndef __arborescence_h__
#define __arborescence_h__

#define LIGNES 6
#define COLONNES 4
#define TAILLE LIGNES*COLONNES

typedef struct cellule{
    int indice;
    struct cellule *suiv;
}cellule_t;

void creer(int *classes, int *hauteurs);
void afficher_tab(int *tab);
void fusion(int i, int j, int *classes, int *hauteurs);
int recuperer_classe(int i, int *classes);
void lister_classe(int classe, int *classes, int *liste, int *nb_elements);
void afficher_elements(int *liste, int nb_elements);
void lister_partition(int *classes, cellule_t *liste_classes[TAILLE]);
void ADJ_TETE(cellule_t **ptete, int el);
void graph_partition(FILE *fichier, int *classes);

#endif