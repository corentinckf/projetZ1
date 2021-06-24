#ifndef __tasbin_h__
#define __tasbin_h__

typedef struct tete{
    int nb_elements;
    int *tas;
}tete_t;

int fils1(int i);
int fils2(int i);
int pere(int i);
void init(tete_t **tete);
int estPlein(tete_t *tete);
int estVide(tete_t *tete);
int ajouter(tete_t *tete, int valeur);
int retirer_racine(tete_t *tete, int *res);
void modifier(tete_t *tete, int place, int augmenter);
void construire(int tab[7], tete_t *tete);
void afficher_tas(tete_t *tete);

#endif