#ifndef __LISTE_CHAINEE_H__
#define __LISTE_CHAINEE_H__

typedef struct liste_chainee
{
    int valeur;
    struct cellule_t *suiv;
} cellule_t;

int main_lch();

cellule_t *creer_cellule(int valeur);
void SUP_CEL(cellule_t **prec);
void ADJ_LCH(cellule_t *elt, cellule_t **prec);
cellule_t **RECH_PREC_LCH_TRIEE_DSC(cellule_t **tete, int v);
void insertion_val_lch_triee_dsc(cellule_t **p_tete, int val_insert);
void liberer_lch(cellule_t **tete);
void afficher_lch(cellule_t **tete);

void sauv_lch_fichier(char *nom_fichier, cellule_t **p_tete);

#endif