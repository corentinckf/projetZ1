#include "tas_binaire.h"

int main_tas_binaire()
{

    return 0;
}

void affficher_tab(int *tab, int nb_elt)
{
    for (int i = 0; i < nb_elt; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}
void affficher_tas(couple_t *tab, int nb_elt)
{
    for (int i = 0; i < nb_elt; i++)
    {
        printf(" %d|d=%d,n=%d| ", i, tab[i].d, tab[i].n);
    }
    printf("\n");
}

void init_tab(int tab[N])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        tab[i] = i;
    }
}

//Creer le tas a partir d'un tableau de valeur, 1 si reussi, 0 sinon
tas_binaire_t *creer_tas_b(couple_t val_couple)
{
    tas_binaire_t *tas = NULL;
    tas = (tas_binaire_t *)malloc(sizeof(tas_binaire_t));

    if (tas != NULL)
    {
        for (int i = 0; i < N; ++i)
        {
            tas->indice_tas[i] = -1;
            //tas->info_n[i]=???;
        }
        tas->tas[0] = val_couple;
        tas->nb_elt = 1;
        //printf("tas %d %d\n", tas->tas[0].d,tas->tas[0].n);
    }
    return tas;
}

int f_g(int i)
{
    return (2 * i) + 1;
}
int f_d(int i)
{
    return (2 * i + 2);
}
int pere(int i)
{
    return (i - 1) / 2;
}

void ajouter_elt(tas_binaire_t *tas, couple_t val)
{
    if (tas->nb_elt == 0)
    {
        tas->tas[0] = val;
        tas->indice_tas[val.n] = tas->nb_elt;
        tas->nb_elt++;
    }
    else if (tas->nb_elt > 0 && tas->nb_elt < N)
    {
        tas->tas[tas->nb_elt].d = val.d;
        tas->tas[tas->nb_elt].n = val.n;
        tas->indice_tas[val.n] = tas->nb_elt;
        detasser(tas, tas->nb_elt);
        tas->nb_elt++;
    }
    else
        printf("ERREUR, plus de place dans le tas");
    //affficher_tas(tas->tas, tas->nb_elt);
}

couple_t *retirer_elt(tas_binaire_t *tas)
{
    couple_t *rac = malloc(sizeof(couple_t));
    rac->d = -1;
    rac->n = -1;

    //affficher_tas(tas->tas, tas->nb_elt);
    if (tas->nb_elt > 1)
    {
        rac->d = tas->tas[0].d;
        rac->n = tas->tas[0].n;
        tas->indice_tas[rac->n] = -2;
        tas->nb_elt--;
        tas->tas[0] = tas->tas[tas->nb_elt];
        tas->indice_tas[tas->tas[0].n] = 0;
        entasser(tas, 0);
    }
    else if (tas->nb_elt == 1)
    {
        rac->d = tas->tas[0].d;
        rac->n = tas->tas[0].n;
        tas->indice_tas[rac->n] = -2;
        tas->nb_elt--;
        //printf("Plus rien a retirer apres\n");
    }
    else
    {
        printf("ERREUR, plus rien a retirer\n");
    }

    //printf("rac = %d,%d\n", rac->d, rac->n);
    return rac;
}

void entasser(tas_binaire_t *tas, int i)
{
    int l = f_g(i);
    int r = f_d(i);
    int min = i;

    if (l <= tas->nb_elt && tas->tas[l].d < tas->tas[i].d && tas->indice_tas[tas->tas[l].n] >= 0)
    {
        min = l;
    }

    if (r <= tas->nb_elt && tas->tas[r].d < tas->tas[min].d && tas->indice_tas[tas->tas[r].n] >= 0)
    {
        min = r;
    }

    if (min != i)
    {
        permute_a_b(&tas->indice_tas[tas->tas[i].n], &tas->indice_tas[tas->tas[min].n]);
        permute_a_b(&tas->tas[i].d, &tas->tas[min].d);
        permute_a_b(&tas->tas[i].n, &tas->tas[min].n);
        entasser(tas, min);
    }
}

void detasser(tas_binaire_t *tas, int i)
{
    int p = pere(i);

    int max = i;

    if (p > 0 && tas->tas[p].d > tas->tas[i].d)
    {
        max = p;
    }

    if (max != i)
    {
        permute_a_b(&tas->indice_tas[tas->tas[i].n], &tas->indice_tas[tas->tas[p].n]);
        permute_a_b(&tas->tas[i].d, &tas->tas[p].d);
        permute_a_b(&tas->tas[i].n, &tas->tas[p].n);

        detasser(tas, max);
    }
}

void fichier_graphiz(tas_binaire_t *tas)
{
    FILE *fichier = NULL;
    fichier = fopen("graph_tas.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    int k = 1;

    fprintf(fichier, "graph { ");
    while (k < tas->nb_elt)
    {
        if (tas->tas[k].n > 0 && tas->tas[f_g(k)].n > 0 && f_g(k) <= tas->nb_elt)
            fprintf(fichier, "\n\t%d--%d", tas->tas[k].n, tas->tas[f_g(k)].n);

        if (tas->tas[k].n > 0 && tas->tas[f_d(k)].n > 0 && f_d(k) <= tas->nb_elt)
            fprintf(fichier, "\n\t%d--%d", tas->tas[k].n, tas->tas[f_d(k)].n);
        k++;
    }
    fprintf(fichier, "\n} ");

    fclose(fichier);
}

void modifier_cle(tas_binaire_t *tas, int indice, int val_ajoutee)
{
    if (indice < tas->nb_elt)
    {
        printf("cle modifie : %d + %d = %d\n", tas->tas[indice].d, val_ajoutee, tas->tas[indice].d + val_ajoutee);
        tas->tas[indice].d += val_ajoutee;
        if (val_ajoutee < 0)
            detasser(tas, indice);
        else
        {
            entasser(tas, indice);
            entasser(tas, indice);
        }
    }
    else
        printf("modification impossible : indice trop petit\n");
}

void diminuer_cle(tas_binaire_t *tas, couple_t val_couple)
{
    int indice = tas->indice_tas[val_couple.n];

    if (indice < tas->nb_elt)
    {
        tas->tas[indice].d = val_couple.d;
        int i = indice;
        int p_i = pere(i);
        /*
        while (i > 0 && tas->tas[p_i].d > tas->tas[i].d)
        {
            permute_a_b(&tas->indice_tas[tas->tas[i].n], &tas->indice_tas[tas->tas[p_i].n]);
            permute_a_b(&tas->tas[i].d, &tas->tas[p_i].d);
            permute_a_b(&tas->tas[i].n, &tas->tas[p_i].n);
            i = p_i;
            p_i = pere(i);
        }
        */
        detasser(tas, indice);
    }
    else
        printf("modification impossible : indice trop petit\n");
}

/*
int *tri_tas_min(tas_binaire_t *tab_valeur)
{
    int *tas = NULL;
    tas = creer_tas_b(tab_valeur, nb_elt);
    //affficher_tab(tas, NB_ELT_MAX);

    if (tas != NULL)
    {
        int nb_elt = tas->nb_elt;
        for (int i = 0; i < nb_elt; i++)
        {
            tab_valeur[i] = retirer_elt(tas);
        }
    }
    else
    {
        printf("echec allocation malloc dans tri_tas_min\n");
    }
    return tab_valeur;
}
*/

// fonction utilisateur de comparaison fournie a qsort()
/*
static int compare(void const *a, void const *b)
{
    // definir des pointeurs type's et initialise's
      avec les parametres 
    int const *pa = a;
    int const *pb = b;

    // evaluer et retourner l'etat de l'evaluation (tri croissant) 
    return *pa - *pb;
}
*/