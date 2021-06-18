#include "tas_binaire.h"

int main()
{
    int tab_v[NB_ELT_MAX];

    init_tab(tab_v);

    tab_v[0] = 12;
    tab_v[1] = 24;
    tab_v[2] = 345;
    tab_v[3] = 44;
    tab_v[4] = 58;
    tab_v[5] = 74;
    tab_v[6] = 6;
    tab_v[7] = 100;
    tab_v[8] = 41;

    //remplir_tab(tab_v);
    affficher_tab(tab_v);

    tas_binaire_t *tas = NULL;

    tas = creer_tas_b(tab_v, tab_v);

    //ajouter_elt(tas, 2);

    //printf("valeur retiree %d\n", retirer(tas));

    fichier_graphiz(tas);

    return 0;
}

void affficher_tab(int tab[NB_ELT_MAX])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}


void init_tab(int tab[NB_ELT_MAX])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        tab[i] = 0;
    }
}

//Creer le tas a partir d'un tableau de valeur, 1 si reussi, 0 sinon
tas_binaire_t *creer_tas_b(int tab[NB_ELT_MAX], int tab_v[NB_ELT_MAX])
{
    tas_binaire_t *tas = NULL;
    tas = malloc(sizeof(tas_binaire_t));
    
    init_tab(tas->arbre);
    
    if (tas != NULL)
    {
        tas->nb_elt = 0;
        for (int i = 0; i < NB_ELT_MAX; i++)
        {
            tas->arbre[i] = tab_v[i];
            tas->nb_elt += (tab_v[i] != 0);
        }

        for (int i = NB_ELT_MAX / 2; i > 0; i--)
            entasser(tas, i);
    }
    return tas;
}

int f_g(int i)
{
    return (2 * i + 1);
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


void fichier_graphiz(tas_binaire_t *tas)
{
    FILE *fichier = NULL;
    fichier = fopen("graph_tas.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    int k = 0;

    fprintf(fichier, "graph { ");
    while (k < tas->nb_elt - 1)
    {
        if (tas->arbre[k] > 0 && tas->arbre[f_g(k)] > 0 && f_g(k) < NB_ELT_MAX)
            fprintf(fichier, "\n\t%d--%d", tas->arbre[k], tas->arbre[f_g(k)]);

        if (tas->arbre[k] > 0 && tas->arbre[f_d(k)] > 0 && f_d(k) < NB_ELT_MAX)
            fprintf(fichier, "\n\t%d--%d", tas->arbre[k], tas->arbre[f_d(k)]);
        k++;
    }
    fprintf(fichier, "\n} ");

    fclose(fichier);
}

void entasser(tas_binaire_t *tas, int i)
{
    int l = f_g(i);
    int r = f_d(i);
    int max = i;

    if (l < tas->nb_elt && tas->arbre[l] < tas->arbre[i])
    {
        max = l;
    }
    if (r < tas->nb_elt && tas->arbre[r] < tas->arbre[i])
    {
        max = r;
    }
    if(max !=i)
    {
        permute_a_b(&(tas->arbre[i]), &(tas->arbre[max]));
        entasser(tas, max);
    }
}

void detasser(tas_binaire_t *tas, int i)
{
    int p = pere(i);

    int max = i;

    if (pere <0 && tas->arbre[pere] >tas->arbre[i])
    {
        max = pere;
    }

    if(max !=i)
    {
        permute_a_b(&(tas->arbre[i]), &(tas->arbre[max]));
        detasser(tas, max);
    }
}