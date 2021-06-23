#include "tas_binaire.h"

int main_tas_binaire()
{

    return 0;
}

void affficher_tab(int *tab)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", tab[i]);
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
int *creer_tas_b()
{
    tas_binaire_t *tas = NULL;
    tas = (tas_binaire_t *)malloc(sizeof(tas_binaire_t) * N);

    init_tab(tas);

    if (tas != NULL)
    {

        tas->nb_elt = 0;
        for (int i = 0; i < N; i++)
        {
            tas[i + 1] = tab_v[i];
            tas[0] += (tab_v[i] != 0);
        }

        for (int i = (tas[0] / 2); i > 0; i--)
        {
            //printf("tas[%d]=%d\n", i, tas[i]);
            entasser(tas, i);
        }
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

void permute_a_b(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ajouter_elt(int *tas, int val)
{
    if (tas[0] < NB_ELT_MAX)
    {
        tas[0]++;
        tas[tas[0]] = val;
        detasser(tas, tas[0]);
    }
    else
        printf("plus de place dans le tas");
}

int retirer_elt(int *tas)
{
    int rac = 0;
    if (tas[0] > 0)
    {
        rac = tas[1];
        tas[1] = tas[tas[0]];
        tas[0]--;
        entasser(tas, 1);
    }
    else
    {
        printf("plus rien a retirer\n");
    }
    return rac;
}

void entasser(int *tas, int i)
{
    int l = f_g(i);
    int r = f_d(i);
    int min = i;
    //printf("tas[i]=%d, tas[l]=%d, tas[r]=%d\n", tas[i], tas[l], tas[r]);

    if (l <= tas[0] && tas[l] < tas[i])
    {
        min = l;
    }
    void fichier_graphiz(int *tas)

        int max = i;

    if (p > 1 && tas[p] > tas[i])
    {
        max = p;
    }

    if (max != i)
    {
        permute_a_b(&(tas[i]), &(tas[max]));
        detasser(tas, max);
    }
}

void fichier_graphiz(int *tas)
{
    FILE *fichier = NULL;
    fichier = fopen("graph_tas.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    int k = 1;

    fprintf(fichier, "graph { ");
    while (k <= tas[0])
    {
        if (tas[k] > 0 && tas[f_g(k)] > 0 && f_g(k) <= tas[0])
            fprintf(fichier, "\n\t%d--%d", tas[k], tas[f_g(k)]);

        if (tas[k] > 0 && tas[f_d(k)] > 0 && f_d(k) <= tas[0])
            fprintf(fichier, "\n\t%d--%d", tas[k], tas[f_d(k)]);
        k++;
    }
    fprintf(fichier, "\n} ");

    fclose(fichier);
}

void modifier_cle(int *tas, int indice, int val_ajoutee)
{
    if (indice < tas[0])
    {
        printf("cle modifie : %d + %d = %d\n", tas[indice], val_ajoutee, tas[indice] + val_ajoutee);
        tas[indice] += val_ajoutee;
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

void diminuer_cle(int *tas, int indice, int nouv_key)
{
    if (indice <= tas[0])
    {
        tas[indice] = nouv_key;
        int i = indice;
        int p_i = pere(i);
        while (i > 1 && tas[p_i] > tas[i])
        {
            permute_a_b(&tas[i], &tas[p_i]);
            i = p_i;
            p_i = pere(i);
        }
    }
    else
        printf("modification impossible : indice trop petit\n");
}

int *tri_tas_min(int *tab_valeur, int nb_elt)
{
    int *tas = NULL;
    tas = creer_tas_b(tab_valeur, nb_elt);
    //affficher_tab(tas, NB_ELT_MAX);

    if (tas != NULL)
    {
        int nb_elt = tas[0];
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

/* fonction utilisateur de comparaison fournie a qsort() */
static int compare(void const *a, void const *b)
{
    /* definir des pointeurs type's et initialise's
      avec les parametres */
    int const *pa = a;
    int const *pb = b;

    /* evaluer et retourner l'etat de l'evaluation (tri croissant) */
    return *pa - *pb;
}