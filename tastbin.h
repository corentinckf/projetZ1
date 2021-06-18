#ifndef __tastbin_h__
#define __tastbin_h__

typedef struct tete{
    int nb_elements;
    int *tas;
}tete_t;

int fils1(int i);
int fils2(int i);
int pere(int i);
void init (tete_t **tete);
void ajouter(tete_t *tete, int valeur);
void augmenter(tete_t *tete, int place, int augmenter);
void construire(int tab[7],tete_t *tete);
void liberer_tas(tete_t **tete);
void afficher_tas(tete_t *tete);

#endif