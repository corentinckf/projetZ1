#ifndef __tasbin_h__
#define __tasbin_h__

typedef struct tete{
    int fin;
    int *tas;
}tete_t;

int fils1(int i);
int fils2(int i);
int pere(int i);
void init(tete_t **tete);
int estPlein(tete_t *tete);
int estVide(tete_t *tete);
void ajouter(tete_t *tete, int valeur);
void retirer_racine(tete_t *tete, int *res);
int fils_min(tete_t *tete, int i);
void construire(int *tab, tete_t *tete, int nb_elements);
void afficher_tas(tete_t *tete);
void percolate_down(tete_t *tete, int place);
void percolate_up(tete_t *tete, int place);
int tri(tete_t *tete, int *tab, int *liste, int nb_elements);
void afficher_tab(int *liste, int nb_elements);
void liberer_tas(tete_t *tete);
void tas_graphviz(FILE *fichier, tete_t *tete);
void relier_pere_fils(FILE *fichier, tete_t *tete, int i);
int inf(int *v1, int *v2);

#endif