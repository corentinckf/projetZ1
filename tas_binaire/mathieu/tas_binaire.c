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
    tas_binaire_t *tas = NULL;

    tas = creer_tas_b(tas, tab_v);

    fichier_graphiz(tas);

    return 0;
}

void init_tab(int tab[NB_ELT_MAX])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        tab[i] = 0;
    }
}

//Creer le tas a partir d'un tableau de valeur, 1 si reussi, 0 sinon
tas_binaire_t *creer_tas_b(tas_binaire_t *tas_vide, int tab_v[NB_ELT_MAX])
{
    tas_binaire_t *tas = NULL;
    tas = malloc(sizeof(tas_binaire_t));
    if (tas != NULL)
    {
        tas->nb_elt = 0;
        for (int i = 0; i < NB_ELT_MAX; i++)
        {
            tas->arbre[i] = tab_v[i];
            tas->nb_elt += (tab_v[i] != 0);
        }
    }
    //percolate_down();
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

void percolate_up(tas_binaire_t *tas)
{
    int i = 0;
    int i_pere = pere(i);
    while (i > 0 && tas->arbre[i] < tas->arbre[i_pere])
    {
        permute_a_b(&tas->arbre[i], &tas->arbre[i_pere]);
        i = i_pere;
        i_pere = pere(i);
    }
}

void percolate_down(tas_binaire_t *tas)
{
    int i = 0;
    int i_f_g = f_g(i);
    int i_f_d = f_d(i);

    while (i < tas->nb_elt && (tas->arbre[i] > tas->arbre[i_f_g] || tas->arbre[i] > tas->arbre[i_f_d]))
    {
        if (tas->arbre[i] > tas->arbre[i_f_g])
        {
            permute_a_b(&tas->arbre[i], &tas->arbre[i_f_g]);
            i = i_f_g;
        }
        else
        {
            permute_a_b(&tas->arbre[i], &tas->arbre[i_f_d]);
            i = i_f_d;
        }

        i_f_g = f_g(i);
        i_f_d = f_d(i);
    }
}

void permute_a_b(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ajouter_elt(tas_binaire_t *tas, int elt)
{
    if (tas->nb_elt < NB_ELT_MAX)
    {
        tas->arbre[tas->nb_elt] = elt;
        tas->nb_elt++;
        percolate_up(tas);
    }
    else
    {
        printf("Tas trop petit\n");
    }
}
int retirer(tas_binaire_t *tas)
{
    int rac = tas->arbre[0];

    if (tas->nb_elt > 0)
    {
        tas->nb_elt--;
        tas->arbre[0] = tas->arbre[tas->nb_elt];
        percolate_down(tas);
    }
    else
    {
        printf("Pas d'elt dans le tas");
    }
    return rac;
}

void fichier_graphiz(tas_binaire_t *tas)
{
    FILE *fichier = NULL;
    fichier = fopen("graph_tas.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    int k = 0;

    fprintf(fichier, "graph { ");
    while (k < tas->nb_elt)
    {
        if (tas->arbre[k] != 0 && tas->arbre[f_g(k)] != 0)
            fprintf(fichier, "\n\t%d--%d", tas->arbre[k], tas->arbre[f_g(k)]);

        if (tas->arbre[k] != 0 && tas->arbre[f_d(k)] != 0)
            fprintf(fichier, "\n\t%d--%d", tas->arbre[k], tas->arbre[f_d(k)]);
        k++;
    }
    fprintf(fichier, "\n} ");

    fclose(fichier);
}