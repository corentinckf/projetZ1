#include "tas_binaire_struct.h"

/*void affficher_tab(arrete_t  tab[NB_ELT_MAX])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}*/

/*void init_tab(arrete_t  tab[NB_ELT_MAX])
{
    for (int i = 0; i < NB_ELT_MAX; i++)
    {
        tab[i] = 0;
    }
}*/

//Creer le tas a partir d'un tableau de valeur, 1 si reussi, 0 sinon
/*tas_binaire_t *creer_tas_b(arrete_t  tab_v[NB_ELT_MAX])
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

        for (int i = NB_ELT_MAX / 2; i >= 0; i--)
        {
            entasser(tas, i);
            
        }
    }
    return tas;
}*/

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
    int p = (i - 1) / 2;
    if (p >= 0)
        return p;
    else
        return 0;
}

void permute_a_b(arrete_t *a, arrete_t *b)
{
    arrete_t temp = *a;
    *a = *b;
    *b = temp;
}

arrete_t retirer_elt(tas_binaire_t *tas)
{
    arrete_t rac;
    if (tas->nb_elt > 0)
    {
        rac = tas->arbre[0];
        tas->nb_elt--;
        tas->arbre[0] = tas->arbre[tas->nb_elt];
        entasser(tas, 0);
    }
    else
    {
        printf("plus rien a retirer\n");
    }
    return rac;
}

void ajouter_arr(tas_binaire_t *tas, arrete_t val)
{
    if (tas->nb_elt < NB_ELT_MAX)
    {
        tas->arbre[tas->nb_elt] = val;
        tas->nb_elt++;
        detasser(tas, tas->nb_elt - 1);
    }
    else
        printf("plus de place dans le tas");
}


void entasser(tas_binaire_t *tas, int i)
{
    int l = f_g(i);
    int r = f_d(i);
    int max = i;
    /*
    fichier_graphiz(tas);
    system("dot -Tjp\ng graph_tas.dot -o img.jpg");
    system("eog ./img.jpg 2> /dev/null");
    */
    if (l < tas->nb_elt && tas->arbre[l].poids < tas->arbre[i].poids)
    {
        max = l;
    }
    if (r < tas->nb_elt && tas->arbre[r].poids < tas->arbre[i].poids)
    {
        max = r;
    }
    if (max != i)
    {
        permute_a_b(&(tas->arbre[i]), &(tas->arbre[max]));
        entasser(tas, max);
    }
}

void detasser(tas_binaire_t *tas, int i)
{
    int p = pere(i);

    int max = i;

    if (p > 0 && tas->arbre[p].poids > tas->arbre[i].poids)
    {
        max = p;
    }

    if (max != i)
    {
        permute_a_b(&(tas->arbre[i]), &(tas->arbre[max]));
        detasser(tas, max);
    }
}

void fichier_graphiz(tas_binaire_t *tas)
{
    FILE *fichier = NULL;
    fichier = fopen("tas.dot", "w");
    if (fichier == NULL)
        exit(EXIT_FAILURE);

    int k = 0;

    fprintf(fichier, "graph { ");
    while (k < tas->nb_elt - 1)
    {
        if (tas->arbre[k].a > 0 && tas->arbre[f_g(k)].a > 0 && f_g(k) < tas->nb_elt)
            fprintf(fichier, "\n\t%d--%d", tas->arbre[k].a, tas->arbre[f_g(k)].a);

        if (tas->arbre[k].b > 0 && tas->arbre[f_d(k)].b > 0 && f_d(k) < tas->nb_elt)
            fprintf(fichier, "\n\t%d--%d", tas->arbre[k].b, tas->arbre[f_d(k)].b);
        //fprintf(fichier, "\n\t%d--%d", tas->arbre[k].a, tas->arbre[k].b);

        k++;
    }
    fprintf(fichier, "\n} ");

    fclose(fichier);

    system("dot -Tjpg tas.dot -o img.jpg");
    system("display ./img.jpg 2> /dev/null");
}

/*void diminuer_cle(tas_binaire_t *tas, int indice, int nouv_key)
{
    if (indice < tas->nb_elt)
    {
        tas->arbre[indice] = nouv_key;
        int i = indice;
        int p_i = pere(i);
        while (i > 1 && tas->arbre[p_i] > tas->arbre[i])
        {
            permute_a_b(&tas->arbre[i], &tas->arbre[p_i]);
            i = p_i;
            p_i = pere(i);
        }
    }
    else
        printf("modification impossible : indice trop petit\n");
}*/