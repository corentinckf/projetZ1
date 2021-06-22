#include <stdio.h>
#include <stdlib.h>
#include "liste_chainee.h"

//clear ; gcc liste_chainee.c -o prog ; ./prog


/* -------------------------------------------------------------------- */
/* creer_cellule         Creer une cellule d'une liste                  */
/*                       chainee avec une valeur                        */
/*                                                                      */
/* En entree: valeur (un entier)                                        */
/*                                                                      */
/* En sortie: retourne un pointeur sur la nouvelle cellule creer        */
/*            ou alors NULL en cas d'echec de malloc                    */
/* -------------------------------------------------------------------- */
cellule_t *creer_cellule(int valeur)
{
    cellule_t *nouv_cell;
    nouv_cell = (cellule_t *)malloc(sizeof(cellule_t));
    if (nouv_cell != NULL)
    {
        nouv_cell->valeur = valeur;
    }
    return nouv_cell;
}

/* -------------------------------------------------------------------- */
/* SUP_CEL       Supprime une cellule dans une liste chainee            */
/*                                                                      */
/* En entree: p_prec (pointeur sur la case pointeur, qui pointe sur     */
/*                  la cellule a supprimer )                            */
/*                                                                      */
/* En sortie: RIEN                                                      */
/* -------------------------------------------------------------------- */
void SUP_CEL(cellule_t **p_prec)
{
    cellule_t *sauv = *p_prec;
    *p_prec = sauv->suiv;
    free(sauv);
}

/* -------------------------------------------------------------------- */
/* ADJ_LCH        Ajoute une cellule dans une liste chainee             */
/*                                                                      */
/* En entree: elt (pointeur sur la cellule a inserer)                   */
/*            p_prec (pointeur sur la case pointeur, qui pointe sur     */
/*                  la cellule avant laquelle on veut inserer la        */
/*                  nouvelle cellule )                                  */
/*                                                                      */
/* En sortie: RIEN                                                      */
/* -------------------------------------------------------------------- */
void ADJ_LCH(cellule_t *elt, cellule_t **p_prec)
{
    elt->suiv = *p_prec;
    *p_prec = elt;
}

/* -------------------------------------------------------------------- */
/* RECH_PREC_LCH_TRIEE_DSC    Recherche l'endroit où inserer une        */
/*                            valeur dans lch triee decroissante        */
/*                                                                      */
/* En entree: p_tete (pointeur sur la tete de la liste chainee)         */
/*            v      (entier)                                           */
/*                                                                      */
/* En sortie: pointeur sur le precedent où inserer le nb v              */
/* -------------------------------------------------------------------- */
cellule_t **RECH_PREC_LCH_TRIEE_DSC(cellule_t **p_tete, int v)
{
    cellule_t *cour = *p_tete;
    cellule_t **p_prec = p_tete;

    while (cour != NULL && cour->valeur > v)
    {
        p_prec = &cour->suiv;
        cour = cour->suiv;
    }
    return p_prec;
}

/* -------------------------------------------------------------------- */
/* insertion_val_lch_triee_dsc       Insert une valeur dans une         */
/*                                    lch triee en decroissant          */
/*                                                                      */
/* En entree: p_tete (pointeur sur la tete de la lch)                   */
/*                                                                      */
/* En sortie: RIEN                                                      */
/* -------------------------------------------------------------------- */
void insertion_val_lch_triee_dsc(cellule_t **p_tete, int val_insert)
{
    cellule_t *nouv_cell = NULL;
    cellule_t **p_prec = p_tete;

    p_prec = RECH_PREC_LCH_TRIEE_DSC(p_tete, val_insert);
    nouv_cell = creer_cellule(val_insert);
    if (nouv_cell != NULL)
    {
        ADJ_LCH(nouv_cell, p_prec);
    }
    else
    {
        printf("Erreur de creation de nouvelle cellule.\n");
    }
}

/* -------------------------------------------------------------------- */
/* liberer_lch       Libere les allocation de la lch                    */
/*                                                                      */
/* En entree: p_tete     (pointeur sur la tete de la lch)               */
/*            val_insert (un entier)                                    */
/*                                                                      */
/* En sortie: RIEN                                                      */
/* -------------------------------------------------------------------- */
void liberer_lch(cellule_t **p_tete)
{
    while (*p_tete != NULL)
    {
        SUP_CEL(p_tete);
    }
}

/* -------------------------------------------------------------------- */
/* afficher_lch       Affiche une liste chainee dans la console         */
/*                                                                      */
/* En entree: p_tete (pointeur sur la tete de la lch)                   */
/*                                                                      */
/* En sortie: RIEN                                                      */
/* -------------------------------------------------------------------- */
void afficher_lch(cellule_t **p_tete)
{

    printf("Debut de la liste chainee : ");
    cellule_t *cour = *p_tete;
    while (cour != NULL)
    {
        printf("|%d| -> ", cour->valeur);
        cour = cour->suiv;
    }
    printf("NULL");
    printf(" Fin de la liste chainee\n");
}

/* -------------------------------------------------------------------- */
/* sauv_lch_fichier       Sauvegarde une lch dans un fichier txt        */
/*                                                                      */
/* En entree: nom_fichier (chaine de caracteres)                        */
/*            p_tete      (pointeur sur la tete de la lch)              */
/*                                                                      */
/* En sortie: RIEN                                                      */
/* -------------------------------------------------------------------- */
void sauv_lch_fichier(char *nom_fichier, cellule_t **p_tete)
{
    cellule_t *cour = *p_tete;

    FILE *fichier;
    fichier = fopen(nom_fichier, "w");

    if (fichier != NULL)
    {
        while (cour != NULL)
        {
            fprintf(fichier, "|%d| -> ", cour->valeur);
            cour = cour->suiv;
        }
        fprintf(fichier, "NULL");
    }

    fclose(fichier);
}